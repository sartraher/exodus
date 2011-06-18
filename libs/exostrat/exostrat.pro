TEMPLATE = lib
TARGET = exostrat
DESTDIR=../../bin/
DEPENDPATH += ../../3rdParty/fmod/api/inc
INCLUDEPATH += ../../3rdParty/ogre/include \
			   ../../3rdParty/ogre/boost_1_42
QT += opengl
LIBS += -L"../../3rdParty/fmod/api/lib" -lfmodex_vc \
		-L"../../3rdParty/ogre/boost_1_42/lib" -llibboost_thread-vc100-mt-1_42 \
		-L"../../3rdParty/ogre/lib/release" -lOgreMain \
		-L"../../3rdParty/ogre/lib/release" -lOgrePaging \
		-L"../../3rdParty/ogre/lib/release" -lOgreProperty \
		-L"../../3rdParty/ogre/lib/release" -lOgreRTShaderSystem \
		-L"../../3rdParty/ogre/lib/release" -lOgreTerrain 
		
# Input
HEADERS 	+= exostrat.h \
			   ogrewidget.h \
			   exostratapi.h
		   
SOURCES 	+= exostrat.cpp \
			   ogrewidget.cpp