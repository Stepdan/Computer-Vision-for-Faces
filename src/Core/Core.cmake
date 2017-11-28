AddTarget(NAME Core
    SOURCE_DIR
        ${CORE_ROOT}/
    SRC
        *.cpp
        *.h
    SUBDIRS
        Core/Interfaces/
        Core/CoreTypes/
        Core/DataImage/
        Core/Utils/
    DEPS
        Types
    QT_USE
        Core
        Widgets
)
