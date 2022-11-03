#include <WiFi.h>

const char* ssid     = "brisa-1403078";
const char* password = "1tite2wp";

WiFiServer server(80);

//DECLARAR OS ESTADOS
bool ledStatus = false;
bool ledStatus2 = false;
bool ledStatus3 = false;
bool ledStatus4 = false;
bool ledStatusT = false;

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
                client.print("<style>.card {background-color: #313131;color: #fff;padding: 10px 12px;border-radius: 15px;border: solid 2px #000;margin: 15px auto;box-shadow: 0px 0px 10px 0px #8000ff;display: flex;align-content: center;justify-content: center;width: 453px;}</style>");
                client.print("<style>.comodo{margin: auto 10px;}.estado.off {background-color: #c81919;padding: 5px 10px;border-radius: 5px;box-shadow: 0px 0px 10px 0px #c81919;margin: auto;margin-right: auto;margin-right: 44px;}.ligar{margin: auto 14px;text-decoration: none;color: #fff;background-color: #199119;padding: 5px 10px;border-radius: 5px;}</style>");
                client.print("<style>.desligar{margin: auto 14px;text-decoration: none;color: #fff;background-color: #c81919;padding: 5px 10px;border-radius: 5px;}.estado.on {background-color: #199119;padding: 5px 10px;border-radius: 5px;box-shadow: 0px 0px 10px 0px #199119;margin: auto;margin-right: auto;margin-right: auto;margin-right: auto;margin-right: 44px;}</style>");
                //FIM CSS
              client.print("</head>");
              client.print("<body>");
                client.print("<header class='cabecalho'>");
                   client.print("<h1>Casa Integrada 1.0</h1>");
                   client.print("<h2>Projeto IOT</h2>");
                client.print("</header>");
                client.print("<main class='principal'>");
                  client.print("<div class='conteudo'>");
                  //CARDS
                    client.print("<div class='card'>");
                      client.print("<p class='comodo'>LUZ DA SALA</p>");
                      ledStatus ? client.print("<div class='estado on'>ON</div>") : client.print("<div class='estado off'>OFF</div>");
                      client.print("<p class='devisor'>|</p>");
                      client.print("<a class='ligar' href='/LS'>LIGAR</a><br><a class='desligar' href='/AS'>DESLIGAR</a>");
                    client.print("</div>");
                    client.print("<div class='card'>");
                      client.print("<p class='comodo'>LUZ DA COZINHA</p>");
                      ledStatus2 ? client.print("<div class='estado on'>ON</div>") : client.print("<div class='estado off'>OFF</div>");
                      client.print("<p class='devisor'>|</p>");
                      client.print("<a class='ligar' href='/LC'>LIGAR</a><br><a class='desligar' href='/AC'>DESLIGAR</a>");
                    client.print("</div>");
                    client.print("<div class='card'>");
                      client.print("<p class='comodo'>LUZ DO QUARTO</p>");
                      ledStatus3 ? client.print("<div class='estado on'>ON</div>") : client.print("<div class='estado off'>OFF</div>");
                      client.print("<p class='devisor'>|</p>");
                      client.print("<a class='ligar' href='/LQ'>LIGAR</a><br><a class='desligar' href='/AQ'>DESLIGAR</a>");
                    client.print("</div>");
                    client.print("<div class='card'>");
                      client.print("<p class='comodo'>LUZ DA GARAGEM</p>");
                      ledStatus4 ? client.print("<div class='estado on'>ON</div>") : client.print("<div class='estado off'>OFF</div>");
                      client.print("<p class='devisor'>|</p>");
                      client.print("<a class='ligar' href='/LG'>LIGAR</a><br><a class='desligar' href='/AG'>DESLIGAR</a>");
                    client.print("</div>");
                    client.print("<div class='card'>");
                      client.print("<p class='comodo'>TODAS AS LUZES</p>");
                      ledStatusT ? client.print("<div class='estado on'>ON</div>") : client.print("<div class='estado off'>OFF</div>");
                      client.print("<p class='devisor'>|</p>");
                      client.print("<a class='ligar' href='/LT'>LIGAR</a><br><a class='desligar' href='/AT'>DESLIGAR</a>");
                    client.print("</div>");
                    //FIM CARDS                    
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
          ledStatus = true;
          digitalWrite(13, ledStatus);               
        }
        if (currentLine.endsWith("GET /AS")) {
          ledStatus = false;
          digitalWrite(13, ledStatus);                
        }
        if (currentLine.endsWith("GET /LC")) {
          ledStatus2 = true;
          digitalWrite(12, ledStatus2);               
        }
        if (currentLine.endsWith("GET /AC")) {
          ledStatus2 = false;
          digitalWrite(12, ledStatus2);                
        }
        if (currentLine.endsWith("GET /LQ")) {
          ledStatus3 = true;
          digitalWrite(14, ledStatus3);               
        }
        if (currentLine.endsWith("GET /AQ")) {
          ledStatus3 = false;
          digitalWrite(14, ledStatus3);                
        }
        if (currentLine.endsWith("GET /LG")) {
          ledStatus4 = true;
          digitalWrite(27, ledStatus4);               
        }
        if (currentLine.endsWith("GET /AG")) {
          ledStatus4 = false;
          digitalWrite(27, ledStatus4);                
        }
        if (currentLine.endsWith("GET /LT")) {
          ledStatusT = true;
          digitalWrite(13, ledStatusT);
          digitalWrite(12, ledStatusT);
          digitalWrite(14, ledStatusT);
          digitalWrite(27, ledStatusT);               
        }
        if (currentLine.endsWith("GET /AT")) {
          ledStatusT = false;
          digitalWrite(13, ledStatusT);
          digitalWrite(12, ledStatusT);
          digitalWrite(14, ledStatusT);
          digitalWrite(27, ledStatusT);                
        }
      }
    }
    // close the connection:
    client.stop();
    Serial.println("Client Disconnected.");
  }
}
