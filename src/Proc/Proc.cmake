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
        Proc/Effects/Factory
    DEPS
        Types
        Core
    QT_USE
        Core
        Widgets
)
