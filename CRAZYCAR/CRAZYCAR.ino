#include <Backlight.h>
#include <Battery.h>
#include <Buttons.h>
#include <Display.h>
#include <Sound.h>
//imports the SPI library (needed to communicate with Gamebuino's screen)
#include <SPI.h>
//imports the Gamebuino library
#include <Gamebuino.h>
#define LIMITEROUTEH 36
#define LIMITEROUTEB 12
#define LIMITEROUTEM 24
#define NOMBREPOINTILLES 4
//creates a Gamebuino object named gb
Gamebuino gb;

int voitureX=8, voitureY=28, i;
int  espacePointilles = 4,taillePointille=LCDWIDTH/NOMBREPOINTILLES-espacePointilles, perdu = 0, score = 0, debut = 1;
int vitesse=2;
const char strEasy[] PROGMEM = "Easy";
const char strHard[] PROGMEM = "Hard";
const char strExtreme[] PROGMEM = "Extreme";
const char strExit[] PROGMEM = "Exit";
const char* const menu[4] PROGMEM = {strEasy,strHard,strExtreme,strExit};
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
const byte animal[] PROGMEM = {8,8,
B00000010,
B00000011,
B01111111,
B11111110,
B01111110,
B01000100,
B01000100,
B00000000,
};
const byte clous[] PROGMEM = {8,8,
B00000000,
B00010000,
B00111000,
B00000100,
B00001110,
B00100000,
B01110000,
B00000000,
};
const byte cone[] PROGMEM = {8,8,
B00000000,
B00011000,
B00111100,
B00100100,
B01111110,
B01000010,
B11111111,
B11111111,
};
const byte homme[] PROGMEM = {8,8,
B01011010,
B01011010,
B01111110,
B00011000,
B00011000,
B00111100,
B00100100,
B01101100,
};
const byte arbre[] PROGMEM = {8,8,
B00111100,
B01111110,
B01111110,
B01111110,
B00111100,
B00011000,
B00011000,
B00111100,
};

void dVoiture();
void dDecor();
void dObstacles();
void afficherMenu();

typedef struct Obstacle Obstacle;
struct Obstacle
{
  int x = 0;
  int y = 0;
  int nBitmap = 0;
};
Obstacle obs[3];
typedef struct Decor Decor;
struct Decor
{
  int x = 0;
  int y = 0;
};
Decor dec[22];

// the setup routine runs once when Gamebuino starts up
void setup(){
  // initialize the Gamebuino object
  obs[0].x = -8;
  obs[1].x = 30;
  obs[2].x = 60;
  obs[0].y = obs[1].y = obs[2].y = 14;
  dec[0].x = dec[11].x = 0;
  dec[1].x = dec[12].x = 8;
  dec[2].x = dec[13].x = 16;
  dec[3].x = dec[14].x = 24;
  dec[4].x = dec[15].x = 32;
  dec[5].x = dec[16].x = 40;
  dec[6].x = dec[17].x = 48;
  dec[7].x = dec[18].x = 56;
  dec[8].x = dec[19].x = 64;
  dec[9].x = dec[20].x = 72;
  dec[10].x = dec[21].x = 80;
  for (i=0;i<11;i++)
  {
    dec[i].y= 37;
    dec[i+11].y= 1;
  }
  
  gb.begin();
  // shows the start menu
  gb.titleScreen(F("Crazycar"));

}

// the loop routine runs over and over again forever
void loop(){
  //updates the gamebuino (the display, the sound, the auto backlight... everything)
  //returns true when it's time to render a new frame (20 times/second)
  if(gb.update()){
    if (debut)
    {
     debut = 0;
     afficherMenu(); 
    }
    else if (!perdu)
    {
    dDecor();
    dVoiture();
    dObstacles();
    }
    else
    {
      gb.display.clear();
      gb.display.print("Your score is: ");
      gb.display.println(score);
      gb.display.print("Press C");
      if (gb.buttons.pressed(BTN_C))
      {
       gb.sound.playCancel();
       afficherMenu(); 
      }
    }
    }
    }

void dVoiture()
{

    if ((gb.buttons.repeat(BTN_DOWN,1))&&((voitureY+8)<LIMITEROUTEH))
    {
      voitureY+=vitesse;
    }
    if ((gb.buttons.repeat(BTN_UP,1))&&(voitureY>LIMITEROUTEB))
    {
      voitureY-=vitesse;
    }
    gb.display.drawBitmap(voitureX,voitureY,voiture);

}
void dDecor()
{
    gb.display.drawLine(0,LIMITEROUTEH,LCDWIDTH,LIMITEROUTEH);
    gb.display.drawLine(0,LIMITEROUTEB,LCDWIDTH,LIMITEROUTEB);
    for (i=0; i<11; i++)
    {
      if (dec[i].x<=-8){dec[i].x = 84;}
      if (dec[i+11].x<=-8){dec[i+11].x = 84;}
      gb.display.drawBitmap(dec[i].x-=vitesse,dec[i].y,arbre);
      gb.display.drawBitmap(dec[i+11].x-=vitesse,dec[i+11].y,arbre);

    }
    for (i=0;i<NOMBREPOINTILLES+1;i++)
    {
      gb.display.drawLine(espacePointilles+i*(taillePointille+8),LIMITEROUTEM,espacePointilles+i*(taillePointille+8)+taillePointille,LIMITEROUTEM);
      //On dessine les pointilles de la route, 8 et espacePointilles sont les espaces entre les pointillés, ils doivent être égaux
    }

    espacePointilles-=vitesse;
    if (espacePointilles<-taillePointille-4) {espacePointilles=2;};
}
void dObstacles()
{
for (i=0; i<3; i++)
{
  switch (obs[i].nBitmap)
  {
    case 0:
    gb.display.drawBitmap(obs[i].x-=vitesse,obs[i].y,cone);
    if (gb.collideBitmapBitmap(obs[i].x,obs[i].y,cone,voitureX,voitureY,voiture)) {perdu = 1;}
    break;
    case 1: 
    gb.display.drawBitmap(obs[i].x-=vitesse,obs[i].y,clous);
    if (gb.collideBitmapBitmap(obs[i].x,obs[i].y,clous,voitureX,voitureY,voiture)) {perdu = 1;}
    break;
    case 2: 
    gb.display.drawBitmap(obs[i].x-=vitesse,obs[i].y,animal);
    if (gb.collideBitmapBitmap(obs[i].x,obs[i].y,animal,voitureX,voitureY,voiture)) {perdu = 1;}
    break;
    case 3: 
    gb.display.drawBitmap(obs[i].x-=vitesse,obs[i].y,homme);
    if (gb.collideBitmapBitmap(obs[i].x,obs[i].y,homme,voitureX,voitureY,voiture)) {perdu = 1;}
    break;

  }
  if (obs[i].x<=-8) 
  {
    score++;
    obs[i].x = 84;
    obs[i].y = random(2)*12+14;
    obs[i].nBitmap = random(4);
  }
}
}
void afficherMenu()
{
        voitureY=28;
        obs[0].y = obs[1].y = obs[2].y = 14;
        perdu = 0;
        score = 0;
        switch(gb.menu(menu,4))
        {
        case -1:
        debut = 1;
        gb.titleScreen(F("CRAZYCAR"));
        break;
        case 0:
        vitesse = 2;
        break;
        case 1:
        vitesse = 3;
        break;
        case 2:
        vitesse = 4;
        break;
        case 3:
        debut = 1;
        gb.titleScreen(F("CRAZYCAR"));
        break;
       }

}
