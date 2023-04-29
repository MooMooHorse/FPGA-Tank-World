	lab7soc u0 (
		.button_wire_export             (<connected-to-button_wire_export>),             //             button_wire.export
		.clk_clk                        (<connected-to-clk_clk>),                        //                     clk.clk
		.debug_debug1                   (<connected-to-debug_debug1>),                   //                   debug.debug1
		.debug_debug2                   (<connected-to-debug_debug2>),                   //                        .debug2
		.hex_wire_export                (<connected-to-hex_wire_export>),                //                hex_wire.export
		.keycode_wire_export            (<connected-to-keycode_wire_export>),            //            keycode_wire.export
		.led_external_connection_export (<connected-to-led_external_connection_export>), // led_external_connection.export
		.reset_reset_n                  (<connected-to-reset_reset_n>),                  //                   reset.reset_n
		.sdram_pll_c1_clk               (<connected-to-sdram_pll_c1_clk>),               //            sdram_pll_c1.clk
		.sdram_wire_addr                (<connected-to-sdram_wire_addr>),                //              sdram_wire.addr
		.sdram_wire_ba                  (<connected-to-sdram_wire_ba>),                  //                        .ba
		.sdram_wire_cas_n               (<connected-to-sdram_wire_cas_n>),               //                        .cas_n
		.sdram_wire_cke                 (<connected-to-sdram_wire_cke>),                 //                        .cke
		.sdram_wire_cs_n                (<connected-to-sdram_wire_cs_n>),                //                        .cs_n
		.sdram_wire_dq                  (<connected-to-sdram_wire_dq>),                  //                        .dq
		.sdram_wire_dqm                 (<connected-to-sdram_wire_dqm>),                 //                        .dqm
		.sdram_wire_ras_n               (<connected-to-sdram_wire_ras_n>),               //                        .ras_n
		.sdram_wire_we_n                (<connected-to-sdram_wire_we_n>),                //                        .we_n
		.spi_0_MISO                     (<connected-to-spi_0_MISO>),                     //                   spi_0.MISO
		.spi_0_MOSI                     (<connected-to-spi_0_MOSI>),                     //                        .MOSI
		.spi_0_SCLK                     (<connected-to-spi_0_SCLK>),                     //                        .SCLK
		.spi_0_SS_n                     (<connected-to-spi_0_SS_n>),                     //                        .SS_n
		.switch_wire_export             (<connected-to-switch_wire_export>),             //             switch_wire.export
		.usb_gpx_wire_export            (<connected-to-usb_gpx_wire_export>),            //            usb_gpx_wire.export
		.usb_irq_wire_export            (<connected-to-usb_irq_wire_export>),            //            usb_irq_wire.export
		.usb_rst_wire_export            (<connected-to-usb_rst_wire_export>),            //            usb_rst_wire.export
		.vga_blue                       (<connected-to-vga_blue>),                       //                     vga.blue
		.vga_green                      (<connected-to-vga_green>),                      //                        .green
		.vga_red                        (<connected-to-vga_red>),                        //                        .red
		.vga_hs                         (<connected-to-vga_hs>),                         //                        .hs
		.vga_vs                         (<connected-to-vga_vs>),                         //                        .vs
		.i2c_sda_in                     (<connected-to-i2c_sda_in>),                     //                     i2c.sda_in
		.i2c_scl_in                     (<connected-to-i2c_scl_in>),                     //                        .scl_in
		.i2c_sda_oe                     (<connected-to-i2c_sda_oe>),                     //                        .sda_oe
		.i2c_scl_oe                     (<connected-to-i2c_scl_oe>)                      //                        .scl_oe
	);

