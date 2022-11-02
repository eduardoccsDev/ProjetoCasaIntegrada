/*
 WiFi Web Server LED Blink

 A simple web server that lets you blink an LED via the web.
 This sketch will print the IP address of your WiFi Shield (once connected)
 to the Serial monitor. From there, you can open that address in a web browser
 to turn on and off the LED on pin 5.

 If the IP address of your shield is yourAddress:
 http://yourAddress/H turns the LED on
 http://yourAddress/L turns it off

 This example is written for a network using WPA encryption. For
 WEP or WPA, change the Wifi.begin() call accordingly.

 Circuit:
 * WiFi shield attached
 * LED attached to pin 5

 created for arduino 25 Nov 2012
 by Tom Igoe

ported for sparkfun esp32 
31.01.2017 by Jan Hendrik Berlin
 
 */

#include <WiFi.h>

const char* ssid     = "brisa-1403078";
const char* password = "1tite2wp";

WiFiServer server(80);

void setup()
{
    Serial.begin(115200);
    pinMode(13, OUTPUT);      // PINO DO LED
    pinMode(12, OUTPUT);      // PINO DO LED
    pinMode(14, OUTPUT);      // PINO DO LED
    pinMode(27, OUTPUT);      // PINO DO LED

    delay(10);

    // We start by connecting to a WiFi network

    Serial.println();
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected.");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    
    server.begin();

}

int value = 0;

void loop(){
 WiFiClient client = server.available();   // listen for incoming clients

  if (client) {                             // if you get a client,
    Serial.println("New Client.");           // print a message out the serial port
    String currentLine = "";                // make a String to hold incoming data from the client
    while (client.connected()) {            // loop while the client's connected
      if (client.available()) {             // if there's bytes to read from the client,
        char c = client.read();             // read a byte, then
        Serial.write(c);                    // print it out the serial monitor
        if (c == '\n') {                    // if the byte is a newline character

          // if the current line is blank, you got two newline characters in a row.
          // that's the end of the client HTTP request, so send a response:
          if (currentLine.length() == 0) {
            // HTTP headers always start with a response code (e.g. HTTP/1.1 200 OK)
            // and a content-type so the client knows what's coming, then a blank line:
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println();

            // the content of the HTTP response follows the header:
            client.print("<html>");
              client.print("<head>");
                client.print("<meta charset='UTF-8'>");
                client.print("<meta http-equiv='X-UA-Compatible' content='IE=edge'");
                client.print("name='viewport' content='width=device-width, initial-scale=1.0'");
                client.print("<title>CASA INTEGRADA</title>");
                //CSS
                client.print("<style>body{height:100vh;margin:0px;display:grid;grid-template-rows:120px 1fr 60px;grid-template-columns:1fr;grid-template-areas:'cabecalho''principal''rodape';}</style>");
                client.print("<style>.cabecalho{grid-area: cabecalho;background-color: #381d97;color:#fff;display:flex;flex-direction: column;justify-content: center;align-items: center;padding-bottom: 10px;z-index: 1;box-shadow: 0px 4px 10px -2px rgba(0, 0, 0, 0.55);}</style>");
                client.print("<style>.cabecalho > h1{ margin:0px;font-weight:300;font-size:2.8rem;}.cabecalho > h2{margin: 0px;font-weight: 200;font-size: 1.6rem;}.principal{grid-area: principal;background-color: #f0f0f0;height: calc(100vh - 180px);padding: 20px;}</style>");
                client.print("<style>.conteudo{position:realive;height:100%;overflow-y: scroll;background-color: #fff;padding: 20px;box-shadow:0px 0px 25px 0px rgba(0, 0, 0, 0.2);}</style>");
                client.print("<style>.rodape{grid-area: rodape;background-color: #381d97;display:flex;justify-content: center;align-items: center;font-size: 1.2rem;padding-inline: 20px;color:#fff;}</style>");
                client.print("<style>.modulos{display:flex;flex-wrap: wrap;justify-content: space-around;}.modulo{flex-basis: 32%;margin-bottom:20px;border-radius:5px;}.modulo > h3{margin:0px;color: #fff;font-weight:300;font-size: 1.5rem;padding: 10px 20px;background-color: #381d97;}</style>");
                client.print("<style>.modulo > ul {margin:0px;padding:10px;list-style: none;}.modulo > ul > li{padding: 5px;font-size: 1.2rem;cursor: pointer;}.modulo > ul > li > a{display: flex;text-decoration: none;color:#222;}.modulo > ul > li:hover{background-color: #eee;}</style>");
                client.print("<style>.modulo.verde {border: 2px solid darkgreen;}.modulo.verde > h3{background-color: darkgreen;}.modulo.azul {border: 2px solid darkblue;}.modulo.azul > h3{background-color: darkblue;}</style>");
                //FIM CSS
              client.print("</head>");
              client.print("<body>");
                client.print("<header class='cabecalho'>");
                   client.print("<h1>Casa Integrada 1.0</h1>");
                   client.print("<h2>Projeto IOT</h2>");
                client.print("</header>");
                client.print("<main class='principal'>");
                  client.print("<div class='conteudo'>");
                    client.print("<nav class='modulos'>");
                      client.print("<div class='modulo verde'>");
                        client.print("<h3>LIGAR LUZES</h3>");
                        //BOTÕES
                        client.print("<ul>");
                          client.print("<li>");
                            client.print("<a href='/LS'>LIGAR LUZ DA SALA</a>");                            
                          client.print("</li>");
                          client.print("<li>");
                            client.print("<a href='/LC'>LIGAR LUZ DA COZINHA</a>");                            
                          client.print("</li>");
                          client.print("<li>");
                            client.print("<a href='/LQ'>LIGAR LUZ DO QUARTO</a>");                            
                          client.print("</li>");
                          client.print("<li>");
                            client.print("<a href='/LG'>LIGAR LUZ DA GARAGEM</a>");                            
                          client.print("</li>");
                          client.print("<li>");
                            client.print("<a href='/LT'>LIGAR TODAS AS LUZES</a>");                            
                          client.print("</li>");
                        client.print("</ul>");
                        //FIM BOTÕES
                      client.print("</div>");
                      client.print("<div class='modulo azul'>");
                        client.print("<h3>APAGAR LUZES</h3>");
                        //BOTÕES
                        client.print("<ul>");
                          client.print("<li>");
                            client.print("<a href='/AS'>APAGAR LUZ DA SALA</a>");                            
                          client.print("</li>");
                          client.print("<li>");
                            client.print("<a href='/AC'>APAGAR LUZ DA COZINHA</a>");                            
                          client.print("</li>");
                          client.print("<li>");
                            client.print("<a href='/AQ'>APAGAR LUZ DO QUARTO</a>");                            
                          client.print("</li>");
                          client.print("<li>");
                            client.print("<a href='/AG'>APAGAR LUZ DA GARAGEM</a>");                            
                          client.print("</li>");
                          client.print("<li>");
                            client.print("<a href='/AT'>APAGAR TODAS AS LUZES</a>");                            
                          client.print("</li>");
                        client.print("</ul>");
                        //FIM BOTÕES
                      client.print("</div>");
                    client.print("</nav>");
                  client.print("</div>");
                client.print("</main>");
                client.print("<footer>");
                  client.print("<p>DESENVOLVIDO POR: EDUARDO CASTRO</p>");
                client.print("</footer>");                
              client.print("</body>");
            client.print("</html>");

            // The HTTP response ends with another blank line:
            client.println();
            // break out of the while loop:
            break;
          } else {    // if you got a newline, then clear currentLine:
            currentLine = "";
          }
        } else if (c != '\r') {  // if you got anything else but a carriage return character,
          currentLine += c;      // add it to the end of the currentLine
        }

        // Check to see if the client request was "GET /H" or "GET /L":
        if (currentLine.endsWith("GET /LS")) {
          digitalWrite(13, HIGH);               
        }
        if (currentLine.endsWith("GET /AS")) {
          digitalWrite(13, LOW);                
        }
        if (currentLine.endsWith("GET /LC")) {
          digitalWrite(12, HIGH);               
        }
        if (currentLine.endsWith("GET /AC")) {
          digitalWrite(12, LOW);                
        }
        if (currentLine.endsWith("GET /LQ")) {
          digitalWrite(14, HIGH);               
        }
        if (currentLine.endsWith("GET /AQ")) {
          digitalWrite(14, LOW);                
        }
        if (currentLine.endsWith("GET /LG")) {
          digitalWrite(27, HIGH);               
        }
        if (currentLine.endsWith("GET /AG")) {
          digitalWrite(27, LOW);                
        }
        if (currentLine.endsWith("GET /LT")) {
          digitalWrite(13, HIGH);
          digitalWrite(12, HIGH);
          digitalWrite(14, HIGH);
          digitalWrite(27, HIGH);               
        }
        if (currentLine.endsWith("GET /AT")) {
          digitalWrite(13, LOW);
          digitalWrite(12, LOW);
          digitalWrite(14, LOW);
          digitalWrite(27, LOW);                
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
