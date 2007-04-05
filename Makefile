#############################################################################
# Makefile for building: hgen
# Generated by qmake (2.01a) (Qt 4.2.3) on: Cz kw 5 17:11:38 2007
# Project:  hgen.pro
# Template: app
# Command: /usr/bin/qmake -unix -o Makefile hgen.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
LEX           = flex
YACC          = yacc
DEFINES       = -DQT_NO_DEBUG -DQT_GUI_LIB -DQT_CORE_LIB
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT  $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT  $(DEFINES)
LEXFLAGS      = 
YACCFLAGS     = -d
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtGui -I/usr/include/qt4 -I. -I. -I.
LINK          = g++
LFLAGS        = 
LIBS          = $(SUBLIBS)  -L/usr/lib -lQtGui -lQtCore -lpthread
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -sf
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = AlternateClusterFilterControl.cpp \
		ClusterFillControl.cpp \
		ClusterFilterControl.cpp \
		ControlPanel.cpp \
		CreateMapDialog.cpp \
		FaultFilterControl.cpp \
		Heightmap.cpp \
		HeightmapCore.cpp \
		HGenMain.cpp \
		LiquidFilterControl.cpp \
		main.cpp \
		MapPreview.cpp \
		MethodSelector.cpp \
		RandomFillControl.cpp \
		SmoothFilterControl.cpp \
		WalkerFilterControl.cpp moc_AlternateClusterFilterControl.cpp \
		moc_ClusterFillControl.cpp \
		moc_ClusterFilterControl.cpp \
		moc_ControlPanel.cpp \
		moc_CreateMapDialog.cpp \
		moc_FaultFilterControl.cpp \
		moc_Heightmap.cpp \
		moc_HGenMain.cpp \
		moc_LiquidFilterControl.cpp \
		moc_MapPreview.cpp \
		moc_MethodSelector.cpp \
		moc_RandomFillControl.cpp \
		moc_SmoothFilterControl.cpp \
		moc_WalkerFilterControl.cpp
OBJECTS       = AlternateClusterFilterControl.o \
		ClusterFillControl.o \
		ClusterFilterControl.o \
		ControlPanel.o \
		CreateMapDialog.o \
		FaultFilterControl.o \
		Heightmap.o \
		HeightmapCore.o \
		HGenMain.o \
		LiquidFilterControl.o \
		main.o \
		MapPreview.o \
		MethodSelector.o \
		RandomFillControl.o \
		SmoothFilterControl.o \
		WalkerFilterControl.o \
		moc_AlternateClusterFilterControl.o \
		moc_ClusterFillControl.o \
		moc_ClusterFilterControl.o \
		moc_ControlPanel.o \
		moc_CreateMapDialog.o \
		moc_FaultFilterControl.o \
		moc_Heightmap.o \
		moc_HGenMain.o \
		moc_LiquidFilterControl.o \
		moc_MapPreview.o \
		moc_MethodSelector.o \
		moc_RandomFillControl.o \
		moc_SmoothFilterControl.o \
		moc_WalkerFilterControl.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		hgen.pro
QMAKE_TARGET  = hgen
DESTDIR       = 
TARGET        = hgen

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: hgen.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/g++.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf
	$(QMAKE) -unix -o Makefile hgen.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/g++.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
qmake:  FORCE
	@$(QMAKE) -unix -o Makefile hgen.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/hgen1.0.0 || $(MKDIR) .tmp/hgen1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/hgen1.0.0/ && $(COPY_FILE) --parents AlternateClusterFilterControl.h ClusterFillControl.h ClusterFilterControl.h ControlPanel.h CreateMapDialog.h FaultFilterControl.h HAction.h Heightmap.h HeightmapCore.h HGenMain.h LiquidFilterControl.h MapControls.h MapPreview.h MethodSelector.h RandomFillControl.h SmoothFilterControl.h WalkerFilterControl.h .tmp/hgen1.0.0/ && $(COPY_FILE) --parents AlternateClusterFilterControl.cpp ClusterFillControl.cpp ClusterFilterControl.cpp ControlPanel.cpp CreateMapDialog.cpp FaultFilterControl.cpp Heightmap.cpp HeightmapCore.cpp HGenMain.cpp LiquidFilterControl.cpp main.cpp MapPreview.cpp MethodSelector.cpp RandomFillControl.cpp SmoothFilterControl.cpp WalkerFilterControl.cpp .tmp/hgen1.0.0/ && (cd `dirname .tmp/hgen1.0.0` && $(TAR) hgen1.0.0.tar hgen1.0.0 && $(COMPRESS) hgen1.0.0.tar) && $(MOVE) `dirname .tmp/hgen1.0.0`/hgen1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/hgen1.0.0


yaccclean:
lexclean:
clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


/usr/bin/moc-qt4:
	(cd $(QTDIR)/src/tools/moc && $(MAKE))

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_AlternateClusterFilterControl.cpp moc_ClusterFillControl.cpp moc_ClusterFilterControl.cpp moc_ControlPanel.cpp moc_CreateMapDialog.cpp moc_FaultFilterControl.cpp moc_Heightmap.cpp moc_HGenMain.cpp moc_LiquidFilterControl.cpp moc_MapPreview.cpp moc_MethodSelector.cpp moc_RandomFillControl.cpp moc_SmoothFilterControl.cpp moc_WalkerFilterControl.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_AlternateClusterFilterControl.cpp moc_ClusterFillControl.cpp moc_ClusterFilterControl.cpp moc_ControlPanel.cpp moc_CreateMapDialog.cpp moc_FaultFilterControl.cpp moc_Heightmap.cpp moc_HGenMain.cpp moc_LiquidFilterControl.cpp moc_MapPreview.cpp moc_MethodSelector.cpp moc_RandomFillControl.cpp moc_SmoothFilterControl.cpp moc_WalkerFilterControl.cpp
moc_AlternateClusterFilterControl.cpp: AlternateClusterFilterControl.h \
		/usr/bin/moc-qt4
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) AlternateClusterFilterControl.h -o moc_AlternateClusterFilterControl.cpp

moc_ClusterFillControl.cpp: ClusterFillControl.h \
		/usr/bin/moc-qt4
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ClusterFillControl.h -o moc_ClusterFillControl.cpp

moc_ClusterFilterControl.cpp: ClusterFilterControl.h \
		/usr/bin/moc-qt4
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ClusterFilterControl.h -o moc_ClusterFilterControl.cpp

moc_ControlPanel.cpp: ControlPanel.h \
		/usr/bin/moc-qt4
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) ControlPanel.h -o moc_ControlPanel.cpp

moc_CreateMapDialog.cpp: CreateMapDialog.h \
		/usr/bin/moc-qt4
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) CreateMapDialog.h -o moc_CreateMapDialog.cpp

moc_FaultFilterControl.cpp: FaultFilterControl.h \
		/usr/bin/moc-qt4
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) FaultFilterControl.h -o moc_FaultFilterControl.cpp

moc_Heightmap.cpp: HeightmapCore.h \
		Heightmap.h \
		/usr/bin/moc-qt4
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) Heightmap.h -o moc_Heightmap.cpp

moc_HGenMain.cpp: HGenMain.h \
		/usr/bin/moc-qt4
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) HGenMain.h -o moc_HGenMain.cpp

moc_LiquidFilterControl.cpp: LiquidFilterControl.h \
		/usr/bin/moc-qt4
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) LiquidFilterControl.h -o moc_LiquidFilterControl.cpp

moc_MapPreview.cpp: Heightmap.h \
		HeightmapCore.h \
		MapPreview.h \
		/usr/bin/moc-qt4
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) MapPreview.h -o moc_MapPreview.cpp

moc_MethodSelector.cpp: MethodSelector.h \
		/usr/bin/moc-qt4
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) MethodSelector.h -o moc_MethodSelector.cpp

moc_RandomFillControl.cpp: RandomFillControl.h \
		/usr/bin/moc-qt4
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) RandomFillControl.h -o moc_RandomFillControl.cpp

moc_SmoothFilterControl.cpp: SmoothFilterControl.h \
		/usr/bin/moc-qt4
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) SmoothFilterControl.h -o moc_SmoothFilterControl.cpp

moc_WalkerFilterControl.cpp: WalkerFilterControl.h \
		/usr/bin/moc-qt4
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) WalkerFilterControl.h -o moc_WalkerFilterControl.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean compiler_image_collection_clean compiler_moc_source_clean compiler_uic_clean 

####### Compile

AlternateClusterFilterControl.o: AlternateClusterFilterControl.cpp AlternateClusterFilterControl.h \
		HAction.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o AlternateClusterFilterControl.o AlternateClusterFilterControl.cpp

ClusterFillControl.o: ClusterFillControl.cpp ClusterFillControl.h \
		HAction.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ClusterFillControl.o ClusterFillControl.cpp

ClusterFilterControl.o: ClusterFilterControl.cpp ClusterFilterControl.h \
		HAction.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ClusterFilterControl.o ClusterFilterControl.cpp

ControlPanel.o: ControlPanel.cpp ControlPanel.h \
		MapControls.h \
		MethodSelector.h \
		RandomFillControl.h \
		ClusterFillControl.h \
		ClusterFilterControl.h \
		AlternateClusterFilterControl.h \
		LiquidFilterControl.h \
		SmoothFilterControl.h \
		WalkerFilterControl.h \
		FaultFilterControl.h \
		HAction.h \
		MapPreview.h \
		Heightmap.h \
		HeightmapCore.h \
		CreateMapDialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ControlPanel.o ControlPanel.cpp

CreateMapDialog.o: CreateMapDialog.cpp CreateMapDialog.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CreateMapDialog.o CreateMapDialog.cpp

FaultFilterControl.o: FaultFilterControl.cpp FaultFilterControl.h \
		HAction.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o FaultFilterControl.o FaultFilterControl.cpp

Heightmap.o: Heightmap.cpp HeightmapCore.h \
		Heightmap.h \
		HAction.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Heightmap.o Heightmap.cpp

HeightmapCore.o: HeightmapCore.cpp HeightmapCore.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o HeightmapCore.o HeightmapCore.cpp

HGenMain.o: HGenMain.cpp HGenMain.h \
		ControlPanel.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o HGenMain.o HGenMain.cpp

LiquidFilterControl.o: LiquidFilterControl.cpp LiquidFilterControl.h \
		HAction.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o LiquidFilterControl.o LiquidFilterControl.cpp

main.o: main.cpp HGenMain.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

MapPreview.o: MapPreview.cpp MapPreview.h \
		Heightmap.h \
		HeightmapCore.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MapPreview.o MapPreview.cpp

MethodSelector.o: MethodSelector.cpp MethodSelector.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MethodSelector.o MethodSelector.cpp

RandomFillControl.o: RandomFillControl.cpp RandomFillControl.h \
		HAction.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o RandomFillControl.o RandomFillControl.cpp

SmoothFilterControl.o: SmoothFilterControl.cpp SmoothFilterControl.h \
		HAction.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o SmoothFilterControl.o SmoothFilterControl.cpp

WalkerFilterControl.o: WalkerFilterControl.cpp WalkerFilterControl.h \
		HAction.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o WalkerFilterControl.o WalkerFilterControl.cpp

moc_AlternateClusterFilterControl.o: moc_AlternateClusterFilterControl.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_AlternateClusterFilterControl.o moc_AlternateClusterFilterControl.cpp

moc_ClusterFillControl.o: moc_ClusterFillControl.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ClusterFillControl.o moc_ClusterFillControl.cpp

moc_ClusterFilterControl.o: moc_ClusterFilterControl.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ClusterFilterControl.o moc_ClusterFilterControl.cpp

moc_ControlPanel.o: moc_ControlPanel.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ControlPanel.o moc_ControlPanel.cpp

moc_CreateMapDialog.o: moc_CreateMapDialog.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_CreateMapDialog.o moc_CreateMapDialog.cpp

moc_FaultFilterControl.o: moc_FaultFilterControl.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_FaultFilterControl.o moc_FaultFilterControl.cpp

moc_Heightmap.o: moc_Heightmap.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_Heightmap.o moc_Heightmap.cpp

moc_HGenMain.o: moc_HGenMain.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_HGenMain.o moc_HGenMain.cpp

moc_LiquidFilterControl.o: moc_LiquidFilterControl.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_LiquidFilterControl.o moc_LiquidFilterControl.cpp

moc_MapPreview.o: moc_MapPreview.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_MapPreview.o moc_MapPreview.cpp

moc_MethodSelector.o: moc_MethodSelector.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_MethodSelector.o moc_MethodSelector.cpp

moc_RandomFillControl.o: moc_RandomFillControl.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_RandomFillControl.o moc_RandomFillControl.cpp

moc_SmoothFilterControl.o: moc_SmoothFilterControl.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_SmoothFilterControl.o moc_SmoothFilterControl.cpp

moc_WalkerFilterControl.o: moc_WalkerFilterControl.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_WalkerFilterControl.o moc_WalkerFilterControl.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

