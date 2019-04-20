include compiler.mk

Mode?=Debug

ifeq ($(Mode),Debug)
CC_FLAGS=-std=c++0x -O0 -Wall -g -rdynamic
else
CC_FLAGS=-std=c++0x -Wall
endif

LD_FLAGS:=-shared

FRAMEWORK_DIR=../editorFramework
LIB_DIR = /usr/local/lib:/usr/lib:/usr/lib/i386-linux-gnu
SRC_DIR = ./
INC_DIR=./
PREPROC_DIR=./preprocessor
OBJ_DIR = ./bin/${Mode}
INCLUDE_DIR = -I./
BIN_DIR=./

SRC_FILES = ${SRC_DIR}/cScanner.cpp ${SRC_DIR}/cMacro.cpp ${SRC_DIR}/cMacroCall.cpp ${SRC_DIR}/cMacroInvoker.cpp ${SRC_DIR}/cPreprocessor.cpp

OBJ_FILES = ${OBJ_DIR}/cScanner.o ${OBJ_DIR}/cMacro.o ${OBJ_DIR}/cMacroCall.o ${OBJ_DIR}/cMacroInvoker.o ${OBJ_DIR}/cPreprocessor.o

OBJ_FLEX_FILES = ${OBJ_DIR}/preProcessor.o ${OBJ_DIR}/preProcessorHelper.o

BIN = preProcessor

PREPROC_BISON:
	${BISON} -v -o ${PREPROC_DIR}/preProcessor.tab.cpp -d ${PREPROC_DIR}/preProcessor.ypp

PREPROC_LEX: PREPROC_BISON
	${FLEX} -o ${PREPROC_DIR}/preProcessorHelper.cpp ${PREPROC_DIR}/preProcessor.l
	${CXX} ${INCLUDE_DIR} -g -c ${CC_FLAGS} ${PREPROC_DIR}/preProcessorHelper.cpp -o ${OBJ_DIR}/preProcessorHelper.o
	${CXX} ${INCLUDE_DIR} -g -c ${CC_FLAGS} ${PREPROC_DIR}/preProcessor.tab.cpp -o ${OBJ_DIR}/preProcessor.o

LEXS: PREPROC_LEX

#targets for full compilation chain
${OBJ_DIR}/%.o: ${SRC_DIR}/%.cpp
	${CXX} ${INCLUDE_DIR} -g -c ${CC_FLAGS} $< -o $@

${BIN}: ${OBJ_FILES}
	${LINKER} -L${LIB_DIR} -o $@ ${OBJ_FLEX_FILES} $^ ${LIB}

clean_bin:
	rm -f ${BIN_DIR}/${BIN}

clean_obj:
	rm -rf ${OBJ_FILES}

clean_all: clean_obj clean_bin

build: LEXS ${BIN}

rebuild: clean_all build
