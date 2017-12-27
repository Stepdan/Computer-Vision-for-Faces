AddTarget(EXECUTABLE NAME VisionApp
    SOURCE_DIR
        ${VISION_APP_ROOT}/
    SRC
        *.cpp
        *.h
        *.qrc
    UI_FILES
        ${SOURCE_DIR}/*.ui
        ${SOURCE_DIR}/UI/*.ui
        ${SOURCE_DIR}/UI/CapturePanel/*.ui
        ${SOURCE_DIR}/UI/EffectsPanel/*.ui
        ${SOURCE_DIR}/UI/TrainingPanel/*.ui
        ${SOURCE_DIR}/UI/MainWindow/*.ui
        ${SOURCE_DIR}/UI/Scene/*.ui
    SUBDIRS
        UI/
        UI/CapturePanel
        UI/EffectsPanel
        UI/TrainingPanel
        UI/MainWindow
        UI/Scene
        Helpers/
    DEPS
        Types
        Core
        Proc
        Capture
        Utils
    QT_USE
        Core
        Widgets
)
