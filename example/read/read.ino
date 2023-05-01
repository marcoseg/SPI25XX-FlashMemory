#include <25XX.h>



Spi25XX mem1 (2,3,4,5);   
void setup() {
Serial.begin(9600);
mem1.wen();
Serial.println("\n Read Status Register...\n");
Serial.println(mem1.rsr(),HEX);
int temp[256];
for(int y = 0; y<256;y++){
  temp[y]=y;
}


Serial.println("\n Lectura Bloque 0 mem1 ....\n");
Serial.println(mem1.mfid(),HEX);
Serial.println(mem1.jedec(),HEX);
for(word base = 0x0000;base <=0x0500;base +=16){
    uint8_t MemLoc[16];
    for(int offset = 0; offset <=15; offset++){
      MemLoc[offset]=mem1.read(base + offset);
    }
    char buff[255];
    sprintf(buff,"%05x:    %02x %02x %02x %02x %02x %02x %02x %02x   %02x %02x %02x %02x %02x %02x %02x %02x",
            base, MemLoc[0], MemLoc[1], MemLoc[2], MemLoc[3], MemLoc[4], MemLoc[5], MemLoc[6], MemLoc[7],
            MemLoc[8], MemLoc[9], MemLoc[10], MemLoc[11], MemLoc[12], MemLoc[13], MemLoc[14], MemLoc[15]);
 
   Serial.println(buff);
 }
}

void loop() {
  // put your main code here, to run repeatedly:

}
