#-------------------------------------------------
#
# Project created by QtCreator 2012-11-24T18:23:37
#
#-------------------------------------------------

QT       += core gui opengl

LIBS += -lGLU -lglut#-lglut  # change this to the right path on system

#LIBS += -L /usr/lib/x86_64-linux-gnu/ -lGLU -lglut  # change this to the right path on system

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ColorLines4PADI
TEMPLATE = app


SOURCES += src/main.cpp\
        src/ui/mainwindow.cpp \
    src/model/Model.Ball.cpp \
    src/model/Model.Color.cpp \
    src/model/Model.GameField.cpp \
    src/controller/Controller.GameActionController.cpp \
    src/controller/Controller.GameController.cpp \
    src/model/Model.FieldPosition.cpp \
    src/ui/optionsframe.cpp \
    src/controller/examplerenderthread.cpp \
    src/ui/exampleglwidget.cpp \
    src/controller/Controller.HighscoreController.cpp \
    src/model/Model.HighscoreEntry.cpp \
    src/model/Model.TimeOperator.cpp \
    src/ui/highscoresframe.cpp

HEADERS  += src/ui/mainwindow.h \
    src/model/Model.Color.h \
    src/model/Model.GameField.h \
    src/model/Model.Ball.h \
    src/model/Model.FieldPosition.h \
    src/controller/Controller.GameController.h \
    src/model/Model.GameAction.h \
    src/controller/Controller.GameActionController.h \
    src/ui/optionsframe.h \
    src/controller/examplerenderthread.h \
    src/ui/exampleglwidget.h \
    src/model/Model.HighscoreEntry.h \
    src/controller/Controller.HighscoreController.h \
    src/model/Model.TimeOperator.h \
    src/ui/highscoresframe.h \
    src/model/Model.AnimationContainer.h

FORMS    += src/ui/mainwindow.ui \
    src/ui/optionsframe.ui \
    src/ui/highscoreframe.ui \
    src/ui/highscoresframe.ui
