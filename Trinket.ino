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
int redmap[] = {0, 3, 140, 50, 250, 255, 255};
int greenmap[] = {175, 130, 255, 205, 220, 190, 0};
int bluemap[] = {240, 237, 0, 50, 0, 0, 0};

// Dynamic arrays change with incoming weather data
// Pops (Probability of Precipitation) stored by index based on cooresponding hour of day
int pops[24];//={0,10,20,30,40,50,60,70,0,10,20,30,40,50,60,70,0,10,20,30,40,50,60,5};
int red[24];
int green[24];
int blue[24];

void setup()
{
  // Serial setup
  Serial.begin(9600);

  // Default values
  for (int i = 0; i < 24; i++)
  {
    //pops[i]  = 100;
    red[i]   = 0;
    green[i] = 0;
    blue[i]  = 0;
  }

  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);


  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  startupAnimation();

}
int test;
void loop()
{
  
  test = Serial.peek();

  //Beaglebone transmits data in the form of H(n) P(n) H(n+1) P(n+1)...starting with first hour available from
  //      Wundergound site
  // -1: connected, no data
  //  0: signal lost
  //  #: incoming data

  if (test == -1)
  {
    delay(5000);
  }

  else if (test == 0)
  {
    // Blink the Ring Red on and off
    for (uint16_t i = 0; i < 24; i++)
    {
      strip.setPixelColor(i, strip.Color(30, 0, 90));
    }
    strip.show();

    delay(1000);

    for (uint16_t i = 0; i < 24; i++)
    {
      strip.setPixelColor(i, strip.Color(0, 0, 0));
    }
    strip.show();

    delay(1000);
  }

  else
  {
    // If data is recieved, blink onboard Trinket LED twice
    blink(13, 2);
    // Allow data to keep coming in
    delay(8000);

    // Update the pops array
   getData();

    // Update the colors
    findColors();

    // Assign pixel colors
    for (uint16_t i = 0; i < 24; i++)
    {
      strip.setPixelColor(i, strip.Color(red[i], green[i], blue[i]));
    }

    //Show colors
    strip.show();
    digitalWrite(13, LOW);

    blink(13, 2);
    delay(3000);

    clearBuffer();
  }
}


// Simple blink
void blink(int pin, int times)
{

  for (int i = 0; i < times; i++)
  {
    digitalWrite(pin, LOW);
    delay(50);
    digitalWrite(pin, HIGH);
    delay(150);
    digitalWrite(pin, LOW);
    delay(50);
  }
  return;
}

//Process incoming serial data from Beaglebone Black
void getData()
{
  int digit1, digit2;
  int hour, pop, currenthour;
  char trash;
  int iteration=0;
  while (Serial.peek() > 0)
  {
    blink(13,1);
    
    if (Serial.peek() == ';')
    {
      // Get rid of the trash character
      trash = Serial.read();
      // Skip the rest of this iteration of the loop
      continue;
    }

    //Get the first hour digit
    digit1 = (Serial.read() - '0');

    //If the hour has double digits, get the second digit
    if (Serial.peek() != ';')
    {
      digit2 = (Serial.read() - '0');
      hour = ((10 * digit1) + digit2);
    }
    else
    {
      hour = digit1;
    }

      
    // We don't want to loop back over 24 hours in advance. We must store the current hour
      // so that we dont go past it when scanning in the data
    if(iteration==0)
    {
      currenthour = hour;
    }

    // Now we know the next item in the buffer is a ';' so trash it
    trash = Serial.read();

    //Get the first pop digit
    digit1 = (Serial.read() - '0');

    //If the pop has double digits, get the second digit
    if (Serial.peek() != ';')
    {
      digit2 = (Serial.read() - '0');
      pop = ((10 * digit1) + digit2);
    }
    else
    {
      pop = digit1;
    }
      
    //Write the data we just collected, so long as we are not looping back over 24 hours
    if(hour != currenthour || ((hour==currenthour) && (iteration==0)) )
    {
      pops[hour] = pop;
      iteration=99;
    }
    else
    {
      // We don't need more than 24 hours data; clear the buffer and stop scanning
      clearBuffer();
      break;
    }

  }
  
}

void clearBuffer(){
   while (Serial.available() > 0)
   {
     char k = Serial.read();
     
     delay(1);
   }
   delay(1);
}
//Assign colors based on the pop
//Assign colors based on the pop
int findColors()
{
  for (int i = 0; i < 24; i++)
  {
    if (pops[i] < 10)
    {
      red[i] = redmap[0];
      green[i] = greenmap[0];
      blue[i] = bluemap[0];
    }
    else if (pops[i] < 20)
    {
      red[i] = redmap[1];
      green[i] = greenmap[1];
      blue[i] = bluemap[1];
    }
    else if (pops[i] < 30)
    {
      red[i] = redmap[2];
      green[i] = greenmap[2];
      blue[i] = bluemap[2];
    }
    else if (pops[i] < 40)
    {
      red[i] = redmap[3];
      green[i] = greenmap[3];
      blue[i] = bluemap[3];
    }
    else if (pops[i] < 50)
    {
      red[i] = redmap[4];
      green[i] = greenmap[4];
      blue[i] = bluemap[4];
    }
    else if (pops[i] < 60)
    {
      red[i] = redmap[5];
      green[i] = greenmap[5];
      blue[i] = bluemap[5];
    }
    else if (pops[i] >= 60)
    {
      red[i] = redmap[6];
      green[i] = greenmap[6];
      blue[i] = bluemap[6];
    }
  }

}

void startupAnimation()
{
  for (int i = 0; i < 24; i++) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, strip.Color(0, 150, 0)); // Moderately bright green color.

    strip.show(); // This sends the updated pixel color to the hardware.

    delay(50); // Delay for a period of time (in milliseconds).

  }

  for (int i = 24; i >= 0; i--) {

    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    strip.setPixelColor(i, strip.Color(0, 0, 0));

    strip.show(); // This sends the updated pixel color to the hardware.

    delay(50); // Delay for a period of time (in milliseconds).

  }

}
