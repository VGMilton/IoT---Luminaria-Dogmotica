#include <Firebase_ESP_Client.h>
#include <WiFi.h>
#include <addons/TokenHelper.h>
#include <ArduinoJson.h>
#define FIREBASE_USE_PSRAM

// Define the WiFi credentials
const char* WIFI_SSID = "******";
const char* WIFI_PASSWORD = "*******";
const char* API_KEY = "APIKEY FIREBASE";
const char* FIREBASE_PROJECT_ID = "PROYECTID";
const char* USER_EMAIL = "EMAIL";//CONFIGURAR UN EMAIL Y CONTRASEÑA EN AUTHENTICATION
const char* USER_PASSWORD = "PASS";

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

void setupWiFi() {
  Serial.print("Connecting to Wi-Fi");
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
}

void setupFirebase() {
  config.api_key = API_KEY;
  auth.user.email = USER_EMAIL;
  auth.user.password = USER_PASSWORD;
  config.token_status_callback = tokenStatusCallback;  // Ver addons/TokenHelper.h
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void setup() {
  Serial.begin(115200);
  Serial.printf("Firebase Client v%s\n\n", FIREBASE_CLIENT_VERSION);
  setupWiFi();
  setupFirebase();
}

void loop() {
  String path = "controlLED";//RUTA DE COLECCION
  FirebaseJson json;

  if (Firebase.Firestore.getDocument(&fbdo, FIREBASE_PROJECT_ID, "", path.c_str(), "")) {

    StaticJsonDocument<1024> doc;
    DeserializationError error = deserializeJson(doc, fbdo.payload().c_str());

    if (!error) {
      for (JsonObject document : doc["documents"].as<JsonArray>()) {
        const char* document_name = document["name"];//PARAMETRO NOMBRE
        //Serial.print(document_name);
        const bool state = document["fields"]["encender"]["booleanValue"];//PARAMETRO DE CAMPOS A REVISAR
        Serial.print(" : ");
        if (strstr(document_name, "LED1") != nullptr) {//COMPARAR NOMBRE CON  RESULTADO ESPERADO LED1
          state ? Serial.print("Control 1 On") : Serial.print("Control 1 OFF");
        }
        else if (strstr(document_name, "LED2") != nullptr) {
          state ? Serial.print("Control 2 On") : Serial.print("Control 2 OFF");
        }
        else if (strstr(document_name, "LED3") != nullptr) {
          state ? Serial.print("Control 3 On") : Serial.print("Control 3 OFF");
        }
        else if (strstr(document_name, "LED4") != nullptr) {
          state ? Serial.print("Control 4 On") : Serial.print("Control 4 OFF");
        }
        delay(500);  // Esperar 500 MILIS antes de la próxima lectura
      }
    }
  }
}

