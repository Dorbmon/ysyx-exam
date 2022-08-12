TOPNAME = ysyx_22041207_top
NXDC_FILES = constr/top.nxdc
INC_PATH ?=

DIFFTEST ?=
RUN_ARGS ?=
VERILATOR = verilator
VERILATOR_CFLAGS += -MMD --build -cc  \
				-O2 --x-assign fast --x-initial fast --noassert --trace
BUILD_DIR = ./build
OBJ_DIR = $(BUILD_DIR)/obj_dir
BIN = $(BUILD_DIR)/$(TOPNAME)
default: $(BIN)
$(shell mkdir -p $(BUILD_DIR))
# 引脚文件
SRC_AUTO_BIND = $(abspath $(BUILD_DIR)/auto_bind.cpp)
$(SRC_AUTO_BIND): $(NXDC_FILES)
	python3 $(NVBOARD_HOME)/scripts/auto_pin_bind.py $^ $@

# VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")
VSRCS = $(shell find $(abspath ./vsrc) -name "*.v")
CSRCS = $(shell find $(abspath ./csrc) -name "*.c" -or -name "*.cc" -or -name "*.cpp")
CSRCS += $(SRC_AUTO_BIND)
include ${NVBOARD_HOME}/scripts/nvboard.mk

INCFLAGS = $(addprefix -I, $(INC_PATH))
CFLAGS += $(INCFLAGS) -DTOP_NAME="\"V$(TOPNAME)\"" $(shell llvm-config --cxxflags) -fPIE -g -O0
LDFLAGS += -lSDL2 -lSDL2_image -lreadline $(shell llvm-config --libs) -ldl
$(BIN): $(VSRCS) $(CSRCS) $(NVBOARD_ARCHIVE)
	@rm -rf $(OBJ_DIR)
	$(VERILATOR) $(VERILATOR_CFLAGS) \
		--top-module $(TOPNAME) $^ \
		$(addprefix -CFLAGS , $(CFLAGS)) $(addprefix -LDFLAGS , $(LDFLAGS)) \
		--Mdir $(OBJ_DIR) --exe -o $(abspath $(BIN))
all: $(BIN)
sim: $(BIN)
	$(call git_commit, "sim RTL") # DO NOT REMOVE THIS LINE!!!
	echo $(RUN_ARGS)
	@$^ $(RUN_ARGS)
clean: 
	rm -rf $(BUILD_DIR)
include ../Makefile
