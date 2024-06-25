// Copyright (C) 2023 Dingyuan Zhang <zhangdingyuan@uniontech.com>.
// SPDX-License-Identifier: Apache-2.0 OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include "wglobal.h"
#include "woutput.h"
#include "wxdgshell.h"
#include "wxdgsurface.h"
#include "private/wglobal_p.h"
#include "wforeigntoplevelv1.h"

#include <qwforeigntoplevelhandlev1.h>
#include <qwxdgshell.h>

#include <map>
#include <memory>

extern "C" {
#define static
#include <wlr/types/wlr_foreign_toplevel_management_v1.h>
#undef static
}

QW_USE_NAMESPACE

WAYLIB_SERVER_BEGIN_NAMESPACE

class WForeignToplevelPrivate : public WObjectPrivate {
public:
    WForeignToplevelPrivate(WForeignToplevel *qq)
        : WObjectPrivate(qq) {}
    ~WForeignToplevelPrivate() {
        for (auto pair : connections) {
            for (auto co : pair.second) {
                QObject::disconnect(co);
            }
        }

        connections.clear();
        surfaces.clear();
    }

    void initSurface(WXdgSurface *surface) {
        auto handle = surfaces[surface];
        std::vector<QMetaObject::Connection> connection;

        connection.push_back(surface->safeConnect(&WXdgSurface::titleChanged, surface, [=] {
            handle->setTitle(surface->title().toUtf8());
        }));

        connection.push_back(surface->safeConnect(&WXdgSurface::appIdChanged, surface, [=] {
            handle->setAppId(surface->appId().toUtf8());
        }));

        connection.push_back(surface->safeConnect(&WXdgSurface::minimizeChanged, surface, [=] {
            handle->setMinimized(surface->isMinimized());
        }));

        connection.push_back(surface->safeConnect(&WXdgSurface::maximizeChanged, surface, [=] {
            handle->setMaximized(surface->isMaximized());
        }));

        connection.push_back(surface->safeConnect(&WXdgSurface::fullscreenChanged, surface, [=] {
            handle->setFullScreen(surface->isFullScreen());
        }));

        connection.push_back(surface->safeConnect(&WXdgSurface::activateChanged, surface, [=] {
            handle->setActivated(surface->isActivated());
        }));

        connection.push_back(surface->safeConnect(&WXdgSurface::parentSurfaceChanged, surface, [this, surface, handle] {
            auto find = std::find_if(
                surfaces.begin(), surfaces.end(),
                [surface](auto pair) { return pair.first == surface; });

            handle->setParent(find != surfaces.end() ? find->second.get() : nullptr);
        }));

        connection.push_back(surface->surface()->safeConnect(&WSurface::outputEntered, surface, [this, handle](WOutput *output) {
            handle->outputEnter(output->handle());
        }));

        connection.push_back(surface->surface()->safeConnect(&WSurface::outputLeft, surface, [this, handle](WOutput *output) {
            handle->outputLeave(output->handle());
        }));

        connection.push_back(QObject::connect(handle.get(),
                            &QWForeignToplevelHandleV1::requestActivate,
                            surface,
                            [surface, this](wlr_foreign_toplevel_handle_v1_activated_event *event) {
                                Q_EMIT q_func()->requestActivate(surface);
                            }));

        connection.push_back(QObject::connect(handle.get(),
                            &QWForeignToplevelHandleV1::requestMaximize,
                            surface,
                            [surface, this](wlr_foreign_toplevel_handle_v1_maximized_event *event) {
                                Q_EMIT q_func()->requestMaximize(surface, event->maximized);
                            }));

        connection.push_back(QObject::connect(handle.get(),
                            &QWForeignToplevelHandleV1::requestMinimize,
                            surface,
                            [surface, this](wlr_foreign_toplevel_handle_v1_minimized_event *event) {
                                Q_EMIT q_func()->requestMinimize(surface, event->minimized);
                            }));

        connection.push_back(QObject::connect(handle.get(),
                            &QWForeignToplevelHandleV1::requestFullscreen,
                            surface,
                            [surface, this](wlr_foreign_toplevel_handle_v1_fullscreen_event *event) {
                                Q_EMIT q_func()->requestFullscreen(surface, event->fullscreen);
                            }));

        connection.push_back(QObject::connect(handle.get(),
                            &QWForeignToplevelHandleV1::requestClose,
                            surface,
                            [surface, this] {
                                Q_EMIT q_func()->requestClose(surface);
                            }));

        Q_EMIT surface->titleChanged();
        Q_EMIT surface->appIdChanged();
        Q_EMIT surface->minimizeChanged();
        Q_EMIT surface->maximizeChanged();
        Q_EMIT surface->fullscreenChanged();
        Q_EMIT surface->activateChanged();
        Q_EMIT surface->parentSurfaceChanged();

        connections.insert({surface, connection});
    }

    void add(WXdgSurface *surface) {
        W_Q(WForeignToplevel);

        auto handle = std::shared_ptr<QWForeignToplevelHandleV1>(QWForeignToplevelHandleV1::create(q->nativeInterface<QWForeignToplevelManagerV1>()));
        surfaces.insert({surface, handle});
        initSurface(surface);
    }

    void remove(WXdgSurface *surface) {
        Q_ASSERT(connections.count(surface));

        for (auto co : connections[surface]) {
            QObject::disconnect(co);
        }

        connections.erase(surface);
        surfaces.erase(surface);
    }

    void surfaceOutputEnter(WXdgSurface *surface, WOutput *output) {
        Q_ASSERT(surfaces.count(surface));
        auto handle = surfaces[surface];
        handle->outputEnter(output->handle());
    }

    void surfaceOutputLeave(WXdgSurface *surface, WOutput *output) {
        Q_ASSERT(surfaces.count(surface));
        auto handle = surfaces[surface];
        handle->outputLeave(output->handle());
    }

    W_DECLARE_PUBLIC(WForeignToplevel)

    std::map<WXdgSurface*, std::shared_ptr<QWForeignToplevelHandleV1>> surfaces;
    std::map<WXdgSurface*, std::vector<QMetaObject::Connection>> connections;
};

WForeignToplevel::WForeignToplevel(QObject *parent)
    : WObject(*new WForeignToplevelPrivate(this), nullptr)
{
}

void WForeignToplevel::addSurface(WXdgSurface *surface)
{
    W_D(WForeignToplevel);

    d->add(surface);
}

void WForeignToplevel::removeSurface(WXdgSurface *surface)
{
    W_D(WForeignToplevel);

    d->remove(surface);
}

void WForeignToplevel::create(WServer *server) {
    W_D(WForeignToplevel);

    m_handle = QWForeignToplevelManagerV1::create(server->handle());
}

void WForeignToplevel::destroy(WServer *server) {

}

WAYLIB_SERVER_END_NAMESPACE
