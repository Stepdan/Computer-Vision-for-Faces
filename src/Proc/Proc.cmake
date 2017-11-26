AddTarget(NAME Proc
    SOURCE_DIR
        ${PROC_ROOT}/
    SRC
        *.cpp
        *.h
    SUBDIRS
        Proc/Interfaces/
        Proc/Settings/
        Proc/Effects/
    DEPS
        Types
    QT_USE
        Core
        Widgets
)
