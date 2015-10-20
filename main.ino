//imports the SPI library (needed to communicate with Gamebuino's screen)
#include <SPI.h>
//imports the Gamebuino library
#include <Gamebuino.h>
//creates a Gamebuino object named gb
Gamebuino gb;
int voitureX=8, voitureY=16, i;
const int limiteRouteH=36, limiteRouteB=12,limiteRouteM=24,nombrePointilles=4;
const byte voiture[] PROGMEM = {16,8,
B00000111,B11110000,
B00001011,B11010000,
B00001011,B11111110,
B11111111,B11111111,
B11111111,B11111111,
B11111111,B11111111,
B11001110,B00100111,
B01111000,B00111100,
};
// the setup routine runs once when Gamebuino starts up
void setup(){
  // initialize the Gamebuino object
  gb.begin();
  // shows the start menu
  gb.titleScreen(F("Le Caca"));

}

// the loop routine runs over and over again forever
void loop(){
  //updates the gamebuino (the display, the sound, the auto backlight... everything)
  //returns true when it's time to render a new frame (20 times/second)
  if(gb.update()){
    gb.display.drawLine(0,limiteRouteH,LDCWIDTH,limiteRouteH);
    gb.display.drawLine(0,limiteRouteB,LDCWIDTH,limiteRouteB);
    for (i=0;i<nombrePointilles;i++)
    {
      
    }
    
   gb.display.drawBitmap(voitureX,voitureY,voiture);
  }
}

