//=============================================================================
//  OTAUpdater Header
//-----------------------------------------------------------------------------
//  for:    chickenCoop
//  author: Joe Heumer
//  create: 13 January 2024
//  file:   OTAUpdater.hpp
//=============================================================================

#ifndef __OTAUPDATER_H__
#define __OTAUPDATER_H__

#ifdef ESP32
    #include <WebServer.h> // Für ESP32
    #include <Update.h>




//-----------------------------------------------------------------------------
// Class
//-----------------------------------------------------------------------------

class OTAUpdater {
    //--------------------------- Methods -----------------------------------------
    public:
        OTAUpdater(WebServer& server) : server(server) {}

        void handleFirmwareUpload() {
            HTTPUpload& upload = server.upload();
            if (upload.status == UPLOAD_FILE_START) {
                Serial.printf("Update: %s\n", upload.filename.c_str());
                if (!Update.begin(UPDATE_SIZE_UNKNOWN)) {
                    Update.printError(Serial);
                }
            } else if (upload.status == UPLOAD_FILE_WRITE) {
                if (Update.write(upload.buf, upload.currentSize) != upload.currentSize) {
                    Update.printError(Serial);
                }
            } else if (upload.status == UPLOAD_FILE_END) {
                if (Update.end(true)) {
                    Serial.printf("Update Success: %u\nRebooting...\n", upload.totalSize);
                } else {
                    Update.printError(Serial);
                }
            }
        }
    private:
        

    //--------------------------- Variables -----------------------------------------
    public:
    private:
        WebServer& server;

};

#endif
#endif

//=============================================================================
// End of File
//=============================================================================