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
        src/CircleTrainingScenario.cpp \
        src/CircleTrainingScenario2.cpp \
        src/CircleTrainingScenario3.cpp \
        src/Creature.cpp \
        src/DebugScenario.cpp \
        src/Entity.cpp \
        src/Food.cpp \
        src/Model.cpp \
        src/NeuralNetwork.cpp \
        src/Organism.cpp \
        src/Scenario.cpp \
        src/SimScenario.cpp \
        src/SimTrainingScenario.cpp \
        src/Simulation.cpp \
        src/View.cpp \
        src/main.cpp \
        src/utils.cpp


RESOURCES += src/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    src/Board.h \
    src/CircleTrainingScenario.h \
    src/CircleTrainingScenario2.h \
    src/CircleTrainingScenario3.h \
    src/Creature.h \
    src/DebugScenario.h \
    src/Entity.h \
    src/Food.h \
    src/Model.h \
    src/NeuralNetwork.h \
    src/Organism.h \
    src/Scenario.h \
    src/SimScenario.h \
    src/SimTrainingScenario.h \
    src/Simulation.h \
    src/View.h \
    src/constants.h \
    src/utils.h \

INCLUDEPATH += C:\bin\lib\armadillo\include
LIBS += \
    -LC:\bin\lib\armadillo\examples\lib_win64 \
    -llapack_win64_MT \
    -lblas_win64_MT
