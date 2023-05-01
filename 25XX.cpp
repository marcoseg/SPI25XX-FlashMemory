#include <25XX.h>



Spi25XX::Spi25XX(uint8_t cs,uint8_t clk,uint8_t dai,uint8_t dao)
{
    _cs_pin = cs;
    _clk_pin = clk;
    _din_pin = dai;
    _dout_pin = dao;
    pinMode(_cs_pin,OUTPUT);
    pinMode(_clk_pin,OUTPUT);
    pinMode(_din_pin,OUTPUT);   // data input on chip
    pinMode(_dout_pin,INPUT);   // data output on chip
    digitalWrite(_cs_pin,HIGH);
   
}

void Spi25XX::wen()
{
    digitalWrite(_cs_pin,LOW);
    sendBits(_din_pin,_clk_pin,WREN,8);
    digitalWrite(_cs_pin,HIGH);
}

void Spi25XX::wdis()
{
    digitalWrite(_cs_pin,LOW);
    sendBits(_din_pin,_clk_pin,WRDI,8);
    digitalWrite(_cs_pin,HIGH);
}

uint8_t Spi25XX::rsr()
{
    digitalWrite(_cs_pin,LOW);
    sendBits(_din_pin,_clk_pin,RDSR,8);
    _data =  recivedBits(_dout_pin,_clk_pin,8);
    digitalWrite(_cs_pin,HIGH);
    return _data;
}

void Spi25XX::wsr(uint8_t value)
{
     digitalWrite(_cs_pin,LOW);
    sendBits(_din_pin,_clk_pin,WRSR + value,16);
    digitalWrite(_cs_pin,HIGH);
    delay(20);
}

uint8_t Spi25XX::read(uint32_t address)
{
    digitalWrite(_cs_pin,LOW);
    sendBits(_din_pin,_clk_pin,(READ + address),32);
    _data =  recivedBits(_dout_pin,_clk_pin,8);
    digitalWrite(_cs_pin,HIGH);
    return _data;
}

void Spi25XX::pageprogram(uint32_t address , int buffer[])
{  
    digitalWrite(_cs_pin,LOW);
    sendBits(_din_pin,_clk_pin,(PP + address),32);
    for (int i = 0; i < 0x100; i++){
        sendBits(_din_pin,_clk_pin, buffer[i],8);
    }
    digitalWrite(_cs_pin,HIGH);
    delay(5);
}

void Spi25XX::blk64erase(uint32_t address)
{
    digitalWrite(_cs_pin,LOW);
    sendBits(_din_pin,_clk_pin,(BE + address),32);
    digitalWrite(_cs_pin,HIGH);
    delay(2500);
}

void Spi25XX::sector4kerase(uint32_t address)
{
    digitalWrite(_cs_pin,LOW);
    sendBits(_din_pin,_clk_pin,(SEE + address),32);
    digitalWrite(_cs_pin,HIGH);
    delay(400);
}

void Spi25XX::chiperase()
{
    digitalWrite(_cs_pin,LOW);
    sendBits(_din_pin,_clk_pin,CE,8);
    digitalWrite(_cs_pin,HIGH);
    delay(100000);
} 


void Spi25XX::powerdown()
{
    digitalWrite(_cs_pin,LOW);
    sendBits(_din_pin,_clk_pin,PWD,8);
    digitalWrite(_cs_pin,HIGH);

}

uint8_t Spi25XX::rpwd()
{
    digitalWrite(_cs_pin,LOW);
    sendBits(_din_pin,_clk_pin,RPID,32);
    _data = recivedBits(_dout_pin,_clk_pin,8);
    digitalWrite(_cs_pin,HIGH);
    return _data;
}

uint16_t Spi25XX::mfid()
{
    digitalWrite(_cs_pin,LOW);
    sendBits(_din_pin,_clk_pin,MFID,32);
   _data= recivedBits(_dout_pin,_clk_pin,16);
    digitalWrite(_cs_pin,HIGH);
    return _data;
}

uint32_t Spi25XX::jedec()
{
    digitalWrite(_cs_pin,LOW);
    sendBits(_din_pin,_clk_pin,JEDEC,8);
    _data = recivedBits(_dout_pin,_clk_pin,24);
    digitalWrite(_cs_pin,HIGH);
    return _data;
}

void Spi25XX::sendBits(uint8_t dataPin,uint8_t clkPin,uint32_t value,uint8_t nbits)
{
        digitalWrite(clkPin,LOW);
switch (nbits)
{
    case 8:
        MASK=0x80;
    break;
    case 16:
        MASK=0x8000;
    break;
     case 32:
        MASK=0x80000000;
    break;
}
     for (int i = 0; i < nbits; i++){
        digitalWrite(dataPin, (value & MASK) !=0);
        value<<=1;
        digitalWrite(clkPin,HIGH);
        digitalWrite(clkPin,LOW);
    } 
}

uint16_t Spi25XX::recivedBits(uint8_t dataPin,uint8_t clkPin,uint8_t nbits)
{
     uint32_t value32 = 0x00000000; 
  
        for(int i = 1; i <= nbits; i++ ){
             digitalWrite(clkPin,HIGH); 
            value32 |= digitalRead(dataPin) << (nbits - i); 
            digitalWrite(clkPin,LOW); 
        }
    return value32;
}
