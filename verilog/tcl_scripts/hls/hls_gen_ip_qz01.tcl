source ./tcl/hls_settings_qz01.tcl

set PROJ "hls_proj_qz01"
set SOLN "sol1"


open_project -reset $PROJ

#! add hardware files
# The content after cflags should be caused by "", no matter how many sentences
add_files "${HW_SRC_DIR}/data_mover.cpp" -cflags ${INC_HW}
add_files "${HW_SRC_DIR}/calc_coordinates.cpp" -cflags ${INC_SW_HW}
add_files "${HW_SRC_DIR}/insert_sort.cpp" -cflags ${INC_SW_HW}
add_files "${HW_SRC_DIR}/search_plateau.cpp" -cflags ${INC_SW_HW}
add_files "${HW_SRC_DIR}/kernel_all_hls_ip.cpp" -cflags ${INC_SW_HW}

#! add software files
add_files "${SW_SRC_DIR}/hls_main.cpp" -cflags ${INC_SW_HW} -csimflags "-DHLS_PROJ"
add_files "${SW_SRC_DIR}/hls_test_kernel.cpp" -cflags ${INC_SW_HW} -csimflags "-DHLS_PROJ"
#! 添加宏定义是为了与 vitis 工程共用 host_utility.hpp/cpp 文件，在 vitis 工程中需要用到 opencl 库
#! type_define 中有一部分 hls 的内容，所以暂时还不能去掉这个宏，后面看看能不能把类型定义也单独放到一个文件里面
add_files "${SW_SRC_DIR}/hls_utility.cpp" -cflags ${INC_SW} -csimflags "-DHLS_PROJ"
add_files "${SW_SRC_DIR}/hls_sw_calc.cpp" -cflags ${INC_SW_HW} -csimflags "-DHLS_PROJ"
add_files "${SW_SRC_DIR}/hls_sw_sort.cpp" -cflags ${INC_SW} -csimflags "-DHLS_PROJ"
add_files "${SW_SRC_DIR}/hls_sw_search.cpp" -cflags ${INC_SW} -csimflags "-DHLS_PROJ"

#! set testbench
add_files -tb "${SW_SRC_DIR}/hls_main.cpp" -cflags ${INC_SW_HW}  -csimflags "-DHLS_PROJ"
add_files -tb "${DATA_DIR}/calc_input_t_177.txt"
add_files -tb "${DATA_DIR}/calc_input_id_177.txt"

#! set top function
set_top kernel_fpga


open_solution -reset -flow_target vitis $SOLN
# vivdado IP flow
#open_solution -flow_target vivado $SOLN
set_part $XPART
create_clock -period $CLKP

csim_design
# csim_design -ldflags "lOpenCL"
# Set any optimization directives
# End of directives

if {$hls_exec == 1} {
	# Run Synthesis and Exit
	csynth_design
} elseif {$hls_exec == 2} {
	# Run Synthesis, RTL Simulation and Exit
	csynth_design
	cosim_design -trace_level all
} elseif {$hls_exec == 3} { 
	# Run Synthesis, RTL Simulation, RTL implementation and Exit
	csynth_design
	cosim_design 
	export_design
    # export_design -rtl verilog -format ip_catalog
} else {
	# Default is to exit after running csynth
	# csynth_design
}

exit
