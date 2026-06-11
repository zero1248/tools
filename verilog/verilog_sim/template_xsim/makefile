# ============================================================
# Vivado XSIM Makefile
# Flow: xvlog -> xelab -> xsim
# ============================================================

VIVADO_BIN ?=
XVLOG = $(VIVADO_BIN)xvlog
XELAB = $(VIVADO_BIN)xelab
XSIM  = $(VIVADO_BIN)xsim
GTKWAVE = gtkwave
VIVADO = vivado

# ------------------------------------------------------------
# User config
# ------------------------------------------------------------
TB ?= tb_sequence_detect

RTL_DIR = src
TB_DIR  = tb

RTL = $(wildcard $(RTL_DIR)/*.v)
TB  = $(wildcard $(TB_DIR)/*.v)

BUILD_DIR = build
WAVE_DIR  = wave
INC_DIRS = ../common

WDB = $(WAVE_DIR)/$(TB).wdb
VCD = $(WAVE_DIR)/$(TB).vcd

SNAPSHOT = $(TB)_sim
INC_FLAGS = $(addprefix -i ,$(INC_DIRS))


# ------------------------------------------------------------
# Default target
# ------------------------------------------------------------
all: sim


# ------------------------------------------------------------
# Compile Verilog files
# ------------------------------------------------------------
compile:
	mkdir -p $(BUILD_DIR) $(WAVE_DIR)
	$(XVLOG) --work work $(INC_FLAGS) --log $(BUILD_DIR)/xvlog.log $(RTL) $(TB)


# ------------------------------------------------------------
# Elaborate design
# ------------------------------------------------------------
elab: compile
	$(XELAB) $(TB) \
		--snapshot $(SNAPSHOT) \
		--debug typical \
		--log $(BUILD_DIR)/xelab.log


# ------------------------------------------------------------
# Run simulation in batch mode, dump .wdb and .vcd 
# ------------------------------------------------------------
sim: elab
	@echo "log_wave -r /*" > $(BUILD_DIR)/wave_wdb_vcd_auto.tcl
	@echo "open_vcd $(VCD)" >> $(BUILD_DIR)/wave_wdb_vcd_auto.tcl
	@echo "log_vcd /*" >> $(BUILD_DIR)/wave_wdb_vcd_auto.tcl
	@echo "run all" >> $(BUILD_DIR)/wave_wdb_vcd_auto.tcl
	@echo "close_vcd" >> $(BUILD_DIR)/wave_wdb_vcd_auto.tcl
	@echo "quit" >> $(BUILD_DIR)/wave_wdb_vcd_auto.tcl

	$(XSIM) $(SNAPSHOT) \
		--tclbatch $(BUILD_DIR)/wave_wdb_vcd_auto.tcl \
		--wdb $(WDB) \
		--log $(BUILD_DIR)/xsim.log


# ------------------------------------------------------------
# Run simulation in batch mode, dump .wdb only
# ------------------------------------------------------------
wdb: elab
	@echo "log_wave -r /*" > $(BUILD_DIR)/wave_wdb_auto.tcl
	@echo "run all" >> $(BUILD_DIR)/wave_wdb_auto.tcl
	@echo "quit" >> $(BUILD_DIR)/wave_wdb_auto.tcl

	$(XSIM) $(SNAPSHOT) \
		--tclbatch $(BUILD_DIR)/wave_wdb_auto.tcl \
		--wdb $(WDB) \
		--log $(BUILD_DIR)/xsim.log


# ------------------------------------------------------------
# Run simulation and dump .vcd only
# ------------------------------------------------------------
vcd: elab
	@echo "open_vcd $(VCD)" >> $(BUILD_DIR)/wave_vcd_auto.tcl
	@echo "log_vcd /*" >> $(BUILD_DIR)/wave_vcd_auto.tcl
	@echo "run all" >> $(BUILD_DIR)/wave_vcd_auto.tcl
	@echo "close_vcd" >> $(BUILD_DIR)/wave_vcd_auto.tcl
	@echo "quit" >> $(BUILD_DIR)/wave_vcd_auto.tcl

	$(XSIM) $(SNAPSHOT) \
		--tclbatch $(BUILD_DIR)/wave_vcd_auto.tcl \
		--log $(BUILD_DIR)/xsim_vcd.log


# ------------------------------------------------------------
# Open waveform GUI in Vivado
# ------------------------------------------------------------
wave_wdb: 
	$(XSIM) --gui $(WDB)
	# $(VIVADO) $(WDB)


# ------------------------------------------------------------
# Open waveform GUI in gtkwave
# ------------------------------------------------------------
wave_vcd: 
	$(GTKWAVE) $(VCD)


# ------------------------------------------------------------
# Clean generated files
# ------------------------------------------------------------
clean:
	rm -rf $(BUILD_DIR) $(WAVE_DIR)
	rm -rf xsim.dir .Xil work
	rm -f *.jou *.log *.pb *.wdb

.PHONY: all compile elab sim vcd wdb wave_wdb wave_vcd clean