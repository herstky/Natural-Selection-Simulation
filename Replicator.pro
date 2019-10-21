QT += quick
QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Refer to the documentation for the
# deprecated API to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        blue.cpp \
        green.cpp \
        main.cpp \
        red.cpp \
        simulation.cpp \
        organism.cpp \
        utils.cpp \
        scentsystem.cpp \
        neuralnetwork.cpp \
        view.cpp \
        model.cpp \
        entity.cpp \
        food.cpp \
        board.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    blue.h \
    constants.h \
    green.h \
    red.h \
    simulation.h \
    organism.h \
    utils.h \
    scentsystem.h \
    neuralnetwork.h \
    view.h \
    model.h \
    entity.h \
    food.h \
    board.h 

INCLUDEPATH += C:\bin\lib\armadillo\include
LIBS += \
    -LC:\bin\lib\armadillo\examples\lib_win64 \
    -llapack_win64_MT \
    -lblas_win64_MT
