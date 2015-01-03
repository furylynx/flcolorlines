#-------------------------------------------------
#
# Project created by QtCreator 2012-11-24T18:23:37
#
#-------------------------------------------------

QT       += core gui opengl

CONFIG += c++11

LIBS += -lGLU -lglut -lX11 #-lglut  # change this to the right path on system

#LIBS += -L /usr/lib/x86_64-linux-gnu/ -lGLU -lglut  # change this to the right path on system

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = flColorLines
TEMPLATE = app


SOURCES += src/main.cpp\
    src/model/Model.Ball.cpp \
    src/model/Model.Color.cpp \
    src/model/Model.GameField.cpp \
    src/controller/Controller.GameActionController.cpp \
    src/controller/Controller.GameController.cpp \
    src/model/Model.FieldPosition.cpp \
    src/controller/Controller.HighscoreController.cpp \
    src/model/Model.HighscoreEntry.cpp \
    src/model/Model.TimeOperator.cpp \
    src/controller/Controller.RenderThread.cpp \
    src/ui/UI.GLWidget.cpp \
    src/ui/UI.HighscoresFrame.cpp \
    src/ui/UI.MainWindow.cpp \
    src/ui/UI.OptionsFrame.cpp

HEADERS  += \
    src/controller/Controller.RenderThread.hpp \
    src/controller/Controller.HighscoreController.hpp \
    src/controller/Controller.GameController.hpp \
    src/controller/Controller.GameActionController.hpp \
    src/model/Model.AnimationContainer.hpp \
    src/model/Model.Ball.hpp \
    src/model/Model.Color.hpp \
    src/model/Model.FieldPosition.hpp \
    src/model/Model.GameAction.hpp \
    src/model/Model.GameField.hpp \
    src/model/Model.HighscoreEntry.hpp \
    src/model/Model.TimeOperator.hpp \
    src/ui/UI.HighscoresFrame.hpp \
    src/ui/UI.MainWindow.hpp \
    src/ui/UI.OptionsFrame.hpp \
    src/ui/UI.GLWidget.hpp

FORMS    += src/ui/mainwindow.ui \
    src/ui/optionsframe.ui \
    src/ui/highscoreframe.ui \
    src/ui/highscoresframe.ui
