# TranslationUtils.cmake
# Provides common functions for handling translation files

include(GNUInstallDirs)

function(_treeland_get_translation_dest OUT_VAR)
    if(DEFINED TREELAND_COMPONENTS_TRANSLATION_DIR AND NOT TREELAND_COMPONENTS_TRANSLATION_DIR STREQUAL "")
        set(${OUT_VAR} "${TREELAND_COMPONENTS_TRANSLATION_DIR}" PARENT_SCOPE)
        return()
    endif()

    if(DEFINED TREELAND_DATA_DIR AND NOT TREELAND_DATA_DIR STREQUAL "")
        set(${OUT_VAR} "${TREELAND_DATA_DIR}/translations" PARENT_SCOPE)
        return()
    endif()

    set(${OUT_VAR} "${CMAKE_INSTALL_DATADIR}/treeland/translations" PARENT_SCOPE)
endfunction()

function(setup_translations TARGET_NAME TRANSLATION_PREFIX)
    # Automatically discover all translation files
    file(GLOB TS_FILES "${CMAKE_CURRENT_SOURCE_DIR}/translations/${TRANSLATION_PREFIX}.*.ts")
    
    # Filter out non-translation files (if any)
    list(FILTER TS_FILES INCLUDE REGEX ".*\\.ts$")

    if(NOT TS_FILES)
        set(TRANSLATED_FILES "" PARENT_SCOPE)
        return()
    endif()
    
    # Set translation files variable
    set(TRANSLATED_FILES)
    
    # Add lupdate target
    qt_add_lupdate(
        SOURCE_TARGETS ${TARGET_NAME}
        TS_FILES ${TS_FILES}
        NO_GLOBAL_TARGET
    )
    
    # Add lrelease target
    qt_add_lrelease(
        TS_FILES ${TS_FILES}
        QM_FILES_OUTPUT_VARIABLE TRANSLATED_FILES
    )
    
    # Install translation files
    _treeland_get_translation_dest(_translation_dest)
    if(TRANSLATED_FILES AND _translation_dest)
        install(FILES ${TRANSLATED_FILES} DESTINATION "${_translation_dest}")
    endif()
    
    # Set TRANSLATED_FILES variable to parent scope
    set(TRANSLATED_FILES ${TRANSLATED_FILES} PARENT_SCOPE)
endfunction()

function(setup_main_translations TARGET_NAME)
    # Automatically discover all main translation files
    file(GLOB TS_FILES "${CMAKE_SOURCE_DIR}/translations/treeland.*.ts")
    
    # Filter out non-translation files (if any)
    list(FILTER TS_FILES INCLUDE REGEX ".*\\.ts$")

    if(NOT TS_FILES)
        set(TRANSLATED_FILES "" PARENT_SCOPE)
        return()
    endif()
    
    # Set translation files variable
    set(TRANSLATED_FILES)
    
    # Add lupdate target
    qt_add_lupdate(
        SOURCE_TARGETS ${TARGET_NAME}
        TS_FILES ${TS_FILES}
        NO_GLOBAL_TARGET
    )
    
    # Add lrelease target
    qt_add_lrelease(
        TS_FILES ${TS_FILES}
        QM_FILES_OUTPUT_VARIABLE TRANSLATED_FILES
    )
    
    # Install translation files
    _treeland_get_translation_dest(_translation_dest)
    if(TRANSLATED_FILES AND _translation_dest)
        install(FILES ${TRANSLATED_FILES} DESTINATION "${_translation_dest}")
    endif()
    
    # Set TRANSLATED_FILES variable to parent scope
    set(TRANSLATED_FILES ${TRANSLATED_FILES} PARENT_SCOPE)
endfunction()
