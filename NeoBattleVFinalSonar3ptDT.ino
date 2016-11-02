#include <Chrono.h>
#include <LightChrono.h>
#include <Adafruit_NeoPixel.h>

#include <NewPing.h>


NewPing sonarP1(11, 12, 20);
NewPing sonarP2(9, 10, 20);

#define VIDE 0
#define ROUGE 1
#define VERT 2
#define BLEU 3

#define NUMPIXELS 58

Chrono ledMetro;
Chrono brightMetro;

int couleurs[58];
long int tabVarRouge[] = {0xfb5900  , 0xFF1a00 , 0xff0d00};
int indiceRouge = 0 ;

long int tabVarBleu[] = {0x5600FF, 0x330099, 0x19004c };
int indiceBleu = 0 ;

long int tabVarVert[] = {0xbdff00  , 0x00FF00, 0x036700};
int indiceVert = 0 ;

int buttonPreviousState1 = LOW;
int buttonPreviousState2 = LOW;


int pointCentral = 30;
boolean isReadyJ1 = true;
boolean isReadyJ2 = true;
boolean letsPlay = true;


Adafruit_NeoPixel pixels = Adafruit_NeoPixel(58, 7, NEO_GRB + NEO_KHZ800);


void setup() {
  // put your setup code here, to run once:
  pixels.begin(); // This initializes the NeoPixel library.
  pixels.setBrightness(80);
}

void loop() {
  if (letsPlay) {
    if (ledMetro.hasPassed(10))
    {
      if (sonarP1.ping_cm() <= 4 && sonarP1.ping_cm() > 0)
      {
        couleurs[0] = ROUGE;
      }

      else if (sonarP1.ping_cm() > 4 && sonarP1.ping_cm() <= 8)
      {
        couleurs[0] = VERT;
      }
      else if (sonarP1.ping_cm() > 8 && sonarP1.ping_cm() <= 12)
      {
        couleurs[0] = BLEU;
      }

      if (sonarP2.ping_cm() <= 4 && sonarP2.ping_cm() > 0)
      {
        couleurs[58] = ROUGE;
      }

      else if (sonarP2.ping_cm() > 4 && sonarP2.ping_cm() <= 8)
      {
        couleurs[58] = VERT;
      }

      else if (sonarP2.ping_cm() > 8 && sonarP2.ping_cm() <= 12)
      {
        couleurs[58] = BLEU;
      }


      // mettre a jour le point central
      int coteDroit = couleurs[pointCentral - 2];
      int coteGauche = couleurs[pointCentral + 2];

      if ( coteDroit == ROUGE && (coteGauche == VERT ||  coteGauche == VIDE )) {
        couleurs[pointCentral-2] = VIDE;
        pointCentral++;
        couleurs[pointCentral] = VIDE;
        couleurs[pointCentral-2] = VIDE;
         couleurs[pointCentral+3] = VIDE;
         coteDroit = VIDE;
         coteGauche = VIDE;

      } else if ( coteDroit == VERT && (coteGauche == BLEU ||  coteGauche == VIDE )) {
     couleurs[pointCentral-2] = VIDE;
        pointCentral++;
        couleurs[pointCentral] =VIDE;
        couleurs[pointCentral-2] = VIDE;
         couleurs[pointCentral+2] = VIDE;
         couleurs[pointCentral+3] = VIDE;
         coteDroit = VIDE;
         coteGauche = VIDE;
      } else  if ( coteDroit == BLEU && (coteGauche == ROUGE ||  coteGauche == VIDE )) {
        couleurs[pointCentral-2] = VIDE;
        pointCentral++;
        couleurs[pointCentral] = VIDE;
        couleurs[pointCentral-2] = VIDE;
         couleurs[pointCentral+2] = VIDE;
         couleurs[pointCentral+3] = VIDE;
         coteDroit = VIDE;
         coteGauche = VIDE;
      }

      if ( coteGauche == ROUGE && (coteDroit == VERT ||  coteDroit == VIDE )) {
       couleurs[pointCentral+2] = VIDE;
        pointCentral--;
        couleurs[pointCentral] = VIDE;
        couleurs[pointCentral-2] = VIDE;
         couleurs[pointCentral+2] = VIDE;
         couleurs[pointCentral-3] = VIDE;
         coteDroit = VIDE;
         coteGauche = VIDE;
      } else if ( coteGauche == VERT && (coteDroit == BLEU ||  coteDroit == VIDE )) {
     couleurs[pointCentral+2] = VIDE;
        pointCentral--;
        couleurs[pointCentral] = VIDE;
        couleurs[pointCentral-2] = VIDE;
         couleurs[pointCentral+2] = VIDE;
          couleurs[pointCentral-3] = VIDE;
         coteDroit = VIDE;
         coteGauche = VIDE;
      } else  if ( coteGauche == BLEU && (coteDroit == ROUGE ||  coteDroit == VIDE )) {
         couleurs[pointCentral+2] = VIDE;
        pointCentral--;
        couleurs[pointCentral] = VIDE;
        couleurs[pointCentral-2] = VIDE;
         couleurs[pointCentral+2] = VIDE;
          couleurs[pointCentral-3] = VIDE;
         coteDroit = VIDE;
         coteGauche = VIDE;
      }




      for ( int i = pointCentral - 1 ; i >= 0  ; i-- ) {
        couleurs[i + 1] = couleurs[i];

      }


      for ( int i = pointCentral + 1 ; i < 59 ; i++ ) {
        couleurs[i - 1] = couleurs[i];
      }

      for (int i = 0; i < 58; i++) {
        int c = couleurs[i];
        if ( c == VIDE ) {
          pixels.setPixelColor(i, pixels.Color(0, 0, 0)); // Moderately bright green color.
        } else if ( c == ROUGE ) {
          pixels.setPixelColor(i, tabVarRouge[indiceRouge]);
          if (indiceRouge <= 1)
          {
            indiceRouge++;
          }
          else
          {
            indiceRouge = 0;
          }
        } else if ( c == VERT ) {
          pixels.setPixelColor(i, tabVarVert[indiceVert]); // Moderately bright green color.
          if (indiceVert <= 1)
          {
            indiceVert++;
          }
          else
          {
            indiceVert = 0;
          }

        } else if ( c == BLEU ) {
          pixels.setPixelColor(i, tabVarBleu[indiceBleu]);
          if (indiceBleu <= 1)
          {
            indiceBleu++;
          }
          else
          {
            indiceBleu = 0;
          }// Moderately bright green color.
        }
      }

      if ( pointCentral > 55 )
      {
        for (int i = 0; i < NUMPIXELS; i++) {

          // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
          pixels.setPixelColor(i, pixels.Color(0, 0, 0));
          couleurs[i] = VIDE;
        }

        pointCentral = 28;
      }
   else   if ( pointCentral < 2 )
      {
        for (int i = 0; i < NUMPIXELS; i++) {

          // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
          pixels.setPixelColor(i, pixels.Color(0, 0, 0));
          couleurs[i] = VIDE;
        }
        pointCentral = 28;


      }

      pixels.setPixelColor( pointCentral, pixels.Color(255, 255, 255));
      pixels.setPixelColor( pointCentral+1, pixels.Color(255, 255, 255));
      pixels.setPixelColor( pointCentral-1, pixels.Color(255, 255, 255));


      pixels.show();

      ledMetro.restart();
    }

  }
}


