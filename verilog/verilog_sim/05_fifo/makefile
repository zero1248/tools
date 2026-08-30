IVERILOG = iverilog
VVP      = vvp
GTKWAVE = gtkwave
VCD2FST = vcd2fst

SRC_DIR  = src
TB_DIR   = tb
SIM_DIR  = sim
WAVE_DIR = wave
COMMON_DIR = "../common"

RTL = $(wildcard $(SRC_DIR)/*.v)

# 默认 testbench
TOP ?= tb_sequence_detect

# 自动识别 testbench 文件类型
TOP_V_FILE  = $(TB_DIR)/$(TOP).v
TOP_SV_FILE = $(TB_DIR)/$(TOP).sv

ifeq ($(wildcard $(TOP_SV_FILE)),$(TOP_SV_FILE))
    TOP_FILE = $(TOP_SV_FILE)
    IVERILOG_FLAGS  += -g2012
else
    TOP_FILE = $(TOP_V_FILE)
    IVERILOG_FLAGS  =
endif

OUT = $(SIM_DIR)/$(TOP).out
VCD = $(WAVE_DIR)/$(TOP).vcd
FST = $(WAVE_DIR)/$(TOP).fst

# 加上 -v 输出信息更详细
# IVERILOG_FLAGS += -v

sim:
	mkdir -p $(SIM_DIR) $(WAVE_DIR)
	$(IVERILOG) -s $(TOP) $(IVERILOG_FLAGS) -o $(OUT) -I$(COMMON_DIR) $(RTL) $(TOP_FILE) 
	$(VVP) $(OUT)

wave:
	$(GTKWAVE) $(VCD)

fst: 
	$(VCD2FST) -Z $(VCD) $(FST)
	$(GTKWAVE) $(FST)

list:
	@echo "Available testbenches:"
	@ls $(TB_DIR)/*.v | xargs -n1 basename | sed 's/.v$$//'

clean:
	rm -rf $(SIM_DIR) $(WAVE_DIR)

.PHONY: sim wave fst list clean
