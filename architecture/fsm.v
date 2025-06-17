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
    reg [3:0] state, next_state;  // Fixed: Changed from [9:0] to [3:0]
    
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

module top_module (
    input clk,
    input reset,      // Synchronous reset
    input data,
    output reg [3:0] count,    // Fixed: Added 'reg' keyword
    output counting,
    output done,
    input ack );
    
    wire shift_ena;
    reg done_counting;
    reg [3:0] delay;
    
    timer timer_inst(          // Fixed: Added instance name
        .clk(clk), 
        .reset(reset), 
        .data(data), 
        .ack(ack),
        .shift_ena(shift_ena), 
        .counting(counting),
        .done_counting(done_counting), 
        .done(done)
    );
    
    // Fixed: Proper counter logic with done_counting reset
    always @(posedge clk) begin
        if (reset) begin
            count <= 4'd0;
            done_counting <= 1'b0;
        end
        else if (counting) begin
            if (count < ((delay + 4'b1) * 100)) begin
                count <= count + 4'd1;
                done_counting <= 1'b0;
            end
            else begin
                done_counting <= 1'b1;
            end
        end
        else begin
            count <= 4'd0;          // Reset counter when not counting
            done_counting <= 1'b0;   // Reset done flag when not counting
        end
    end
        
    // Shift register for delay value
    always @(posedge clk) begin
        if (reset)
            delay <= 4'd0;
        else if (shift_ena)
            delay <= {delay[2:0], data};  // Fixed: Corrected shift direction
    end
    
endmodule