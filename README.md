# SPI25XX-FlashMemory
Simple Read / Write Spi 25XX flash memory series

# 25XX Library for Arduino / ESP32

 Simple Read / Wirte Library for Spi 25XX flash memory series

## Introduction

Using basic freatures to Read and Write in Windbond / ST / MX Spi 25XX flash memory


## Methods

| Method |  Description |
| ------ | ------ |
| `Spi25XX(cs_clk,di,do)` |  Select the interface pins |
| `wen()` | Enables Write, Erase and (Erase all) commands|
| `wdis()`| Disables Write, Erase and (Erase all) commands  |
| `rsr()`| Read Status Register |
| `wsr()`| Write Status Register |
| `read(address)` | Read specific 32 bit address |
| `pageprogram(address, array[])` | Write 256 bytes (page) from specific 32 bit address |
| `blk64erase(address)` | Erase 64kbytes from specific 32 bit address  |
| `sector4kerase(address)` | Erase 4kbytes sector from specific 32 bit address  |
| `chiperase()` | Erase entire chip  |
| `powerdown()` | Puts the memory in power down mode  |
| `rpwd()` | Release power down mode and returns device ID  |
| `mfid()` | Returns Manufacter ID  |
| `jedec()` | Returns jedec information |

## Memories Tested
| Manufacter | IC |
| ------------ | -------- |
| Windbond | 25/10/20/40/32 series 25X and 25Q | 
| ST | 25V10P |
|MX | 25L6473E |
|Spasion | S25FL016A |

## Paltform Tested
ESP32 and Arduino Mega2560 R3

## Why is simple?
This library don´t use Fast Reads mode, only normal read mode
