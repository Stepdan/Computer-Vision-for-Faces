AddTarget(NAME Utils
    SOURCE_DIR
        ${UTILS_ROOT}/
    SRC
        *.cpp
        *.h
    SUBDIRS
    	Utils/
    QT_USE
        Core
        Widgets
)