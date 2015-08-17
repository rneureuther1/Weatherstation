// Adafruit Trinket code
// Bealgebone Tx pin to Trinket Rx pin
// Adruino shares the same buffer for computer Serial and RxTx pins

void setup() 
{
    
//Serial setup
Serial.begin(9600);

}

void loop() 
{
String test = "";
test=Serial.read();

// -1 connected, no data
// 0 not connected
// ## incoming data

if(test=="-1")
{
    Serial.write("No Data, Sleeping...");
    
    delay(3000);
}

else if(test=="0")
{
    Serial.write("Lost Connection");
    //Make LED ring blink
}

else{
    Serial.write(test);
    delay(500);
}

}
