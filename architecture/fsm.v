module timer (
    input clk,
    input reset,      // Synchronous reset
    input data,
    output shift_ena,
    output counting,
    input done_counting,
    output done,
    input ack );
    
    parameter s = 4'd0, s1 = 4'd1, s3 = 4'd2, s6 = 4'd3;
    parameter b0 = 4'd4, b1 = 4'd5, b2 = 4'd6, b3 = 4'd7, count = 4'd8, Wait = 4'd9;
    reg [3:0] state, next_state;
    
    always @(*) begin
        case (state)
            s: next_state = data ? s1 : s;
            s1: next_state = data ? s3 : s;
            s3: next_state = data ? s3 : s6;
            s6: next_state = data ? b0 : s;
            b0: next_state = b1;
            b1: next_state = b2;
            b2: next_state = b3;
            b3: next_state = count;
            count: next_state = done_counting ? Wait : count;
            Wait: next_state = ack ? s : Wait;
            default: next_state = s;
        endcase
    end
    
    always @(posedge clk) begin
        if (reset)
            state <= s;
        else
            state <= next_state;
    end
    
    assign shift_ena = (state == b0) || (state == b1) || (state == b2) || (state == b3);
    assign counting = (state == count);
    assign done = (state == Wait);
    
endmodule

module delayer (
    input clk,
    input reset,
    input counting,
    output reg [9:0] q,
    output count_down);
    
    always @(posedge clk) begin
        if (reset)
            q <= 10'd0;
        else if (q == 999)
            q <= 10'd0;
        else if (counting)
            q <= q + 10'd1;
    end
    
    assign count_down = (q == 10'd999);
endmodule

module shift_count(
    input clk,
    input shift_ena,
    input count_ena,
    input data,
    output reg [3:0] q);
    
    always @(posedge clk) begin
        if (shift_ena)
            q <= {q[2:0], data};
        else if (count_ena && q != 4'd0)  // Only decrement if not zero
            q <= q - 4'd1;
    end
endmodule

module top_module (
    input clk,
    input reset,      // Synchronous reset
    input data,
    output [3:0] count,
    output counting,
    output done,
    input ack );
    
    wire shift_ena;
    wire done_counting, count_down;
    wire [9:0] q1;
    
    timer timer_inst(
        .clk(clk), 
        .reset(reset), 
        .data(data), 
        .ack(ack),
        .shift_ena(shift_ena), 
        .counting(counting),
        .done_counting(done_counting), 
        .done(done)
    );
    
    shift_count shift_count_inst(
        .clk(clk),
        .shift_ena(shift_ena),
        .count_ena(count_down),
        .data(data),
        .q(count)
    );
    
    delayer delayer_inst(
        .clk(clk),
        .reset(reset || !counting),  
        .counting(counting),
        .q(q1),
        .count_down(count_down)
    );
    
    assign done_counting = (count == 4'd0) && count_down;
        
endmodule