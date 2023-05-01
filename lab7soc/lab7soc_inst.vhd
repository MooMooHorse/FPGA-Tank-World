	component lab7soc is
		port (
			button_wire_export             : in    std_logic_vector(1 downto 0)  := (others => 'X'); -- export
			clk_clk                        : in    std_logic                     := 'X';             -- clk
			debug_debug1                   : out   std_logic_vector(7 downto 0);                     -- debug1
			debug_debug2                   : out   std_logic_vector(7 downto 0);                     -- debug2
			hex_wire_export                : out   std_logic_vector(15 downto 0);                    -- export
			i2c_sda_in                     : in    std_logic                     := 'X';             -- sda_in
			i2c_scl_in                     : in    std_logic                     := 'X';             -- scl_in
			i2c_sda_oe                     : out   std_logic;                                        -- sda_oe
			i2c_scl_oe                     : out   std_logic;                                        -- scl_oe
			i2s_sclk                       : in    std_logic                     := 'X';             -- sclk
			i2s_lrclk                      : in    std_logic                     := 'X';             -- lrclk
			i2s_start                      : in    std_logic                     := 'X';             -- start
			i2s_i2s_dataout                : out   std_logic;                                        -- i2s_dataout
			keycode_wire_export            : out   std_logic_vector(7 downto 0);                     -- export
			led_external_connection_export : out   std_logic_vector(13 downto 0);                    -- export
			reset_reset_n                  : in    std_logic                     := 'X';             -- reset_n
			sdram_pll_c1_clk               : out   std_logic;                                        -- clk
			sdram_wire_addr                : out   std_logic_vector(12 downto 0);                    -- addr
			sdram_wire_ba                  : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_wire_cas_n               : out   std_logic;                                        -- cas_n
			sdram_wire_cke                 : out   std_logic;                                        -- cke
			sdram_wire_cs_n                : out   std_logic;                                        -- cs_n
			sdram_wire_dq                  : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			sdram_wire_dqm                 : out   std_logic_vector(1 downto 0);                     -- dqm
			sdram_wire_ras_n               : out   std_logic;                                        -- ras_n
			sdram_wire_we_n                : out   std_logic;                                        -- we_n
			spi_0_MISO                     : in    std_logic                     := 'X';             -- MISO
			spi_0_MOSI                     : out   std_logic;                                        -- MOSI
			spi_0_SCLK                     : out   std_logic;                                        -- SCLK
			spi_0_SS_n                     : out   std_logic;                                        -- SS_n
			switch_wire_export             : in    std_logic_vector(7 downto 0)  := (others => 'X'); -- export
			usb_gpx_wire_export            : in    std_logic                     := 'X';             -- export
			usb_irq_wire_export            : in    std_logic                     := 'X';             -- export
			usb_rst_wire_export            : out   std_logic;                                        -- export
			vga_blue                       : out   std_logic_vector(3 downto 0);                     -- blue
			vga_green                      : out   std_logic_vector(3 downto 0);                     -- green
			vga_red                        : out   std_logic_vector(3 downto 0);                     -- red
			vga_hs                         : out   std_logic;                                        -- hs
			vga_vs                         : out   std_logic                                         -- vs
		);
	end component lab7soc;

	u0 : component lab7soc
		port map (
			button_wire_export             => CONNECTED_TO_button_wire_export,             --             button_wire.export
			clk_clk                        => CONNECTED_TO_clk_clk,                        --                     clk.clk
			debug_debug1                   => CONNECTED_TO_debug_debug1,                   --                   debug.debug1
			debug_debug2                   => CONNECTED_TO_debug_debug2,                   --                        .debug2
			hex_wire_export                => CONNECTED_TO_hex_wire_export,                --                hex_wire.export
			i2c_sda_in                     => CONNECTED_TO_i2c_sda_in,                     --                     i2c.sda_in
			i2c_scl_in                     => CONNECTED_TO_i2c_scl_in,                     --                        .scl_in
			i2c_sda_oe                     => CONNECTED_TO_i2c_sda_oe,                     --                        .sda_oe
			i2c_scl_oe                     => CONNECTED_TO_i2c_scl_oe,                     --                        .scl_oe
			i2s_sclk                       => CONNECTED_TO_i2s_sclk,                       --                     i2s.sclk
			i2s_lrclk                      => CONNECTED_TO_i2s_lrclk,                      --                        .lrclk
			i2s_start                      => CONNECTED_TO_i2s_start,                      --                        .start
			i2s_i2s_dataout                => CONNECTED_TO_i2s_i2s_dataout,                --                        .i2s_dataout
			keycode_wire_export            => CONNECTED_TO_keycode_wire_export,            --            keycode_wire.export
			led_external_connection_export => CONNECTED_TO_led_external_connection_export, -- led_external_connection.export
			reset_reset_n                  => CONNECTED_TO_reset_reset_n,                  --                   reset.reset_n
			sdram_pll_c1_clk               => CONNECTED_TO_sdram_pll_c1_clk,               --            sdram_pll_c1.clk
			sdram_wire_addr                => CONNECTED_TO_sdram_wire_addr,                --              sdram_wire.addr
			sdram_wire_ba                  => CONNECTED_TO_sdram_wire_ba,                  --                        .ba
			sdram_wire_cas_n               => CONNECTED_TO_sdram_wire_cas_n,               --                        .cas_n
			sdram_wire_cke                 => CONNECTED_TO_sdram_wire_cke,                 --                        .cke
			sdram_wire_cs_n                => CONNECTED_TO_sdram_wire_cs_n,                --                        .cs_n
			sdram_wire_dq                  => CONNECTED_TO_sdram_wire_dq,                  --                        .dq
			sdram_wire_dqm                 => CONNECTED_TO_sdram_wire_dqm,                 --                        .dqm
			sdram_wire_ras_n               => CONNECTED_TO_sdram_wire_ras_n,               --                        .ras_n
			sdram_wire_we_n                => CONNECTED_TO_sdram_wire_we_n,                --                        .we_n
			spi_0_MISO                     => CONNECTED_TO_spi_0_MISO,                     --                   spi_0.MISO
			spi_0_MOSI                     => CONNECTED_TO_spi_0_MOSI,                     --                        .MOSI
			spi_0_SCLK                     => CONNECTED_TO_spi_0_SCLK,                     --                        .SCLK
			spi_0_SS_n                     => CONNECTED_TO_spi_0_SS_n,                     --                        .SS_n
			switch_wire_export             => CONNECTED_TO_switch_wire_export,             --             switch_wire.export
			usb_gpx_wire_export            => CONNECTED_TO_usb_gpx_wire_export,            --            usb_gpx_wire.export
			usb_irq_wire_export            => CONNECTED_TO_usb_irq_wire_export,            --            usb_irq_wire.export
			usb_rst_wire_export            => CONNECTED_TO_usb_rst_wire_export,            --            usb_rst_wire.export
			vga_blue                       => CONNECTED_TO_vga_blue,                       --                     vga.blue
			vga_green                      => CONNECTED_TO_vga_green,                      --                        .green
			vga_red                        => CONNECTED_TO_vga_red,                        --                        .red
			vga_hs                         => CONNECTED_TO_vga_hs,                         --                        .hs
			vga_vs                         => CONNECTED_TO_vga_vs                          --                        .vs
		);

