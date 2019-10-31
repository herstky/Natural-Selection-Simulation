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
        src/Scenario/Training/CircleTraining/QuickWeak.cpp \
        src/Scenario/Scenario.cpp \
        src/Scenario/SimScenario.cpp \
        src/Scenario/Training/Training.cpp \
        src/Scenario/Training/CircleTraining/CircleTraining.cpp \
        src/Scenario/Training/SimTrainingScenario.cpp \
        src/Scenario/Training/CircleTraining/CircleTrainingScenario2.cpp \
        src/Scenario/Training/CircleTraining/NoCrossOver.cpp \
        src/Model/Entity/Organism/Creature.cpp \
        src/Model/Entity/Organism/WeakCreature.cpp \
        srd/Model/Entity/Organism/StrongCreature.cpp \
        src/Board.cpp \
        src/Scenario/DebugScenario.cpp \
        src/Model/Entity/Entity.cpp \
        src/Model/Entity/Food.cpp \
        src/Model/Model.cpp \
        src/NeuralNetwork.cpp \
        src/Model/Entity/Organism/Organism.cpp \
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
    src/Scenario/Scenario.h \
    src/Scenario/SimScenario.h \
    src/Scenario/Training/Training.h \
    src/Scenario/Training/CircleTraining/CircleTraining.h \
    src/Scenario/Training/SimTrainingScenario.h \
    src/Scenario/Training/CircleTraining/QuickWeak.h \
    src/Scenario/Training/CircleTraining/CircleTrainingScenario2.h \
    src/Scenario/Training/CircleTraining/NoCrossOver.h \
    src/Model/Entity/Organism/Creature.h \
    src/Model/Entity/Organism/WeakCreature.h \
    src/Model/Entity/Organism/StrongCreature.h \
    src/Scenario/DebugScenario.h \
    src/Model/Entity/Entity.h \
    src/Model/Entity/Food.h \
    src/Model/Model.h \
    src/NeuralNetwork.h \
    src/Model/Entity/Organism/Organism.h \
    src/Simulation.h \
    src/View.h \
    src/constants.h \
    src/utils.h \

INCLUDEPATH += C:\bin\lib\armadillo\include
LIBS += \
    -LC:\bin\lib\armadillo\examples\lib_win64 \
    -llapack_win64_MT \
    -lblas_win64_MT
