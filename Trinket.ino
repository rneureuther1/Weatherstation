// Adafruit Trinket code
// Bealgebone Tx pin to Trinket Rx pin
// Adruino shares the same buffer for computer Serial and RxTx pins

void setup() 
{
    
//Serial setup
Serial.begin(9600);
pinMode(13, OUTPUT);
digitalWrite(13, LOW);
}

void loop() 
{

int test2;
test2=Serial.read();

// -1 connected, no data
// 0 not connected
// ## incoming data

if(test2==-1)
{
    delay(5000);
}

else if(test2==0)
{

}

else{
    // If data is recieved blink twice
digitalWrite(13, HIGH);
delay(500);
digitalWrite(13, LOW);
delay(500);
digitalWrite(13, HIGH);
delay(500);
digitalWrite(13, LOW);
    delay(3000);
}

}
