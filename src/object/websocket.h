#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <Arduino.h>
#include <AsyncWebSocket.h>

extern AsyncWebSocket ws;
extern bool ledState;

void notifyClients();
void handleWebSocketMessage(void *arg, uint8_t *data, size_t len);
void onEvent(AsyncWebSocket *server, AsyncWebSocketClient *client, AwsEventType type, void *arg, uint8_t *data, size_t len);
void initWebSocket(AsyncWebServer *server);
String processor(const String& var);

#endif