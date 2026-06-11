`timescale 1ns / 1ps

module tb_fread();

    integer fd;
    integer err;
    integer code;
    reg [639: 0] str;
    reg[799: 0] mem [9: 0];

    initial begin
        #10;
        fd = $fopen("data/test_readmem.hex", "r");
        err = $ferror(fd, str);
        if(!err) begin
            // code = $fread(mem, fd, 0, 5);
            code = $fread(mem, fd);
            $display("$fread read num: %0d", code);
            $display("$fread read mem[0]: %s", mem[0]);
            $display("$fread read mem[1]: %s", mem[1]);
            $display("$fread read mem[2]: %s", mem[2]);
            $display("$fread read mem[3]: %s", mem[3]);
            $display("$fread read mem[4]: %s", mem[4]);
            $display("$fread read mem[0][7: 0]: %s", mem[0][7:0]);
            $display("$fread read mem[0][15: 8]: %s", mem[0][15: 8]);
            $display("$fread read mem[0][23: 16]: %s", mem[0][23: 16]);
            $display("$fread read mem[0][31: 24]: %s", mem[0][31: 24]);

        end
        $fclose(fd);
    end

endmodule
