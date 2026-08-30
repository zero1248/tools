# Usage from the project root:
#   vivado -mode batch -source scripts/run_vivado_batch.tcl

set root_dir [file normalize [file dirname [file dirname [info script]]]]
cd $root_dir
file mkdir build/vivado

create_project -force rv32_course_sim build/vivado -part xc7z020clg400-1
set_property target_language Verilog [current_project]

add_files [list \
  rtl/rv32_alu.v \
  rtl/rv32_regfile.v \
  rtl/rv32_immgen.v \
  rtl/rv32_decoder.v \
  rtl/rv32_core_singlecycle.v \
  rtl/simple_soc.v]
add_files -fileset sim_1 tb/tb_soc.v
set_property include_dirs [list [file normalize rtl]] [get_filesets sources_1]
set_property include_dirs [list [file normalize rtl]] [get_filesets sim_1]
set_property top tb_soc [get_filesets sim_1]
set_property generic [list MEM_FILE=[file normalize sw/smoke.hex]] [get_filesets sim_1]
set_property -name {xsim.simulate.runtime} -value {3 us} -objects [get_filesets sim_1]

launch_simulation
run all
quit
