# Set FPGA part
set XPART xcu200-fsgd2104-2-e

#! modify this path according to the project location
set PROJ_PATH  "/data/gaoy/u200_proj/wcda_sort"

# Set variables for project
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



