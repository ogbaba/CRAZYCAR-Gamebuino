//imports the SPI library (needed to communicate with Gamebuino's screen)
#include <SPI.h>
//imports the Gamebuino library
#include <Gamebuino.h>
//creates a Gamebuino object named gb
Gamebuino gb;
int voitureX=8, voitureY=16, i;
const int limiteRouteH=36, limiteRouteB=12,limiteRouteM=24,nombrePointilles=4;
int  espacePointilles = 4,taillePointille=LCDWIDTH/nombrePointilles-espacePointilles;
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
  gb.titleScreen(F("Crazycar"));

}

// the loop routine runs over and over again forever
void loop(){
  //updates the gamebuino (the display, the sound, the auto backlight... everything)
  //returns true when it's time to render a new frame (20 times/second)
  if(gb.update()){
    gb.display.drawLine(0,limiteRouteH,LCDWIDTH,limiteRouteH);
    gb.display.drawLine(0,limiteRouteB,LCDWIDTH,limiteRouteB);
    for (i=0;i<nombrePointilles+1;i++)
    {
      gb.display.drawLine(espacePointilles+i*(taillePointille+4),limiteRouteM,espacePointilles+i*(taillePointille+4)+taillePointille,limiteRouteM); //On dessine les pointilles de la route
    }
    
    espacePointilles-=2;
    if (espacePointilles<-taillePointille) {espacePointilles=4;};
    if ((gb.buttons.repeat(BTN_DOWN,1))||((voitureY)<limiteRouteB))
    {
      voitureY+=2;
    }
    if ((gb.buttons.repeat(BTN_UP,1))||((voitureY+8)>limiteRouteH))
    {
      voitureY-=2;
    }
    gb.display.drawBitmap(voitureX,voitureY,voiture);

  }
}
