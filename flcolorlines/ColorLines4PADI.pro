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


SOURCES += main.cpp\
        mainwindow.cpp \
    Model.Ball.cpp \
    Model.Color.cpp \
    Model.GameField.cpp \
    Controller.GameActionController.cpp \
    Controller.GameController.cpp \
    Model.FieldPosition.cpp \
    optionsframe.cpp \
    examplerenderthread.cpp \
    exampleglwidget.cpp \
    Controller.HighscoreController.cpp \
    Model.HighscoreEntry.cpp \
    Model.TimeOperator.cpp \
    highscoresframe.cpp

HEADERS  += mainwindow.h \
    Model.Color.h \
    Model.GameField.h \
    Model.Ball.h \
    Model.FieldPosition.h \
    Controller.GameController.h \
    Model.GameAction.h \
    Controller.GameActionController.h \
    optionsframe.h \
    examplerenderthread.h \
    exampleglwidget.h \
    Model.HighscoreEntry.h \
    Controller.HighscoreController.h \
    Model.TimeOperator.h \
    highscoresframe.h \
    Model.AnimationContainer.h

FORMS    += mainwindow.ui \
    optionsframe.ui \
    highscoreframe.ui \
    highscoresframe.ui
