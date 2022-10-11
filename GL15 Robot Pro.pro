#-------------------------------------------------
#
# Project created by QtCreator 2022-05-28T17:39:36
#
#-------------------------------------------------

QT       += core gui
QT       += opengl
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GL03

TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
    circle.cpp \
    global.cpp \
       	main.cpp \
       	mainwindow.cpp \
       	gltest.cpp\
      	coordinate.cpp\
       	mesh.cpp\
	model.cpp \
    posture.cpp \
    robot.cpp\
    line.cpp \
    setting.cpp \
    trajectory.cpp

HEADERS += \
    circle.h \
    global.h \
        mainwindow.h \
	gltest.h\
   	camera.h\
   	coordinate.h\
    	mesh.h\
	model.h \
    posture.h \
    robot.h\
    line.h \
    setting.h \
    trajectory.h

FORMS += \
        mainwindow.ui \
        setting.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS+=-lopengl32 -lglu32



RESOURCES += \
    res.qrc


win32: LIBS += -L$$PWD/./ -llibassimp.dll

INCLUDEPATH += $$PWD/assimp
DEPENDPATH += $$PWD/assimp
