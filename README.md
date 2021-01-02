# cev_rz_os

# Boot
Boot Mode1, Reset Vector is 0x0000 0000.
Boot Mode1, Reset Vector is 0xFFFF 0000.

# RZ/A1L Memory Map
|Address|Function|
|:---:|:---|
|0xFFFF_0000～0xFFFF_FFFF|IO|
|0xFFFF_0000～0xFFFF_FFFF|IO|

# Boot Mode
CPU Boot Mode is Mode1(Boot from SPI Serial Flush Memory)
Serial Flush Memory has 2MB ROM.
- Address: 0x1800_0000 ～ 0x1FFF_FFFF

# SDRAM
32MB SDRAM(16bit bus)
- Address: 0x0C00_0000 ～ 0x0FFF_FFFF

# Internal Memory
RZ/1AL has 3MB Internal Memory
- Address: 0x2000 0000 ～ 0x202F FFFF
