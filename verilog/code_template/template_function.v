// 函数只能在模块中定义，位置任意，并在模块的任何地方引用，作用范围也局限于此模块。函数主要有以下几个特点：
// 1）不能含有任何延迟、时序或时序控制逻辑（#、@、wait 等）
// 2）至少有一个输入变量
// 3）只有一个返回值，且没有输出
// 4）不含有非阻塞赋值语句
// 5）函数可以调用其他函数，但是不能调用任务
// 函数的典型应用场景式组合逻辑计算（如位操作、数学运算）

// 无参数函数
// 在 function 定义中，函数名就是返回值
function [返回类型] 函数名;
    // 输入参数（可选）
    input [位宽] 参数名;
    // 内部变量声明
    reg [位宽] 变量;
begin
    // 逻辑代码
    函数名 = 计算结果; // 必须赋值给函数名
end
endfunction




// 统计有多少个 1, 用 flatten_ones 相反
// 输入参数可以用括号括起来
// 返回值可以用 automatic 参数替代，以支持不确定长度的返回值
function automatic integer count_ones(input [7: 0] num_in);
    integer result;
    begin
        result = 0;
        while(num_in != 8'h00) begin 
            num_in = num_in >> 1;
            result = result + 1;
        end
        count_ones = result;
    end
endfunction

// 大小端转换
function [AXIS_TDATA_WIDTH-1: 0] endian_trans(input [AXIS_TDATA_WIDTH-1: 0] data);
    integer i;
    reg [7: 0] tmp;
    begin
        i = 0;
        while(i < (AXIS_TDATA_WIDTH)/8/2) begin
            tmp = data[(i*8)+: 8];   
            data[(i*8)+: 8] = data[(AXIS_TDATA_WIDTH-1 -i*8)-: 8];
            data[(AXIS_TDATA_WIDTH-1 -i*8)-: 8] = tmp;
            i = i + 1;
        end
        endian_trans = data;
    end
endfunction
















