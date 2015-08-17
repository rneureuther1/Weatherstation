//Particle Photon code

int i=0;

void setup() 
{
Serial.begin(9600);
Serial1.begin(9600);
}

void loop() 
{
String test = "";
test=Serial1.read();

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
