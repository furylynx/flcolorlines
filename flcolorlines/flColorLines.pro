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
    win32-g++:contains(QMAKE_TARGET.arch, x86_64){

        #win 64 release
        message( "Building RELEASE for WIN 64 bit")

        DESTDIR = $$PWD/win64release/
        RCC_DIR = $$PWD/win64release-src/
        OBJECTS_DIR = $$PWD/win64release-src/
        MOC_DIR = $$PWD/win64release-src/
        UI_DIR = $$PWD/win64release-src/

        LIBS += -L$$PWD/lib/win64/lib/ -lfreeglut -lglut32 -lopengl32 -lglu32
        INCLUDEPATH += . $$PWD/lib/win64/include/

        # dlls to be copied to destination
        MY_LIB_FILES += $$PWD/lib/win64/bin/freeglut.dll
        MY_LIB_FILES += $$PWD/lib/win64/copying_freeglut.txt

        #qmake flags for a static build as it is required for freeglut with mingw
        QMAKE_LFLAGS += -static
        QMAKE_LFLAGS += -static-libgcc
        QMAKE_LFLAGS += -static-libstdc++
        QMAKE_LFLAGS += -mwindows

    }else{

        #win 32 release
        message( "Building RELEASE for WIN 32 bit")

        DESTDIR = $$PWD/win32release/
        RCC_DIR = $$PWD/win32release-src/
        OBJECTS_DIR = $$PWD/win32release-src/
        MOC_DIR = $$PWD/win32release-src/
        UI_DIR = $$PWD/win32release-src/

        LIBS += -L$$PWD/lib/win32/lib/ -lfreeglut -lglut32 -lopengl32 -lglu32
        INCLUDEPATH += . $$PWD/lib/win32/include/

        # dlls to be copied to destination
        MY_LIB_FILES += $$PWD/lib/win32/bin/freeglut.dll
        MY_LIB_FILES += $$PWD/lib/win32/copying_freeglut.txt

        #qmake flags for a static build as it is required for freeglut with mingw
        QMAKE_LFLAGS += -static
        QMAKE_LFLAGS += -static-libgcc
        QMAKE_LFLAGS += -static-libstdc++
        QMAKE_LFLAGS += -mwindows
    }

    # copy dll to destination path
    extra_libs.files = MY_LIB_FILES
    extra_libs.path = $$DESTDIR

}else:win32:CONFIG(debug, debug|release){
    win32-g++:contains(QMAKE_TARGET.arch, x86_64){

        #win 64 debug
        message( "Building DEBUG for WIN 64 bit")

        DESTDIR = $$PWD/win64debug/
        RCC_DIR = $$PWD/win64debug-src/
        OBJECTS_DIR = $$PWD/win64debug-src/
        MOC_DIR = $$PWD/win64debug-src/
        UI_DIR = $$PWD/win64debug-src/

        LIBS += -L$$PWD/lib/win64/bin/ -lfreeglut -lglut32 -lopengl32 -lglu32
        INCLUDEPATH += . $$PWD/lib/win64/include/

        # dlls to be copied to destination
        MY_LIB_FILES += $$PWD/lib/win64/bin/freeglut.dll
        MY_LIB_FILES += $$PWD/lib/win64/copying_freeglut.txt

        #qmake flags for a static build as it is required for freeglut with mingw
        QMAKE_LFLAGS += -static
        QMAKE_LFLAGS += -static-libgcc
        QMAKE_LFLAGS += -static-libstdc++
        QMAKE_LFLAGS += -mwindows

    }else{

        #win 32 debug
        message( "Building DEBUG for WIN 32 bit")

        DESTDIR = $$PWD/win32debug/
        RCC_DIR = $$PWD/win32debug-src/
        OBJECTS_DIR = $$PWD/win32debug-src/
        MOC_DIR = $$PWD/win32debug-src/
        UI_DIR = $$PWD/win32debug-src/

        LIBS += -L$$PWD/lib/win32/lib/ -lfreeglut -lglut32 -lopengl32 -lglu32
        INCLUDEPATH += . $$PWD/lib/win32/include/

        # dlls to be copied to destination
        MY_LIB_FILES += $$PWD/lib/win32/bin/freeglut.dll
        MY_LIB_FILES += $$PWD/lib/win32/copying_freeglut.txt

        #qmake flags for a static build as it is required for freeglut with mingw
        QMAKE_LFLAGS += -static
        QMAKE_LFLAGS += -static-libgcc
        QMAKE_LFLAGS += -static-libstdc++
        QMAKE_LFLAGS += -mwindows

    }

    # copy dll to destination path
    extra_libs.files = MY_LIB_FILES
    extra_libs.path = $$DESTDIR

}else:unix::CONFIG(release, debug|release){
    contains(QMAKE_HOST.arch, x86_64){

        # 64-bit Unix
        message( "Building RELEASE for UNIX 64 bit")

        DESTDIR = $$PWD/unix64release/
        RCC_DIR = $$PWD/unix64release-src/
        OBJECTS_DIR = $$PWD/unix64release-src/
        MOC_DIR = $$PWD/unix64release-src/
        UI_DIR = $$PWD/unix64release-src/

        LIBS += -lGLU -lglut -lX11
    }else{

        # 32-bit Unix
        message( "Building RELEASE for UNIX 32 bit")

        DESTDIR = $$PWD/unix32release/
        RCC_DIR = $$PWD/unix32release-src/
        OBJECTS_DIR = $$PWD/unix32release-src/
        MOC_DIR = $$PWD/unix32release-src/
        UI_DIR = $$PWD/unix32release-src/

        LIBS += -lGLU -lglut -lX11
    }
}else:unix::CONFIG(debug, debug|release){
    contains(QMAKE_HOST.arch, x86_64){

        # 64-bit Unix
        message( "Building DEBUG for UNIX 64 bit")

        DESTDIR = $$PWD/unix64debug/
        RCC_DIR = $$PWD/unix64debug-src/
        OBJECTS_DIR = $$PWD/unix64debug-src/
        MOC_DIR = $$PWD/unix64debug-src/
        UI_DIR = $$PWD/unix64debug-src/

        LIBS += -lGLU -lglut -lX11
    }else{

        # 32-bit Unix
        message( "Building DEBUG for UNIX 32 bit")

        DESTDIR = $$PWD/unix32debug/
        RCC_DIR = $$PWD/unix32debug-src/
        OBJECTS_DIR = $$PWD/unix32debug-src/
        MOC_DIR = $$PWD/unix32debug-src/
        UI_DIR = $$PWD/unix32debug-src/

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
