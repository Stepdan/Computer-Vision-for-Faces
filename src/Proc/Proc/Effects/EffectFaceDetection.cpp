#include "opencv2/photo.hpp"

#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/image_processing/render_face_detections.h>
#include <dlib/image_processing.h>
#include <dlib/opencv/cv_image.h>
#include <dlib/smart_pointers/shared_ptr.h>

#include "EffectFaceDetection.h"

#include "ModelPath.h"

namespace {

constexpr size_t FACE = 0;
constexpr size_t EYEBROW_LEFT = 17;
constexpr size_t EYEBROW_RIGHT = 22;
constexpr size_t NOSE_VERTICAL = 27;
constexpr size_t NOSE_HORIZONTAL = 31;
constexpr size_t EYE_LEFT = 36;
constexpr size_t EYE_RIGHT = 42;
constexpr size_t MOUTH_OUTER = 48;
constexpr size_t MOUTH_INNER = 60;
constexpr size_t PUPILS_POINTS = 68;
constexpr size_t POINTS_COUNT = 70;

}

namespace Proc {

EffectFaceDetection::EffectFaceDetection(const SettingsFaceDetection & settings/* = SettingsFaceDetection()*/)
	: m_settings(settings)
{
}

void EffectFaceDetection::SetBaseSettings(const BaseSettings & settings)
{
	m_settings = dynamic_cast<const SettingsFaceDetection &>(settings);
}

const BaseSettings & EffectFaceDetection::GetBaseSettings() const
{
	return m_settings;
}

void EffectFaceDetection::Apply(const cv::Mat & src, cv::Mat & dst)
{
	dlib::shape_predictor sp;
	dlib::deserialize(g_modelPath[DLIB_FACE_70]) >> sp;

	dlib::cv_image<dlib::rgb_pixel> image(src);
	auto detector = dlib::get_frontal_face_detector();
	const auto dets = detector(image);

	for (const auto & det : dets)
	{
		dlib::full_object_detection shape = sp(image, det);

		Contour faceContour
			, leftEyebrow, rightEyebrow
			, noseVertical, noseHorizontal
			, leftEye, rightEye
			, mouthOuter, mouthInner
			;

		// раскладываем точки лиц по компонентам
		for (size_t i = FACE; i < EYEBROW_LEFT; ++i)
			faceContour.push_back({shape.part(i).x(), shape.part(i).y()});
		for (size_t i = EYEBROW_LEFT; i < EYEBROW_RIGHT; ++i)
			leftEyebrow.push_back({shape.part(i).x(), shape.part(i).y()});
		for (size_t i = EYEBROW_RIGHT; i < NOSE_VERTICAL; ++i)
			rightEyebrow.push_back({shape.part(i).x(), shape.part(i).y()});
		for (size_t i = NOSE_VERTICAL; i < NOSE_HORIZONTAL; ++i)
			noseVertical.push_back({shape.part(i).x(), shape.part(i).y()});
		for (size_t i = NOSE_HORIZONTAL; i < EYE_LEFT; ++i)
			noseHorizontal.push_back({shape.part(i).x(), shape.part(i).y()});
		for (size_t i = EYE_LEFT; i < EYE_RIGHT; ++i)
			leftEye.push_back({shape.part(i).x(), shape.part(i).y()});
		for (size_t i = EYE_RIGHT; i < MOUTH_OUTER; ++i)
			rightEye.push_back({shape.part(i).x(), shape.part(i).y()});
		for (size_t i = MOUTH_OUTER; i < MOUTH_INNER; ++i)
			mouthOuter.push_back({shape.part(i).x(), shape.part(i).y()});
		for (size_t i = MOUTH_INNER; i < POINTS_COUNT; ++i)
			mouthInner.push_back({shape.part(i).x(), shape.part(i).y()});

		PairPoint pupils = { {shape.part(PUPILS_POINTS)  .x(), shape.part(PUPILS_POINTS)  .y()},
							 {shape.part(PUPILS_POINTS+1).x(), shape.part(PUPILS_POINTS+1).y()} };

		Face face(faceContour
			, { leftEyebrow, rightEyebrow }
			, { noseVertical, noseHorizontal }
			, { leftEye, rightEye }
			, { mouthOuter, mouthInner }
			, { { det.left(), det.top() },{ det.right(), det.bottom() } }
			, pupils
		);
		m_settings.AddFace(face);
	}
}

}
