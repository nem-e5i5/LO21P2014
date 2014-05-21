QMAKE_CXXFLAGS += -std=c++11

QT += \
	widgets

FORMS += \
    L021/AddUV.ui \
    L021/l021gui.ui

HEADERS += \
    L021/AllUtility.h \
    L021/Cursus.h \
    L021/Dossier.h \
    L021/Ensemblist.h \
    L021/l021gui.h \
    L021/Other.hpp \
    L021/UTProfiler.h \
    L021/UV.hpp \
    L021/UVDialog.h \
    L021/Ensemblist_lin.h \
    L021/Ensemblist_win.h

SOURCES += \
    L021/Cursus.cpp \
    L021/Dossier.cpp \
    L021/Ensemblist.cpp \
    L021/l021gui.cpp \
    L021/main.cpp \
    L021/UTProfiler.cpp \
    L021/UV.cpp \
    L021/UVDialog.cpp
