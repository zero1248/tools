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
TB ?= tb_sequence_detect

TB_FILE = $(TB_DIR)/$(TB).v

OUT = $(SIM_DIR)/$(TB).out
VCD = $(WAVE_DIR)/$(TB).vcd
FST = $(WAVE_DIR)/$(TB).fst

# IVERILOG_FLAGS ?= -v
IVERILOG_FLAGS ?=

sim:
	mkdir -p $(SIM_DIR) $(WAVE_DIR)
	$(IVERILOG) $(IVERILOG_FLAGS) -o $(OUT) -I$(COMMON_DIR) $(RTL) $(TB_FILE) 
	$(VVP) $(OUT)

wave: sim
	$(GTKWAVE) $(VCD)

fst: sim
	$(VCD2FST) -Z $(VCD) $(FST)
	$(GTKWAVE) $(FST)

list:
	@echo "Available testbenches:"
	@ls $(TB_DIR)/*.v | xargs -n1 basename | sed 's/.v$$//'

clean:
	rm -rf $(SIM_DIR) $(WAVE_DIR)

.PHONY: sim wave fst list clean