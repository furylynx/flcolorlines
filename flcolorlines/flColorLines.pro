#-------------------------------------------------
#
# flColorLines
#   3D implementation of the game ColorLines
#
#   by furylynx
#
#-------------------------------------------------

# qt definitions
QT += core gui opengl

# use widgets if qt is greater than 4
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

# win/unix definitions
win32:CONFIG(release, debug|release){
    win32-g++:contains(QMAKE_HOST.arch, x86_64){

        #win 64 release
        message( "Building RELEASE for WIN 64 bit")

        #DESTDIR = win64release
        LIBS += -Llib/win64/bin/ -lfreeglut
        INCLUDEPATH += . lib/win64/include/

        # dlls to be copied to destination
        MY_LIB_FILES += lib/win64/bin/freeglut.dll

    }else{

        #win 32 release
        message( "Building RELEASE for WIN 32 bit")

        #DESTDIR = win32release
        LIBS += -Llib/win32/bin/ -lfreeglut
        INCLUDEPATH += . lib/win32/include/

        # dlls to be copied to destination
        MY_LIB_FILES += lib/win32/bin/freeglut.dll
    }

    # copy dll to destination path
    extra_libs.files = MY_LIB_FILES
    extra_libs.path = $$DESTDIR

}else:win32:CONFIG(debug, debug|release){
    win32-g++:contains(QMAKE_HOST.arch, x86_64){

        #win 64 debug
        message( "Building DEBUG for WIN 64 bit")

        #DESTDIR = win64debug
        LIBS += -Llib/win64/bin/ -lfreeglut
        INCLUDEPATH += . lib/win64/include/

        # dlls to be copied to destination
        MY_LIB_FILES += lib/win64/bin/freeglut.dll

    }else{
message( "Building for 32 bit")

        #win 32 debug
        message( "Building DEBUG for WIN 32 bit")

        #DESTDIR = win32debug
        LIBS += -Llib/win32/bin/-lfreeglut
        INCLUDEPATH += . lib/win32/include/

        # dlls to be copied to destination
        MY_LIB_FILES += lib/win32/bin/freeglut.dll

    }

    # copy dll to destination path
    extra_libs.files = MY_LIB_FILES
    extra_libs.path = $$DESTDIR

}else:unix::CONFIG(release, debug|release){
    contains(QMAKE_HOST.arch, x86_64){
        # 64-bit Unix

        #DESTDIR = unix64release
        LIBS += -lGLU -lglut -lX11
    }else{
        # 32-bit Unix

        #DESTDIR = unix32release
        LIBS += -lGLU -lglut -lX11
    }
}else:unix::CONFIG(debug, debug|release){
    contains(QMAKE_HOST.arch, x86_64){
        # 64-bit Unix

        #DESTDIR = unix64debug
        LIBS += -lGLU -lglut -lX11
    }else{
        # 32-bit Unix

        #DESTDIR = unix32debug
        LIBS += -lGLU -lglut -lX11
    }
}

# use the c++11 standard
CONFIG += c++11


# target name
TARGET = flColorLines

# template type: application
TEMPLATE = app


# sources/headers/forms to be used
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
    src/ui/UI.OptionsFrame.cpp \
    src/model/timespec.cpp

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
    src/ui/UI.GLWidget.hpp \
    src/model/timespec.hpp

FORMS    += src/ui/mainwindow.ui \
    src/ui/optionsframe.ui \
    src/ui/highscoreframe.ui \
    src/ui/highscoresframe.ui
