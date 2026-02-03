# Makefile for MinGW-W64 PaceCat library (static)
# (C)2026 Raphael Kim

GCC=gcc
GXX=g++
AR=ar
RL=ranlib

SRC_DIR = sdk
INC_DIR = sdk
OBJ_DIR = obj
BIN_DIR = bin
EPT_DIR = $(BIN_DIR)/include

SAMPLE_DIR = samples
3RDPARTY_DIR = 3rdparty/readerwriterqueue

LIB_NM = pacecat
TARGET_PKG = lib$(LIB_NM).a

SRCS += $(SRC_DIR)/global.cpp
SRCS += $(SRC_DIR)/pacecatlidarsdk.cpp  
SRCS += $(SRC_DIR)/playback.cpp 
SRCS += $(SRC_DIR)/upgrade.cpp

CXXFLAGS += -D_WIN32
CXXFLAGS += -I$(SRC_DIR)
CXXFLAGS += -I$(3RDPARTY_DIR)

LDFLAGS += -lws2_32 -liphlpapi -lmman

LIBOUT =  $(BIN_DIR)/$(TARGET_PKG)

# Make object targets from SRCS.
OBJS = $(SRCS:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

.PHONY: prepare clean exportheaders
.PHONY: CommandControl PlaybackPcap PointCloudAndImu Upgrade

all: prepare continue
samples: CommandControl PlaybackPcap PointCloudAndImu Upgrade

continue: $(BIN_DIR)/$(TARGET_PKG)

prepare:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)

clean:
	@echo "Cleaning built targets ..."
	@rm -rf $(BIN_DIR)/$(TARGET_PKG)
	@rm -rf $(OBJS)

$(OBJS): $(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "Building $@ ... "
	@$(CXX) $(CXXFLAGS) -c $< -o $@

$(LIBOUT): $(OBJS)
	@echo "Generating $@ ..."
	@$(AR) -cr $@ $^
	@$(RL) $@

exportheaders:
	@echo "exporting headers" ...
	@mkdir -p $(EPT_DIR)
	@cp -rf 3rdparty $(EPT_DIR)
	@cp -rf sdk/*.h $(EPT_DIR)

CommandControl: $(SAMPLE_DIR)/CommandControl.cpp $(LIBOUT)
	@echo "Building sample ($@) ..."
	@$(CXX) $(CXXFLAGS) $< -L$(BIN_DIR) -l$(LIB_NM) $(LDFLAGS) -o $(BIN_DIR)/$@

PlaybackPcap: $(SAMPLE_DIR)/PlaybackPcap.cpp $(LIBOUT)
	@echo "Building sample ($@) ..."
	@$(CXX) $(CXXFLAGS) $< -L$(BIN_DIR) -l$(LIB_NM) $(LDFLAGS) -o $(BIN_DIR)/$@

PointCloudAndImu: $(SAMPLE_DIR)/PointCloudAndImu.cpp $(LIBOUT)
	@echo "Building sample ($@) ..."
	@$(CXX) $(CXXFLAGS) $< -L$(BIN_DIR) -l$(LIB_NM) $(LDFLAGS) -o $(BIN_DIR)/$@

Upgrade: $(SAMPLE_DIR)/Upgrade.cpp $(LIBOUT)
	@echo "Building sample ($@) ..."
	@$(CXX) $(CXXFLAGS) $< -L$(BIN_DIR) -l$(LIB_NM) $(LDFLAGS) -o $(BIN_DIR)/$@

