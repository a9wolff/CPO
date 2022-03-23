# Original makefile from https://www.enib.fr/~harrouet/s4prc/
# Modified by T. Dupuy -- works on both Windows and Ubuntu

#~~~~ control global settings ~~~~
# make opt=2 --> optimization for size + no debug
# make opt=1 --> optimization          + no debug
# make opt=0 --> no optimization       + debug
opt=0
# make clang=1 --> use clang/clang++
# make clang=0 --> use gcc/g++
clang=0
# make no-warn=1 --> disable all warnings
# make no-warn=0 --> enable all warnings
no-warn=0
# make python-only=1 --> only runs python, doesn't run the application
# make python-only=0 --> runs everything
python-only=0

#~~~~ build program ~~~~
EXE_PREFIX=main

#~~~~ detect operating system ~~~~
ifneq (${OS},Windows_NT)
  ifneq (,${findstring Ubuntu,${shell lsb_release -i 2>/dev/null}})
    OS:=Ubuntu
  endif
endif

#~~~~ adjust project-specific settings ~~~~
CFLAGS   =
CPPFLAGS = 
CXXFLAGS =
LDFLAGS  =
BINFLAGS =

# additional include directory  : CPPFLAGS+=-I header/path
# linking precompiled libraries : LDFLAGS+=-L library/path -Wl,-rpath,library/path -l library_name

ifneq (${strip ${python-only}},1)
  GLEWDIR  = dependencies\GLEW
  GLFWDIR  = dependencies\GLFW
  GLMDIR   = dependencies\GLM
  imguiDIR = src/app/imgui

  CPPFLAGS += -I ${GLEWDIR}/include
  CPPFLAGS += -I ${GLFWDIR}/include
  CPPFLAGS += -I ${GLMDIR}/include
  CPPFLAGS += -I ${imguiDIR}

  LDFLAGS  += -L ${GLFWDIR}/lib -Wl,-rpath,${GLFWDIR}/lib -l glfw3 -l gdi32 -l user32 -l kernel32 -l opengl32 -l glu32
endif

#~~~~ source directories ~~~~#
SRC_DIRS = src src/app src/app/shader src/app/glew src/app/imgui src/app/imgui_render

#~~~~ adjust platform-specific features ~~~~
ifneq (,${findstring Windows_NT,${OS}})
  EXE_SUFFIX=.exe
  SKIP_LINE=echo.
  REMOVE=del /q
else
  EXE_SUFFIX=
  SKIP_LINE=echo
  REMOVE=rm -rf
endif

#~~~~ deduce file names ~~~~
MAIN_C_FILES=${foreach d,${SRC_DIRS},${wildcard ${d}/${strip ${EXE_PREFIX}}*.c}}
MAIN_CXX_FILES=${foreach d,${SRC_DIRS},${wildcard ${d}/${strip ${EXE_PREFIX}}*.cpp}}

COMMON_C_FILES=${filter-out ${MAIN_C_FILES},${foreach d,${SRC_DIRS},${wildcard ${d}/*.c}}}
COMMON_CXX_FILES=${filter-out ${MAIN_CXX_FILES},${foreach d,${SRC_DIRS},${wildcard ${d}/*.cpp}}}

MAIN_OBJECT_FILES=${sort ${patsubst %.c,%.o,${MAIN_C_FILES}} \
                         ${patsubst %.cpp,%.o,${MAIN_CXX_FILES}}}
COMMON_OBJECT_FILES=${sort ${patsubst %.c,%.o,${COMMON_C_FILES}} \
                           ${patsubst %.cpp,%.o,${COMMON_CXX_FILES}}}

OBJECT_FILES=${MAIN_OBJECT_FILES} ${COMMON_OBJECT_FILES}
DEPEND_FILES=${patsubst %.o,%.d,${OBJECT_FILES}}

EXE_FILES=${sort ${patsubst %.c,%${EXE_SUFFIX},${MAIN_C_FILES}} \
                 ${patsubst %.cpp,%${EXE_SUFFIX},${MAIN_CXX_FILES}}}

GENERATED_FILES=${DEPEND_FILES} ${OBJECT_FILES} ${EXE_FILES}

GENERATED_FILES+=${wildcard output_* *~}

WINDOWS_GENERATED_FILES:=${subst /,\,${GENERATED_FILES}}

NO_DELETE_OBJECT_FILES  = src\app\imgui\imgui.o src\app\imgui\imgui_demo.o src\app\imgui\imgui_draw.o
NO_DELETE_OBJECT_FILES += src\app\imgui\imgui_impl_glfw.o src\app\imgui\imgui_impl_opengl3.o
NO_DELETE_OBJECT_FILES += src\app\imgui\imgui_tables.o src\app\imgui\imgui_widgets.o

NO_DELETE_OBJECT_FILES += src\app\glew\glew.o src\app\glew\glew.d

ifeq (${OS},Windows_NT)
	GENERATED_FILES=${WINDOWS_GENERATED_FILES}
endif

#~~~~ compiler/linker settings ~~~~
CFLAGS   += -std=c99
CPPFLAGS += -Wall -Wextra -Wshadow -pedantic
CXXFLAGS += -std=c++17 -Wnon-virtual-dtor
LDFLAGS  +=
BINFLAGS +=

# consider these :
# -Wold-style-cast -Wcast-align -Wunused -Woverloaded-virtual -Wpedantic -Wconversion -Wsign-conversion
# -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference
# -Wuseless-cast -Wdouble-promotion -Wformat=2 -Wlifetime

ifeq (${strip ${clang}},1)
  CC=clang
  CXX=clang++
else
  CC=gcc
  CXX=g++
endif

ifneq (,${strip ${MAIN_CXX_FILES} ${COMMON_CXX_FILES}})
  # force c++ link if there is at least one c++ source file
  LD:=${CXX}
else
  LD:=${CC}
endif

#~~~~ debug/optimisation settings ~~~~
ifeq (${strip ${opt}},0)
  BINFLAGS+=-O0 -g
endif
ifeq (${strip ${opt}},1)
  BINFLAGS+=-O3 -s -DNDEBUG
endif
ifeq (${strip ${opt}},2)
  BINFLAGS+=-Os -DNDEBUG
endif

#~~~~ no warnings option ~~~~
ifeq (${strip ${no-warn}},1)
  BINFLAGS+=-w
endif

#~~~~ python-only option ~~~~
ifeq (${strip ${python-only}},1)
  BINFLAGS+=-D PYTHON_ONLY
endif

#~~~~ main target ~~~~
build : ${EXE_FILES}

all : rebuild run

rebuild : clean build clear

.SUFFIXES:
.SECONDARY:
.PHONY: clean clear build rebuild run all

#~~~~ linker command to produce the executable files (if any) ~~~~
%${EXE_SUFFIX} : %.o ${COMMON_OBJECT_FILES}
	@echo ==== linking [opt=${opt}] $@ ====
	${LD} -o $@ $^ ${BINFLAGS} ${LDFLAGS}
	@${SKIP_LINE}

#~~~~ compiler command for every source file ~~~~
%.o : %.c
	@echo ==== compiling [opt=${opt}] $< ====
	${CC} -o $@ $< -c ${BINFLAGS} ${CPPFLAGS} ${CFLAGS}
	@${SKIP_LINE}

%.o : %.cpp
	@echo ==== compiling [opt=${opt}] $< ====
	${CXX} -o $@ $< -c ${BINFLAGS} ${CPPFLAGS} ${CXXFLAGS}
	@${SKIP_LINE}

-include ${DEPEND_FILES}

#~~~~ remove all files ~~~~
clean :
	@echo ==== cleaning ====
	${REMOVE} ${filter-out ${NO_DELETE_OBJECT_FILES},${GENERATED_FILES}}
	@${SKIP_LINE}

#~~~~ remove all files ~~~~
force-clean :
	@echo ==== force-cleaning ====
	${REMOVE} ${GENERATED_FILES}
	@${SKIP_LINE}

#~~~~ remove generated files ~~~~
clear :
	@echo ==== clearing ====
	${REMOVE} ${filter-out ${NO_DELETE_OBJECT_FILES},${filter-out ${subst /,\,${EXE_FILES}},${GENERATED_FILES}}}
	@${SKIP_LINE}

#~~~~ run main file ~~~~
run :
	@echo ==== running ====
	${EXE_FILES}
	@${SKIP_LINE}
