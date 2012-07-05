######################################################################
# Automatically generated by qmake (2.01a) ?? 7? 5 00:06:46 2012
######################################################################

TEMPLATE = app
TARGET = 
DEPENDPATH += . language resource src
INCLUDEPATH += . src

# Input
HEADERS += src/convert.h \
           src/generaloption.h \
           src/imgfiledlg.h \
           src/imgfilemodel.h \
           src/loadformats.h \
           src/mainwindow.h \
           src/readerror.h \
           src/resizegrp.h
SOURCES += src/convert.cpp \
           src/generaloption.cpp \
           src/imgfiledlg.cpp \
           src/imgfilemodel.cpp \
           src/loadformats.cpp \
           src/main.cpp \
           src/mainwindow.cpp \
           src/readerror.cpp \
           src/resizegrp.cpp
RESOURCES += resource/resources.qrc
TRANSLATIONS += language/zh_CN.ts


INCLUDEPATH +=  /usr/include/GraphicsMagick
CXXFLAGS += -Wall -g -fno-strict-aliasing -fPIE -fstack-protector --param ssp-buffer-size=4 -D_FORTIFY_SOURCE=2 -Wformat -Wformat-security -Werror=format-security -O2 -pthread
LDFLAGS +=  -L/usr/lib -fPIE -pie -Wl,-z,relro -Wl,-z,now -L/usr/lib/X11 -L/usr/lib -L/usr/lib
if (exists(/usr/lib64)) {
  LIBS += -L/usr/lib64 -lGraphicsMagick++ -lGraphicsMagick -llcms -ltiff -lfreetype -ljasper -ljpeg -lpng -lwmflite -lXext -lSM -lICE -lX11 -lbz2 -lxml2 -lz -lm -lgomp -lpthread -lltdl
}
 else {
  LIBS += -L/usr/lib -lGraphicsMagick++ -lGraphicsMagick -llcms -ltiff -lfreetype -ljasper -ljpeg -lpng -lwmflite -lXext -lSM -lICE -lX11 -lbz2 -lxml2 -lz -lm -lgomp -lpthread -lltdl
 }
