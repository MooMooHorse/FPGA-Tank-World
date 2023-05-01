
module lab7soc (
	button_wire_export,
	clk_clk,
	debug_debug1,
	debug_debug2,
	hex_wire_export,
	i2c_sda_in,
	i2c_scl_in,
	i2c_sda_oe,
	i2c_scl_oe,
	i2s_sclk,
	i2s_lrclk,
	i2s_start,
	i2s_i2s_dataout,
	keycode_wire_export,
	led_external_connection_export,
	reset_reset_n,
	sdram_pll_c1_clk,
	sdram_wire_addr,
	sdram_wire_ba,
	sdram_wire_cas_n,
	sdram_wire_cke,
	sdram_wire_cs_n,
	sdram_wire_dq,
	sdram_wire_dqm,
	sdram_wire_ras_n,
	sdram_wire_we_n,
	spi_0_MISO,
	spi_0_MOSI,
	spi_0_SCLK,
	spi_0_SS_n,
	switch_wire_export,
	usb_gpx_wire_export,
	usb_irq_wire_export,
	usb_rst_wire_export,
	vga_blue,
	vga_green,
	vga_red,
	vga_hs,
	vga_vs);	

	input	[1:0]	button_wire_export;
	input		clk_clk;
	output	[7:0]	debug_debug1;
	output	[7:0]	debug_debug2;
	output	[15:0]	hex_wire_export;
	input		i2c_sda_in;
	input		i2c_scl_in;
	output		i2c_sda_oe;
	output		i2c_scl_oe;
	input		i2s_sclk;
	input		i2s_lrclk;
	input		i2s_start;
	output		i2s_i2s_dataout;
	output	[7:0]	keycode_wire_export;
	output	[13:0]	led_external_connection_export;
	input		reset_reset_n;
	output		sdram_pll_c1_clk;
	output	[12:0]	sdram_wire_addr;
	output	[1:0]	sdram_wire_ba;
	output		sdram_wire_cas_n;
	output		sdram_wire_cke;
	output		sdram_wire_cs_n;
	inout	[15:0]	sdram_wire_dq;
	output	[1:0]	sdram_wire_dqm;
	output		sdram_wire_ras_n;
	output		sdram_wire_we_n;
	input		spi_0_MISO;
	output		spi_0_MOSI;
	output		spi_0_SCLK;
	output		spi_0_SS_n;
	input	[7:0]	switch_wire_export;
	input		usb_gpx_wire_export;
	input		usb_irq_wire_export;
	output		usb_rst_wire_export;
	output	[3:0]	vga_blue;
	output	[3:0]	vga_green;
	output	[3:0]	vga_red;
	output		vga_hs;
	output		vga_vs;
endmodule
