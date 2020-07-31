#include <ESP8266WiFi.h>
WiFiServer server(80);

void setup() {
  pinMode(14,OUTPUT);
Serial.begin(115200);
WiFi.begin("enderkanal","parola123");
  while(WiFi.status()!=WL_CONNECTED){
    delay(500);
    Serial.println("enderkanal ağına bağlanamadım.");
  }
Serial.println("ağa bağlandım, ip adresim: ");
Serial.println(WiFi.localIP());
server.begin();
}

String myHtmlPage()
{
  String htmlPage =
     String("HTTP/1.1 200 OK\r\n") +
            "Content-Type: text/html\r\n charset=UTF-8" +
            "Connection: close\r\n" +  // the connection will be closed after completion of the response
            "Refresh: 5\r\n" +  // refresh the page automatically every 5 sec
            "\r\n" +
            "<!DOCTYPE HTML>" +
            "<html>" +
            "<body>" +
      "<h2>MERHABA BEN ESP SERVER</h2>"+
      "<a href=\"http://192.168.43.155/lediYak\" >LED ON</a>"+
      "</br>"+
       "<a href=\"http://192.168.43.155/lediKapat\" >LED OFF</a>"+
      "</body>" +
            "</html>" +
            "\r\n";
  return htmlPage;
}

void loop() {
  WiFiClient client=server.available();
  if(client){
    while(client.connected()){
      if(client.available()){
        String line=client.readStringUntil('\r');
        Serial.println(line);
          if(line=="GET /lediYak HTTP/1.1"){
            digitalWrite(14,HIGH);
          }
          if(line=="GET /lediKapat HTTP/1.1"){
            digitalWrite(14,LOW);
          }              
          if(line.length()==1 && line[0]=='\n'){
            client.println(myHtmlPage());
            break;
      }
    }
  }
  delay(1);
  client.stop();
  Serial.println("İstemci Bağlantıyı Kesti");
  }
}
