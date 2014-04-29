QMAKE_CXXFLAGS += -std=c++11

QT += \
	widgets

SOURCES += \
    L021/Cursus.cpp \
    L021/Dossier.cpp \
    L021/Ensemble.cpp \
    L021/l021gui.cpp \
    L021/main.cpp \
    L021/UTProfiler.cpp \
    L021/UVDialog.cpp \
    L021/UV.cpp

HEADERS += \
    L021/Cursus.h \
    L021/Dossier.h \
    L021/Ensemble.h \
    L021/l021gui.h \
    L021/UTProfiler.h \
    L021/UVDialog.h \
    L021/Other.hpp \
    L021/UV.hpp

FORMS += \
    L021/AddUV.ui \
    L021/l021gui.ui

OTHER_FILES +=

copydata.commands = $(COPY_DIR) $$PWD/res $$OUT_PWD
first.depends = $(first) copydata
export(first.depends)
export(copydata.commands)
QMAKE_EXTRA_TARGETS += first copydata