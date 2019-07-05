    #include <SoftwareSerial.h>
    #include<Servo.h>
    Servo servo;
    SoftwareSerial SIM900A(2,3);
    String data="";
    int i=0;
    char temp[50];
    int loc=0;
    int ldr=4;
    int buzzer=5;
    int smoke=A0;
    int pir=13;
 
    void setup()
    {
      SIM900A.begin(9600);   // Setting the baud rate of GSM Module  
      Serial.begin(9600);    // Setting the baud rate of Serial Monitor (Arduino)
      Serial.println ("SIM900A Ready");
      delay(100);
      Serial.println ("Type s to send message or r to receive message");
      pinMode(8,OUTPUT);
      pinMode(9,OUTPUT);
      pinMode(10,OUTPUT);
      pinMode(11,OUTPUT);
      pinMode(ldr,INPUT);
      pinMode(smoke,INPUT);
      pinMode(buzzer,OUTPUT);
      digitalWrite(8,HIGH);
      digitalWrite(9,HIGH);
      digitalWrite(10,HIGH);
      digitalWrite(11,HIGH);
      pinMode(13,INPUT);
    
    servo.attach(6);

    }
    void loop()
    {
    char character;
      if (Serial.available()>0)
       switch(Serial.read())
      {
        case 's':
          SendMessage();
          break;
        case 'r':
          RecieveMessage();
          break;
        case 'd':
        Serial.println("Message:");
          Serial.print(data);
          break;
      }
     if (SIM900A.available()>0)
      {
      
        character=SIM900A.read();
       Serial.write(character);
       
       //msg[i]=SIM900A.read();
       
       i++;
       data +=character;
       /*if(msg==72e108l11110)
            Serial.println("Succesful");
            else
            Serial.println("Unsuccessful");*/
      }   
      else
        {
          if(data=="")
          {
            }
            else
            {
      //   Serial.println("Received Message is :");
     //     Serial.print(data);
      i++;
      if(i>400)
        {
          compare();
          data="";
          i=0;
        }
        }
        }
      
    if(loc==1)
      {
             int smokeval=analogRead(smoke);
            // Serial.println(smokeval);

                  if(smokeval > 300)
                 {
                       digitalWrite(buzzer,HIGH);
                      // delay(700);
                      // digitalWrite(buzzer,LOW);
                      Serial.println("Fire!!!");
                       SIM900A.println("ATD+916395791526;");
                       delay(10000);
                       SIM900A.println("ATH");
                       digitalWrite(10,LOW);
                       //loc=0;
                     
                }
                else
                 {
                    digitalWrite(buzzer,LOW);
                  }
                int ldrval=digitalRead(ldr);
        if(ldrval==HIGH)
       {
        digitalWrite(buzzer,HIGH);
       Serial.println("Someone Entered");
       }
        else
        digitalWrite(buzzer,LOW);
           
      int pirval=digitalRead(13);
    
        if(pirval==HIGH)    
                {
                  Serial.println("Motion Detected");
                  digitalWrite(buzzer,HIGH);
                  SIM900A.println("ATD6395791526;");
                  delay(10000);
                  SIM900A.println("ATH");
                  }  
                  else
                  {
                    digitalWrite(buzzer,LOW);
                    }
        }


int ldrval=digitalRead(ldr);
        if(ldrval==HIGH)
       {
        digitalWrite(buzzer,HIGH);
       Serial.println("Someone Entered");
       }
        else
        digitalWrite(buzzer,LOW);
      
   //delay(100);
    }
     void SendMessage()
    {
      Serial.println ("Sending Message");
      SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
      delay(1000);
      Serial.println ("Set SMS Number");
      SIM900A.println("AT+CMGS=\"+916395791526\"\r"); //Mobile phone number to send message
      delay(1000);
      Serial.println ("Set SMS Content");
      SIM900A.println("Good morning, how are you doing?");// Messsage content
      delay(100);
      Serial.println ("Finish");
      SIM900A.println((char)26);// ASCII code of CTRL+Z
      delay(1000);
      Serial.println ("Message has been sent ->SMS Selesai dikirim");
    }
     void RecieveMessage()
    {
      Serial.println ("SIM900A Membaca SMS");
    //  delay (1000);
      SIM900A.println("AT+CNMI=2,2,0,0,0"); // AT Command to receive a live SMS
      //delay(1000);
      Serial.write ("Unread Message done");
     }
     void compare()
     {
          Serial.println("comparing string"+data);

      int len=data.length();
      Serial.println(len);
      data.trim();
      Serial.println("Message is : "+data+"\n");
      Serial.println("Number is : "+data.substring(10,20));
      if(data.endsWith("R1OFF") )
        {
          digitalWrite(8,HIGH);
          Serial.println("Lights OFF");
          return;
          }
         if(data.endsWith("R1ON"))
         {
          Serial.println("Lights ON");
          digitalWrite(8,LOW);
          return;
          }

         if(data.endsWith("R2OFF") )
        {
          digitalWrite(9,HIGH);
          Serial.println("Lights 2 OFF");
          return;
          }
         if(data.endsWith("R2ON"))
         {
          Serial.println("Lights 2 ON");
          digitalWrite(9,LOW);
          return;
          }


   if(data.endsWith("R3OFF") )
        {
          digitalWrite(10,HIGH);
          Serial.println("Lights 3 OFF");
          return;
          }
         if(data.endsWith("R3ON"))
         {
          Serial.println("Lights 3 ON");
          digitalWrite(10,LOW);
          return;
          }

   if(data.endsWith("R4OFF") )
        {
          digitalWrite(11,HIGH);
          Serial.println("Lights 4 OFF");
          return;
          }
         if(data.endsWith("R4ON"))
         {
          Serial.println("Lights 4 ON");
          digitalWrite(11,LOW);
          return;
          }
          
          if(data.substring(11,21)=="6395791526")
          {
            Serial.println("call receiving");
            SIM900A.println("ATA");
            }



               if(data.endsWith("ALLOFF") )
        {
          digitalWrite(8,HIGH);
          digitalWrite(9,HIGH);
          digitalWrite(10,HIGH);
          digitalWrite(11,HIGH);

          Serial.println("Lights OFF");
          return;
          }
         if(data.endsWith("ALLON"))
         {
          Serial.println("Lights ON");
          digitalWrite(8,LOW);
          digitalWrite(9,LOW);
          digitalWrite(10,LOW);
          digitalWrite(11,LOW);

          return;
          }
          if(data.endsWith("OUT"))
            {
              Serial.println("MOVING OUT");
              loc=1;
              delay(2000);
              servo.write(25);

              return;
              }
          if(data.endsWith("IN"))
            {
              Serial.println("Moving IN");
              loc=0;
              servo.write(90);

              return;
              }
      }


  /*    void calultra()
      {
        digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  
  
  
 Serial.print(cm);
 Serial.print("cm");
 Serial.println();
  
  pinMode(8,OUTPUT);
  if(cm<25)
          {
            digitalWrite(8,HIGH);
            Serial.println("Lights ON");
             SIM900A.println("ATD+916395791526;");
             delay(1000);
             loc=0;
            }
      delay(250);
        }*/
