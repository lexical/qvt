######################################################################
# Automatically generated by qmake (1.06c) Thu Sep 9 15:59:32 2004
######################################################################

TEMPLATE = app
DEPENDPATH += lex
INCLUDEPATH += . lex
QMAKE_LIBS += -lutil

# Input
HEADERS += qvtchar.h \
           qvtedit.h \
           qvtptyevent.h \
           qvtptythread.h \
           qvtstring.h \
           qvttext.h \
           lex/lex.h \
           lex/qvttoken.h
SOURCES += qvt.cpp \
           qvtchar.cpp \
           qvtedit.cpp \
           qvtptyevent.cpp \
           qvtptythread.cpp \
           qvtstring.cpp \
           qvttext.cpp \
           lex/lex.N.cc \
           lex/lex.VT.cc
