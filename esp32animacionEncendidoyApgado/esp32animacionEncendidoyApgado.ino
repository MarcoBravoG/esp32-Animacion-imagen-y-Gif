#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// Reemplaza con tu red y contraseña
const char* ssid = "Hacker";
const char* password = "123456789";

// Crea el servidor web
AsyncWebServer server(80);

// Define el pin del LED
const int ledPin = 2;

const char* index_html = R"rawliteral(
<!DOCTYPE html>
<html>
<head>
  <title>Controla el LED</title>
</head>
<body>
  <h1>Controla el LED</h1>
  <button onclick="toggleLED('on')">Encender</button>
  <button onclick="toggleLED('off')">Apagar</button>
  <br>
  <img id="ledImage" src="https://c.tenor.com/NVfOOmB8PfsAAAAC/goool-gol.gif" width="200">
  <script>
    function toggleLED(state) {
      var xhttp = new XMLHttpRequest();
      xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
          if (state === 'on') {
            document.getElementById("ledImage").src = "http://pngimg.com/uploads/football_player/football_player_PNG128.png";
          } else {
            document.getElementById("ledImage").src = "https://c.tenor.com/NVfOOmB8PfsAAAAC/goool-gol.gif";
          }
        }
      };
      xhttp.open("GET", state, true);
      xhttp.send();
    }
  </script>
</body>
</html>
)rawliteral";

void setup() {
  // Inicia la comunicación serial
  Serial.begin(115200);

  // Configura el pin del LED como salida
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);

  // Conecta a la red WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }

  // Conexión exitosa
  Serial.println("Conectado a WiFi");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // Servir la página principal
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html);
  });

  // Ruta para encender el LED
  server.on("/on", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, HIGH);
    request->send(200, "text/plain", "LED Encendido");
  });

  // Ruta para apagar el LED
  server.on("/off", HTTP_GET, [](AsyncWebServerRequest *request){
    digitalWrite(ledPin, LOW);
    request->send(200, "text/plain", "LED Apagado");
  });

  // Inicia el servidor
  server.begin();
}

void loop() {
  // No es necesario código en el loop para este ejemplo
}

