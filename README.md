# RadioInterface Module: VUHFRadio Add-on Module

This is the firmware for an GUI Interface Add-on module for the VUHFRadio Module. Adds a 2.2" TFT Screen with buttons for control of the VUHFRadio Module.

Some characteristics of this firmware:
- Custom TFT Screen drivers for the ILI9341 over SPI
- Custom 2D Library to draw basic shapes and text
- Custom AX.25 decoding/encode library
- The MCU used is an STM32F103 and this firmware uses the LL Library
- Command interface to the VUHFRadio module uses the CAT command interface used in the VUHRadio Module over a private UART interface
- TNC style interface to the VUHFRadio uses the KISS protocol

Current version is tested and works with:
- Switching between the two Radio/Transceiver channels, VHF and UHF
- Loading of configurations on startup from the VUHFRadio Module
- Update and display RSSI and RF Frequency tracking variables
- Working menus for changing main analog domain and digital domain configurations and send the changes to the VUHFRadio module
- Display last CAT command sent and return status
- Decode and display AX.25 frames received from the VUHFRadio Module over the KISS protocol
- A Waterfall window with vertical scrolling to show the history of the RSSI and RF Frequency tracking variables

Detailed explanation on the RadioInterface Module and its usage: www.notblackmagic.com/projects/radio-interface/

## File Organization

**src/HAL:** MCU peripheral drivers, custom HALs

**src/Graphics:** TFT Screen interface wrapper and custom 2D Library (tft_gui.c)

**src/gui.c:** GUI Interface

**src/Radio/CATInterface.c:** CAT Command Handler and interpreter functions

**src/Radio/ax25.c** AX25 encode and decode library

**include/configs.c:** Radio configurations save files
