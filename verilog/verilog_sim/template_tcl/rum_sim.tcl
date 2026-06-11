# ============================================================
# Vivado XSim command-line simulation script
#
# Usage:
#   vivado -mode batch -source run_sim.tcl -tclargs <tb_top> [part] [sim_time]
#
# Example:
#   vivado -mode batch -source run_sim.tcl -tclargs tb_sequence_detect xcku5p-ffvb676-2-e 1000ns
# ============================================================

if {$argc < 1} {
    puts "ERROR: Missing tb name!"
    puts "Usage:"
    puts "vivado -mode batch -source run_sim.tcl -tclargs <tb_top> [part] [sim_time]"
    exit 1
}

set TOP_TB [lindex $argv 0]

if {$argc >= 2} {
    set FPGA_PART [lindex $argv 1]
} else {
    set FPGA_PART xcku5p-ffvb676-2-e
}

if {$argc >= 3} {
    set SIM_TIME [lindex $argv 2]
} else {
    set SIM_TIME 1000ns
}

puts "===================================="
puts " Simulation configuration"
puts "------------------------------------"
puts " TOP       : $TOP_TB"
puts " FPGA PART : $FPGA_PART"
puts " SIM TIME  : $SIM_TIME"
puts "===================================="

# ------------------------------------
# Directories
# ------------------------------------
set PROJ_DIR [pwd]

set RTL_DIR  "$PROJ_DIR/src"
set TB_DIR   "$PROJ_DIR/tb"
set SIM_DIR  "$PROJ_DIR/sim"
set WAVE_DIR "$PROJ_DIR/wave"

file mkdir $WAVE_DIR

set RTL_FILES [glob -nocomplain "$RTL_DIR/*.v"]
set TB_FILES  [glob -nocomplain "$TB_DIR/*.v"]

if {[llength $RTL_FILES] == 0} {
    puts "ERROR: No RTL files found in $RTL_DIR"
    exit 1
}

if {[llength $TB_FILES] == 0} {
    puts "ERROR: No testbench files found in $TB_DIR"
    exit 1
}

puts "RTL files:"
puts $RTL_FILES
puts "TB files:"
puts $TB_FILES

# ------------------------------------
# Clean
# ------------------------------------
file delete -force $SIM_DIR
file mkdir $SIM_DIR

# ------------------------------------
# Create project
# ------------------------------------
create_project sim_project \
    $SIM_DIR \
    -part $FPGA_PART \
    -force

# ------------------------------------
# Add RTL and TB
# ------------------------------------
add_files -fileset sources_1 $RTL_FILES
add_files -fileset sim_1     $TB_FILES

# ------------------------------------
# Include directories
# ------------------------------------
set INC_DIRS [list \
    [file normalize "$PROJ_DIR/../common"] \
    [file normalize "$PROJ_DIR/src"] \
    [file normalize "$PROJ_DIR/tb"] \
]

set_property include_dirs $INC_DIRS [get_filesets sources_1]
set_property include_dirs $INC_DIRS [get_filesets sim_1]

# ------------------------------------
# Simulation settings
# ------------------------------------
set_property top $TOP_TB [get_filesets sim_1]

# Prevent Vivado from automatically running simulation time
set_property xsim.simulate.runtime 0ns [get_filesets sim_1]

# Keep internal signals visible
set_property xsim.elaborate.debug_level all [get_filesets sim_1]

# ------------------------------------
# Launch simulation
# ------------------------------------
launch_simulation \
    -simset sim_1 \
    -mode behavioral

# ------------------------------------
# Generate VCD for GTKWave
# ------------------------------------
set USER_VCD "$WAVE_DIR/${TOP_TB}.vcd"

if {[file exists $USER_VCD]} {
    file delete -force $USER_VCD
}

open_vcd $USER_VCD

# Log top-level TB signals
log_vcd /$TOP_TB/*

# Log one-level internal module signals
catch {log_vcd /$TOP_TB/*/*}

# Run simulation
run $SIM_TIME

close_vcd

puts "===================================="
puts " Simulation finished"
puts "------------------------------------"
puts " VCD saved to:"
puts " $USER_VCD"
puts "===================================="

quit