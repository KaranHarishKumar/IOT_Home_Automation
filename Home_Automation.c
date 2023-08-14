#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>   
#include <ArduinoJson.h>

const char* ssid = "Fazil201";
const char* password = "123456789";

#define BOTtoken "5863622840:AAGNLblMI9CUIU_fzWOuGfKs94vPoY629_A"  

#define CHAT_ID "1628016387"

X509List cert(TELEGRAM_CERTIFICATE_ROOT);

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

int botRequestDelay = 1000;
unsigned long lastTimeBotRan;

const int pin1 = 16;
const int pin2 = 5;
const int pin3 = 4;
const int pin4 = 0;
const int pin5 = 2;

// Handle what happens when you receive new messages
void handleNewMessages(int numNewMessages) {
  Serial.println("handleNewMessages");
  Serial.println(String(numNewMessages));

  for (int i=0; i<numNewMessages; i++) {
  
    String chat_id = String(bot.messages[i].chat_id);
        
    String text = bot.messages[i].text;
    Serial.println(text);

    if (text == "/start") {
      String welcome = "Welcome.\n";
      welcome += "Use the following commands to control your outputs.\n\n";
      welcome += "/bulb1_on to turn bulb1 ON \n";
      welcome += "/bulb1_off to turn bulb1 OFF \n";
      welcome += "/bulb1_state to request current bulb1 state \n";
      welcome += "/bulb2_on to turn bulb2 ON \n";
      welcome += "/bulb2_off to turn bulb2 OFF \n";
      welcome += "/bulb2_state to request current bulb2 state \n";
      welcome += "/bulb3_on to turn bulb3 ON \n";
      welcome += "/bulb3_off to turn bulb3 OFF \n";
      welcome += "/bulb3_state to request current bulb3 state \n";      
      welcome += "/door_state to request current door state \n";
      bot.sendMessage(chat_id, welcome, "");
    }

    //turning bulb1 ON
    if (text == "/bulb1_on") {
      bot.sendMessage(chat_id, "Bulb1 is turned ON", "");
      digitalWrite(pin1, LOW);
    }
    
    //turning bulb1 OFF
    if (text == "/bulb1_off") {
      bot.sendMessage(chat_id, "Bulb1 is turned OFF", "");
      digitalWrite(pin1, HIGH);
    }
    
    //Checking state of bulb1
    if (text == "/bulb1_state") {
      if (digitalRead(pin1)){
        bot.sendMessage(chat_id, "Bulb1 is OFF", "");
      }
      else{
        bot.sendMessage(chat_id, "Bulb1 is ON", "");
      }
    }
    
    //turning bulb2 ON
    if (text == "/bulb2_on") {
      bot.sendMessage(chat_id, "Bulb2 is turned ON", "");
      digitalWrite(pin2, LOW);
    }
    
    //turning bulb2 OFF
    if (text == "/bulb2_off") {
      bot.sendMessage(chat_id, "Bulb2 is turned OFF", "");
      digitalWrite(pin2, HIGH);
    }
    
    //Checking state of bulb2
    if (text == "/bulb2_state") {
      if (digitalRead(pin2)){
        bot.sendMessage(chat_id, "Bulb2 is OFF", "");
      }
      else{
        bot.sendMessage(chat_id, "Bulb2 is ON", "");
      }
    }
    
    //turning bulb3 ON
    if (text == "/bulb3_on") {
      bot.sendMessage(chat_id, "Bulb3 is turned ON", "");
      digitalWrite(pin3, LOW);
    }
    
    //turning bulb3 OFF
    if (text == "/bulb3_off") {
      bot.sendMessage(chat_id, "Bulb3 is turned OFF", "");
      digitalWrite(pin3, HIGH);
    }
    
    //Checking state of bulb3
    if (text == "/bulb3_state") {
      if (digitalRead(pin3)){
        bot.sendMessage(chat_id, "Bulb3 is OFF", "");
      }
      else{
        bot.sendMessage(chat_id, "Bulb3 is ON", "");
      }
    }


    if(text=="/door_state")
    {
      if(digitalRead(pin5))
      {
        bot.sendMessage(chat_id,"Door is open");
      }
      else
      {
        bot.sendMessage(chat_id,"Door is closed");
      }
    }   
  }
}

void setup() {
  Serial.begin(9600);

    configTime(0, 0, "pool.ntp.org");   
    client.setTrustAnchors(&cert); 

//Configuring the pins in output mode

  pinMode(pin1, OUTPUT);
  digitalWrite(pin1, HIGH);
  pinMode(pin2, OUTPUT);
  digitalWrite(pin2, HIGH);
  pinMode(pin3, OUTPUT);
  digitalWrite(pin3, HIGH);
  pinMode(pin4, OUTPUT);
  digitalWrite(pin4, HIGH);
  pinMode(pin5, INPUT_PULLUP);

//Connecting to WiFi
  
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi..");
  }
Serial.println("Connected to WiFi");  
}

//Checking the Bot repeatedly for inputs
void loop() {

  if(digitalRead(pin5))
      {
        digitalWrite(pin4, LOW);
      }
  else
      {
        digitalWrite(pin4, HIGH);
      }
  if (millis() > lastTimeBotRan + botRequestDelay)  {
    int numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    
    while(numNewMessages) {
      Serial.println("got response");
      handleNewMessages(numNewMessages);
      numNewMessages = bot.getUpdates(bot.last_message_received + 1);
    }
    lastTimeBotRan = millis();
  }
}