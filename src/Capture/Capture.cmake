AddTarget(NAME Capture
    SOURCE_DIR
        ${CAPTURE_ROOT}/
    SRC
        *.cpp
        *.h
    SUBDIRS
        Capture/Controller
    DEPS
        Types
        Core
        Proc
    QT_USE
        Core
        Widgets
)
