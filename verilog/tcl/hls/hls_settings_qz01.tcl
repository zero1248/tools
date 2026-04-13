# Set FPGA part
set XPART xcku5p-ffvb676-2-e

#! modify this path according to the project location
set PROJ_PATH  "/data/gaoy/u200_proj/wcda_sort"

# Set variables for project
#! type_define.h 与 vitis 工程共用，考虑能不能独立出来（好像不好实现）
set INC_DIR    "${PROJ_PATH}/include"    
set SW_INC_DIR "${PROJ_PATH}/include_hls/sw"
set HW_INC_DIR "${PROJ_PATH}/include/hw"

set SW_SRC_DIR "${PROJ_PATH}/src_hls/sw"
set HW_SRC_DIR "${PROJ_PATH}/src/hw"
set DATA_DIR   "${PROJ_PATH}/data"

set INC_SW     "-I${SW_INC_DIR} -I${INC_DIR}"
set INC_HW     "-I${HW_INC_DIR} -I${INC_DIR}"
set INC_SW_HW  "-I${HW_INC_DIR} -I${SW_INC_DIR} -I${INC_DIR}"


if {![info exists CLKP]} {
  set CLKP 3.33
}




# Set variable to select which steps to execute
set hls_exec 1

