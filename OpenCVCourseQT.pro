TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp


INCLUDEPATH += D:\\Nestor\\Libraries\\opencv3.4.2\\build\\include \

LIBS += -LD:\\Nestor\\Libraries\\opencv3.4.2\\build\\bin \
    libopencv_calib3d342 \
    libopencv_core342 \
    libopencv_features2d342 \
    libopencv_flann342 \
    libopencv_highgui342 \
    libopencv_imgcodecs342 \
    libopencv_imgproc342 \
    libopencv_ml342 \
    libopencv_objdetect342 \
    libopencv_photo342 \
    libopencv_shape342 \
    libopencv_stitching342 \
    libopencv_superres342 \
    libopencv_video342 \
    libopencv_videoio342 \
    libopencv_videostab342
