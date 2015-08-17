//Particle Photon code
//Bealgebone Tx pin to Photon Rx pin
int i=0;

void setup() 
{
    
//Serial to computer
Serial.begin(9600);

//Serial to receive from BBB
Serial1.begin(9600);
}

void loop() 
{
String test = "";
test=Serial1.read();

// -1 connected, no data
// 0 not connected
// ## incoming data

if(test=="-1")
{
    Spark.publish("Status", "Going down for the long sleep");
    
    delay(3600000);
}

else if(test=="0")
{
    Spark.publish("Status", "Lost Connection");
    //Make LED ring blink
}

else{
    Spark.publish(test);
    delay(500);
}

}
