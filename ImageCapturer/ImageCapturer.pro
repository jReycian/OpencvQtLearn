QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

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

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
