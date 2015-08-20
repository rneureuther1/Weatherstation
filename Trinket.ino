// Adafruit Trinket code
// Bealgebone Tx pin to Trinket Rx pin
// Adruino shares the same buffer for computer Serial and RxTx pins but Trinket does not support USB Serial
#include <Adafruit_NeoPixel.h>

#define PIN 6

// Parameter 1 = number of pixels in strip
// Parameter 2 = Arduino pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(24, PIN, NEO_GRB + NEO_KHZ800);

int pops[23];
int red[23];
int green[23];
int blue[23];

void setup() 
{   //Serial setup
    Serial.begin(9600);
    pinMode(13, OUTPUT);
    digitalWrite(13, LOW);

    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}

void loop() 
{
    int test;
    test=Serial.peek();

    //Beaglebone transmits data in the form of H(n) P(n) H(n+1) P(n+1)...starting with first hour available from
    //      Wundergound site
    // -1: connected, no data
    //  0: not connected
    //  #: incoming data

    if(test==-1)
    {
        delay(5000);
    }

    else if(test==0)
    {
        // Blink the Ring Red on and off
    }

    else{
        // If data is recieved, blink twice
        blink(13, 2);
        getData();
    }

    }



void blink(int pin, int times)
{
    int i;
    for(i=0; i<times; i++)
    {
        digitalWrite(pin, LOW);
        delay(500);
        digitalWrite(pin, HIGH);
        delay(500);
        digitalWrite(pin, LOW);
        delay(500);
    }
    
}

void getData()
{
     while(Serial.peek() != -1)
     {
     pop[Serial.read()] = Serial.read();
     }
}

int findRed()
{
    
    
}
int findGreen()
{
    
}
int findBlue()
{
    
    
}
