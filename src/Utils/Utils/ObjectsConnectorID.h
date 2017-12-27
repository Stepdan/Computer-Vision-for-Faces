#pragma once

#include <QString>

// Глобальный набор идентификаторов

namespace IObjectsConnectorID
{

static const QString LOAD_IMAGE       = "LOAD_IMAGE";
static const QString LOAD_IMAGE2      = "LOAD_IMAGE2";
static const QString SAVE_IMAGE       = "SAVE_IMAGE";
static const QString UNDO             = "UNDO";
static const QString REDO             = "REDO";
static const QString RESET            = "RESET";
static const QString COMPARE_PRESSED  = "COMPARE_PRESSED";
static const QString COMPARE_RELEASED = "COMPARE_RELEASED";

static const QString EFFECTS_CLICKED  = "EFFECTS_CLICKED";
static const QString EFFECT_APPLYED   = "EFFECT_APPLYED";
static const QString EFFECT_CANCELED  = "EFFECT_CANCELED";

static const QString CAPTURE_CLICKED   = "CAPTURE_CLICKED";
static const QString CAPTURE_STARTED   = "CAPTURE_STARTED";
static const QString CAPTURE_CANCELED  = "CAPTURE_CANCELED";

static const QString TRAINING_CLICKED = "TRAINING_CLICKED";

static const QString CAPTURED_FRAME_CHANGED = "CAPTURED_FRAME_CHANGED";

}
