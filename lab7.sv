//-------------------------------------------------------------------------
//      ECE 385 - Summer 2021 Lab 7 Top-level                            --
//                                                                       --
//      Updated Fall 2021 as Lab 7                                       --
//      For use with ECE 385                                             --
//      UIUC ECE Department                                              --
//-------------------------------------------------------------------------


module lab7 (

      ///////// Clocks /////////
      input    MAX10_CLK1_50,

      ///////// KEY /////////
      input    [ 1: 0]   KEY,

      ///////// SW /////////
      input    [ 9: 0]   SW,

      ///////// LEDR /////////
      output   [ 9: 0]   LEDR,

      ///////// HEX /////////
      output   [ 7: 0]   HEX0,
      output   [ 7: 0]   HEX1,
      output   [ 7: 0]   HEX2,
      output   [ 7: 0]   HEX3,
      output   [ 7: 0]   HEX4,
      output   [ 7: 0]   HEX5,

      ///////// SDRAM /////////
      output             DRAM_CLK,
      output             DRAM_CKE,
      output   [12: 0]   DRAM_ADDR,
      output   [ 1: 0]   DRAM_BA,
      inout    [15: 0]   DRAM_DQ,
      output             DRAM_LDQM,
      output             DRAM_UDQM,
      output             DRAM_CS_N,
      output             DRAM_WE_N,
      output             DRAM_CAS_N,
      output             DRAM_RAS_N,

      ///////// VGA /////////
      output             VGA_HS,
      output             VGA_VS,
      output   [ 3: 0]   VGA_R,
      output   [ 3: 0]   VGA_G,
      output   [ 3: 0]   VGA_B,

      ///////// ARDUINO /////////
      inout    [15: 0]   ARDUINO_IO,
      inout              ARDUINO_RESET_N 

);

//=======================================================
//  REG/WIRE declarations
//=======================================================
	logic SPI0_CS_N, SPI0_SCLK, SPI0_MISO, SPI0_MOSI, USB_GPX, USB_IRQ, USB_RST;
	logic [3:0] hex_num_3, hex_num_2, hex_num_1, hex_num_0; //4 bit input hex digits
	logic [1:0] signs;
	logic [1:0] hundreds;
	logic [7:0] keycode;
	logic [7:0] debug_sig1, debug_sig2;
	logic i2c_sda_oe, i2c_scl_oe;
	logic i2c_serial_scl_in, i2c_serial_sda_in;
	logic [1:0] aud_mclk_ctr;
//=======================================================
//  Structural coding
//=======================================================
	assign ARDUINO_IO[10] = SPI0_CS_N;
	assign ARDUINO_IO[13] = SPI0_SCLK;
	assign ARDUINO_IO[11] = SPI0_MOSI;
	assign ARDUINO_IO[12] = 1'bZ;
	assign SPI0_MISO = ARDUINO_IO[12];
	assign ARDUINO_IO[14] = i2c_sda_oe ? 1'b0 : 1'bz;
	assign i2c_serial_sda_in = ARDUINO_IO[14];
	assign ARDUINO_IO[15] = i2c_scl_oe ? 1'b0 : 1'bz;
	assign i2c_serial_scl_in = ARDUINO_IO[15];

	logic [31:0] l_out, r_out;
	// ARDUINO_IO[2] is I2S_in ARDUINO_IO[1] is I2S_out
	// ARDUINO_IO[4] is LRCLK
	// ARDUINO_IO[5] is SCLK
	assign ARDUINO_IO[1] = 1'bz;
	assign ARDUINO_IO[4] = 1'bz;
	assign ARDUINO_IO[5] = 1'bz;
//	assign ARDUINO_IO[2] = ARDUINO_IO[1];
	// i2s is moved to Platform Designer
	// i2s i2s(.clk(MAX10_CLK1_50), .rst(Reset_h), .start(1'b0), .lrclk(ARDUINO_IO[4]), .sclk(ARDUINO_IO[5]), .data_out(ARDUINO_IO[2]));
	
	
	assign ARDUINO_IO[9] = 1'bZ;
	assign USB_IRQ = ARDUINO_IO[9];
		
	//Assignments specific to Circuits At Home UHS_20
	assign ARDUINO_RESET_N = USB_RST;
	assign ARDUINO_IO[8] = 1'bZ;
	//GPX is unconnected to shield, not needed for standard USB host - set to 0 to prevent interrupt
	assign USB_GPX = 1'b0;
	
	//HEX drivers to convert numbers to HEX output
	HexDriver hex_driver5 (debug_sig1, HEX5[6:0]);
	assign HEX5[7] = 1'b1;

	HexDriver hex_driver4 (debug_sig2, HEX4[6:0]);
	assign HEX4[7] = 1'b1;

	HexDriver hex_driver3 (hex_num_3, HEX3[6:0]);
	assign HEX3[7] = 1'b1;
	
	HexDriver hex_driver2 (hex_num_2, HEX2[6:0]);
	assign HEX2[7] = 1'b1;
	
	HexDriver hex_driver1 (hex_num_1, HEX1[6:0]);
	assign HEX1[7] = 1'b1;
	
	HexDriver hex_driver0 (hex_num_0, HEX0[6:0]);
	assign HEX0[7] = 1'b1;
	
	assign ARDUINO_IO[3] = aud_mclk_ctr[1];	 //generate 12.5MHz CODEC mclk
	always_ff @(posedge MAX10_CLK1_50) begin
		aud_mclk_ctr <= aud_mclk_ctr + 1;
	end


	
	
	assign {Reset_h}=~ (KEY[0]); 
	
	//remember to rename the SOC as necessary
	lab7soc u0 (
		.clk_clk                           (MAX10_CLK1_50),  //clk.clk
		.reset_reset_n                     (KEY[0]),           //reset.reset_n
		.altpll_0_locked_conduit_export    (),               //altpll_0_locked_conduit.export
		.altpll_0_phasedone_conduit_export (),               //altpll_0_phasedone_conduit.export
		.altpll_0_areset_conduit_export    (),               //altpll_0_areset_conduit.export
		.button_wire_export    (KEY),            //key_external_connection.export

		//SDRAM
		.sdram_pll_c1_clk(DRAM_CLK),                            //clk_sdram.clk
		.sdram_wire_addr(DRAM_ADDR),                         //sdram_wire.addr
		.sdram_wire_ba(DRAM_BA),                             //.ba
		.sdram_wire_cas_n(DRAM_CAS_N),                       //.cas_n
		.sdram_wire_cke(DRAM_CKE),                           //.cke
		.sdram_wire_cs_n(DRAM_CS_N),                         //.cs_n
		.sdram_wire_dq(DRAM_DQ),                             //.dq
		.sdram_wire_dqm({DRAM_UDQM,DRAM_LDQM}),              //.dqm
		.sdram_wire_ras_n(DRAM_RAS_N),                       //.ras_n
		.sdram_wire_we_n(DRAM_WE_N),                         //.we_n

		//USB SPI	
		.spi_0_SS_n(SPI0_CS_N),
		.spi_0_MOSI(SPI0_MOSI),
		.spi_0_MISO(SPI0_MISO),
		.spi_0_SCLK(SPI0_SCLK),
		
		//USB GPIO
		.usb_rst_wire_export(USB_RST),
		.usb_irq_wire_export(USB_IRQ),
		.usb_gpx_wire_export(USB_GPX),
		
		//LEDs and HEX
		.hex_wire_export({hex_num_3, hex_num_2, hex_num_1, hex_num_0}),
		.led_external_connection_export({hundreds, signs, LEDR}),
		.keycode_wire_export(keycode),
		
		//VGA
		.vga_red (VGA_R),
		.vga_green (VGA_G),
		.vga_blue (VGA_B),
		.vga_hs (VGA_HS),
		.vga_vs (VGA_VS),
		.debug_debug1(debug_sig1),
		.debug_debug2(debug_sig2),
		
		// i2C
		.i2c_sda_in(i2c_serial_sda_in),
		.i2c_scl_in(i2c_serial_scl_in),
		.i2c_sda_oe(i2c_sda_oe),
		.i2c_scl_oe(i2c_scl_oe),
		
		// i2s
		.i2s_sclk(ARDUINO_IO[5]),
		.i2s_lrclk(ARDUINO_IO[4]),
		.i2s_start(1'b0),
		.i2s_data_out(ARDUINO_IO[2])
		
	 );

endmodule
