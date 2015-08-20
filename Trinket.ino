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

// Fixed maps define a 7 level color scheme: LBlue, Blue, LGreen, Green, Yellow, Orange, Red
int redmap[]={0,0,140,50,250,255,255};
int greenmap[]={240,160,0,50,0,0,0};
int bluemap[]={175,240,255,205,220,190,0};

// Dynamic arrays change with incoming weather data
// Pops (Probability of Precipitation) stored by index based on cooresponding hour of day
int pops[23];
int red[23];
int green[23];
int blue[23];

void setup() 
{   
    // Serial setup
    Serial.begin(9600);
    
    // Default values
    for(int i=0; i<24, i++)
    {
        pops[i]  = 100;
        red[i]   = 0;
        green[i] = 0;
        blue[i]  = 0;
    }
    
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

    else
    {
        // If data is recieved, blink onboard Trinket LED twice
        blink(13, 2);
        
        // Update the pops array
        getData();
        
        // Update the colors
        findRed();
        findGreen();
        findBlue();
        
        // Assign pixel colors
        for(uint16_t i=0; i<strip.numPixels(); i++)
        {
            strip.setPixelColor(i, strip.Color(red[i], green[i], blue[i]));
        }
    
        //Show colors
        strip.show();
    }
}


// Simple blink
void blink(int pin, int times)
{
    
    for(int i=0; i<times; i++)
    {
        digitalWrite(pin, LOW);
        delay(100);
        digitalWrite(pin, HIGH);
        delay(300);
        digitalWrite(pin, LOW);
        delay(100);
    }
    
}

//Process incoming serial data from Beaglebone Black
void getData()
{
     while(Serial.peek() != -1)
     {
     pops[Serial.read()] = Serial.read();
     }
}

//Assign colors based on the pop
int findRed()
{   
    for(int i=0; i<24; i++)
    {
        if(pops[i]<10)
        {
            red[i]=redmap[0];
        }
        else if(pops[i]<20)
        {
            red[i]=redmap[1];
        }
        else if(pops[i]<30)
        {
            red[i]=redmap[2];
        }
        else if(pops[i]<40)
        {
            red[i]=redmap[3];
        }
        else if(pops[i]<50)
        {
            red[i]=redmap[4];
        }
        else if(pops[i]<60)
        {
            red[i]=redmap[5];
        }
        else if(pops[i]>=60)
        {
            red[i]=redmap[6];
        }
    }
    
}
int findGreen()
{
    for(int i=0; i<24; i++)
    {
        if(pops[i]<10)
        {
            green[i]=greenmap[0];
        }
        else if(pops[i]<20)
        {
            green[i]=greenmap[1];
        }
        else if(pops[i]<30)
        {
            green[i]=greenmap[2];
        }
        else if(pops[i]<40)
        {
            green[i]=greenmap[3];
        }
        else if(pops[i]<50)
        {
            green[i]=greenmap[4];
        }
        else if(pops[i]<60)
        {
            green[i]=greenmap[5];
        }
        else if(pops[i]>=60)
        {
            green[i]=greenmap[6];
        }
    }
    
    
}
int findBlue()
{
     for(int i=0; i<24; i++)
    {
        if(pops[i]<10)
        {
            blue[i]=bluemap[0];
        }
        else if(pops[i]<20)
        {
            blue[i]=bluemap[1];
        }
        else if(pops[i]<30)
        {
            blue[i]=bluemap[2];
        }
        else if(pops[i]<40)
        {
            blue[i]=bluemap[3];
        }
        else if(pops[i]<50)
        {
            blue[i]=bluemap[4];
        }
        else if(pops[i]<60)
        {
            blue[i]=bluemap[5];
        }
        else if(pops[i]>=60)
        {
            blue[i]=bluemap[6];
        }
    }
    
    
    
}
