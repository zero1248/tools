source ./tcl/hls_settings_u200.tcl

set PROJ "hls_proj_u200"
set SOLN "sol1"


open_project -reset $PROJ

#! add hardware files
# The content after cflags should be caused by "", no matter how many sentences
add_files "${HW_SRC_DIR}/data_mover.cpp" -cflags ${INC_HW}
add_files "${HW_SRC_DIR}/calc_coordinates.cpp" -cflags ${INC_SW_HW}
add_files "${HW_SRC_DIR}/insert_sort.cpp" -cflags ${INC_SW_HW}
add_files "${HW_SRC_DIR}/search_plateau.cpp" -cflags ${INC_SW_HW}
# add_files "${HW_SRC_DIR}/kernel_all_n_area_multirun.cpp" -cflags ${INC_SW_HW}
add_files "${HW_SRC_DIR}/kernel_all_n_area.cpp" -cflags ${INC_SW_HW}
add_files "${HW_SRC_DIR}/kernel_sort.cpp" -cflags ${INC_SW_HW}

#! add software files
add_files "${SW_SRC_DIR}/hls_main.cpp" -cflags ${INC_SW_HW}
add_files "${SW_SRC_DIR}/hls_test_kernel.cpp" -cflags ${INC_SW_HW}
add_files "${SW_SRC_DIR}/hls_utility.cpp" -cflags ${INC_SW}
add_files "${SW_SRC_DIR}/hls_sw_calc.cpp" -cflags ${INC_SW_HW}
add_files "${SW_SRC_DIR}/hls_sw_sort.cpp" -cflags ${INC_SW}
add_files "${SW_SRC_DIR}/hls_sw_search.cpp" -cflags ${INC_SW}


#! set testbench
# add_files -tb "${SW_SRC_DIR}/hls_main.cpp" -cflags ${INC_SW_HW}  -csimflags "-DHLS_PROJ"
add_files -tb "${SW_SRC_DIR}/hls_main.cpp" -cflags ${INC_SW_HW}
add_files -tb "${DATA_DIR}/calc_input_t_177.txt"
add_files -tb "${DATA_DIR}/calc_input_id_177.txt"

#! set top function
set_top kernel_fpga


open_solution -reset -flow_target vitis $SOLN
# vivdado IP flow
#open_solution -flow_target vivado $SOLN
set_part $XPART
create_clock -period $CLKP

# csim_design -ldflags "lOpenCL"
csim_design
# #! Set any optimization directives
# #! End of directives
# csynth_design
# cosim_design -trace_level all
# export_design


# # Set variable to select which steps to execute
# set hls_exec 1
# if {$hls_exec == 1} {
# 	# Run Synthesis and Exit
# 	csynth_design
# } elseif {$hls_exec == 2} {
# 	# Run Synthesis, RTL Simulation and Exit
# 	csynth_design
# 	cosim_design -trace_level all
# } elseif {$hls_exec == 3} { 
# 	# Run Synthesis, RTL Simulation, RTL implementation and Exit
# 	csynth_design
# 	cosim_design 
# 	export_design
#     # export_design -rtl verilog -format ip_catalog
# } else {
# 	# Default is to exit after running csynth
# 	# csynth_design
# }

exit














