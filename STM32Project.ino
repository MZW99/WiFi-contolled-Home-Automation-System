#include "SparkFun_SHTC3.h"
#include "Arduino.h"
SHTC3 mySHTC3;
String str;
int flag = 0;
int setting = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(PB0, OUTPUT);
  pinMode(PB1, OUTPUT);

//  pinMode(PB10, OUTPUT);
//  pinMode(PA2, OUTPUT);
//  pinMode(PA3, INPUT);
  Serial.begin(115200);
  Serial2.begin(19200);// Begin Serial 
  while(Serial == false){};                                   // Wait for the serial connection to start up
  Serial.println("SHTC3 Example 1 - Basic Readings");    // Title
  Wire.begin();
  Serial.print("Beginning sensor. Result = ");           // Most SHTC3 functions return a variable of the type "SHTC3_Status_TypeDef" to indicate the status of their execution 
  errorDecoder(mySHTC3.begin());                              // To start the sensor you must call "begin()", the default settings use Wire (default Arduino I2C port)
  Serial.println();
  Serial.println("\n\n");
  Serial.println("Waiting for 5 seconds so you can read this info ^^^");
  Serial.flush();
  
  delay(500);  
}

void loop() {
  // put your main code here, to run repeatedly:
  SHTC3_Status_TypeDef result = mySHTC3.update();             // Call "update()" to command a measurement, wait for measurement to complete, and update the RH and T members of the object
//  printInfo();                                                // This function is used to print a nice little line of info to the serial port
  float curr_hum = mySHTC3.toPercent();
  float curr_temp = mySHTC3.toDegC();
  String command = "";
  
//  digitalWrite(PA2, curr_hum);
//  digitalWrite(PB10, curr_temp);
//  Serial.println(curr_temp);
  
  while (Serial2.available()) {
    command = Serial2.readString();
    delay(2);
    command.replace(" ", "");
    command = command.substring(0, 2);
    Serial.println(command);
    if (isNumeric(command)){
//      command = command.substring(0, 2);
      setting = command.toInt();
//      Serial.println(command);
      flag = 1;
      
    }
    else{
      flag = 0;  
    }
    
  }
  if (flag == 1){
    if (setting >= curr_temp){
      digitalWrite(PB0, HIGH);
      digitalWrite(PB1, LOW);
    }
    else{
      digitalWrite(PB0, LOW);
      digitalWrite(PB1, HIGH);
    }
  }
  else{
    if (command.indexOf("A") >= 0){
      digitalWrite(PB0, HIGH);
      digitalWrite(PB1, HIGH);
    }
    else if (command.indexOf("B") >= 0){
      digitalWrite(PB0, LOW);
      digitalWrite(PB1, LOW);
    }
    else if (command.indexOf("C") >= 0){
      digitalWrite(PB0, LOW);
      digitalWrite(PB1, HIGH);
    }
    else if (command.indexOf("D") >= 0){
      digitalWrite(PB0, HIGH);
      digitalWrite(PB1, LOW);
    }
  }
  
  str = String("H")+String(curr_hum)+String("T")+String(curr_temp);
  Serial2.println(str);
  Serial2.flush();
  delay(1000);
  
}



void printInfo()
{
  if(mySHTC3.lastStatus == SHTC3_Status_Nominal)              // You can also assess the status of the last command by checking the ".lastStatus" member of the object
  {
    Serial.print("RH = "); 
    Serial.print(mySHTC3.toPercent());                        // "toPercent" returns the percent humidity as a floating point number
    Serial.print("%, T = "); 
    Serial.print(mySHTC3.toDegC());                           // "toDegF" and "toDegC" return the temperature as a flaoting point number in deg F and deg C respectively 
    Serial.println(" deg C");
    Serial.flush();
  }
  else
  {
    Serial.print("Update failed, error: "); 
    errorDecoder(mySHTC3.lastStatus);
    Serial.println();
    Serial.flush();
  }
}

void errorDecoder(SHTC3_Status_TypeDef message)                             // The errorDecoder function prints "SHTC3_Status_TypeDef" resultsin a human-friendly way
{
  switch(message)
  {
    case SHTC3_Status_Nominal : Serial.print("Nominal"); break;
    case SHTC3_Status_Error : Serial.print("Error"); break;
    case SHTC3_Status_CRC_Fail : Serial.print("CRC Fail"); break;
    default : Serial.print("Unknown return code"); break;
  }
}

boolean isNumeric(String str) {
    unsigned int stringLength = str.length();
 
    if (stringLength == 0) {
        return false;
    }
 
    boolean seenDecimal = false;
 
    for(unsigned int i = 0; i < stringLength; ++i) {
        if (isDigit(str.charAt(i))) {
            continue;
        }
 
        if (str.charAt(i) == '.') {
            if (seenDecimal) {
                return false;
            }
            seenDecimal = true;
            continue;
        }
        return false;
    }
    return true;
}
