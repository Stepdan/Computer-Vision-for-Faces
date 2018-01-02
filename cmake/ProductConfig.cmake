set(DLIB_FACE_68 "${REPO_ROOT}/models/shape_predictor_68_face_landmarks.dat")
set(DLIB_FACE_70 "${REPO_ROOT}/models/shape_predictor_70_face_landmarks.dat")

configure_file(${CMAKE_ROOT}/Templates/ModelPath.h.in ModelPath.h)