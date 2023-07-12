// Copyright (C) 2023 JiDe Zhang <zhangjide@deepin.org>.
// SPDX-License-Identifier: Apache-2.0 OR LGPL-3.0-only OR GPL-2.0-only OR GPL-3.0-only

#include "woutputlayout.h"
#include "private/woutputlayout_p.h"
#include "woutput.h"

#include <qwoutput.h>

QW_USE_NAMESPACE
WAYLIB_SERVER_BEGIN_NAMESPACE

WOutputLayoutPrivate::WOutputLayoutPrivate(WOutputLayout *qq)
    : WObjectPrivate(qq)
{

}

WOutputLayout::WOutputLayout(WOutputLayoutPrivate &dd, QObject *parent)
    : QWOutputLayout(parent)
    , WObject(dd)
{

}

WOutputLayout::WOutputLayout(QObject *parent)
    : WOutputLayout(*new WOutputLayoutPrivate(this), parent)
{

}

QList<WOutput*> WOutputLayout::outputs() const
{
    W_DC(WOutputLayout);
    return d->outputs;
}

void WOutputLayout::add(WOutput *output, const QPoint &pos)
{
    W_D(WOutputLayout);
    Q_ASSERT(!d->outputs.contains(output));
    d->outputs.append(output);

    QWOutputLayout::add(output->handle(), pos);
    output->setLayout(this);

    Q_EMIT outputAdded(output);
}

void WOutputLayout::move(WOutput *output, const QPoint &pos)
{
    W_D(WOutputLayout);
    Q_ASSERT(d->outputs.contains(output));
    QWOutputLayout::move(output->handle(), pos);
}

void WOutputLayout::remove(WOutput *output)
{
    W_D(WOutputLayout);
    Q_ASSERT(d->outputs.contains(output));
    d->outputs.removeOne(output);

    QWOutputLayout::remove(output->handle());
    output->setLayout(nullptr);

    Q_EMIT outputRemoved(output);
}

WAYLIB_SERVER_END_NAMESPACE
