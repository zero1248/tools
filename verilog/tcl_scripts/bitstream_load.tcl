# ============================================================
# Vivado TCL script: program_fpga.tcl
# 功能：通过 JTAG 接口向 FPGA 下载 bitstream
# 用法：在命令行运行：
#   vivado -mode tcl -source program_fpga.tcl -tclargs your_bitstream.bit
# ============================================================

# -----------------------------
# 获取 bit 文件参数
# -----------------------------
# 从命令行参数获取 bit 文件
if { $argc < 1 } {
    puts "Usage: vivado -mode tcl -source bitstream_load.tcl -nojournal -nolog -notrace -tclargs <bitstream_file>"
    exit
}
set bit_file [lindex $argv 0]

# 检查文件是否存在
if { ![file exists $bit_file] } {
    puts "❌ Error: Bitstream file not found: $bit_file"
    exit 1
} else {
    puts "✅ Bitstream file exists: $bit_file"
}

# -----------------------------
# 打开硬件
# -----------------------------
puts "🔌 Connecting to hardware server..."
# 打开硬件会话
open_hw_manager
# 连接硬件服务器 (本地服务器为 localhost:3121)
connect_hw_server -url localhost:3121
# 打开 JTAG 硬件目标
open_hw_target

# 获取第一个 FPGA 设备 (通常是 [lindex ... 0])
set hw_devices [get_hw_devices]
if { [llength $hw_devices] == 0 } {
    puts "❌ Error: No FPGA devices found!"
    exit 1
}
set hw_device [lindex $hw_devices 0]
# 选中 FPGA 设备
current_hw_device $hw_device
puts "✅ Found device: $hw_device"

# -----------------------------
# 设置 bitstream 并下载
# -----------------------------
set_property PROGRAM.FILE $bit_file $hw_device
puts "⏳ Programming FPGA..."

# 使用 catch 捕获下载错误
set result [catch { program_hw_devices $hw_device } errmsg]
if { $result != 0 } {
    puts "❌ FPGA programming failed!"
    puts "Error message: $errmsg"
    exit 1
} else {
    puts "✅ FPGA programming successful!"
}


# -----------------------------
# 退出 Vivado TCL
# -----------------------------
# 断开硬件服务器 (可选)
close_hw_target
disconnect_hw_server

exit