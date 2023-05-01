#ifndef __25XX_H__
#define __25XX_H__

#include <Arduino.h>

class Spi25XX{

    public:

        Spi25XX(uint8_t cs,uint8_t clk,uint8_t dai,uint8_t dao);
        // Commands
        void wen();
        void wdis();
        uint8_t rsr();
        void wsr(uint8_t value);
        uint8_t read(uint32_t address);
        void pageprogram(uint32_t address , int buffer[]);
        void blk64erase(uint32_t address);
        void sector4kerase(uint32_t address);
        void chiperase();
        void powerdown();
        uint8_t rpwd();
        uint16_t mfid();
        uint32_t jedec();

        

    protected:
        // Pin variables and Commnads definitions

        uint8_t _cs_pin;
        uint8_t _clk_pin;
        uint8_t _din_pin;
        uint8_t _dout_pin;
        uint32_t _data;

       //Read / Write Commamds

        #define WREN 0x06       // Write Enable
        #define WRDI 0x04       // Write Disable
        #define RDSR 0x05       // Read Status Register      
        #define WRSR 0x01000    // Write Status Regiter 
        #define READ 0x03000000 // Read one byte
        #define PP 0x02000000   // 256 bytes page program

        // Delete Commnads
        #define BE 0xD8000000   // block rase  64K W25x10-80 
        #define SEE 0x20000000  // sector erase 4K
        #define CE 0xC7         // chip erase (time 6 seconds)

        //Power modes and ID

        #define PWD 0xB9          // Power Down
        #define RPID 0xABFFFFFF   // Returns 8 Bits
        #define MFID 0x90FFFF00   // Returns 16 Bits   
        #define JEDEC 0x9F        // Returns 24 bit

        void sendBits(uint8_t,uint8_t,uint32_t,uint8_t);
        uint16_t recivedBits(uint8_t,uint8_t,uint8_t);
        uint32_t MASK;
    private:


};

#endif // __25XX_H__