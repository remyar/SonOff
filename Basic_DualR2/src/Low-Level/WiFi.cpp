//================================================================================================//
//                                                                                                //
// PROJET       : DongleWifi GoodRace                                                             //
// MODULE       : WiFi                                                                           //
// DESCRIPTION  :                                                                                 //
// CREATION     : 27/01/2020                                                                      //
// HISTORIQUE   :                                                                                 //
//                                                                                                //
//================================================================================================//

//================================================================================================//
//                                        FICHIERS INCLUS                                         //
//================================================================================================//

#include "./WiFi.h"

//================================================================================================//
//                                            DEFINES                                             //
//================================================================================================//

//================================================================================================//
//                                          ENUMERATIONS                                          //
//================================================================================================//

//================================================================================================//
//                                      STRUCTURES ET UNIONS                                      //
//================================================================================================//

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                 VARIABLES PRIVEES ET PARTAGEES                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------------------------//
//---                                         Privees                                          ---//
//------------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------------//
//---                                        Partagees                                         ---//
//------------------------------------------------------------------------------------------------//

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                 FONCTIONS PRIVEES ET PARTAGEES                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------------------------//
//---                                         Privees                                          ---//
//------------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------------//
//---                                        Partagees                                         ---//
//------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------
// FONCTION    : WIFI_Init
//
// DESCRIPTION : Initialisation de la carte : GPIO, Clocks, Interruptions...
//--------------------------------------------------------------------------------------------------
void WIFI_Init(void)
{
    WiFi.mode(WIFI_STA);
}

bool WIFI_WPSProcess(void)
{

    if (DEBUG_WIFI)
    {
        Serial.println("WPS config start");
    }
    bool wpsSuccess = WiFi.beginWPSConfig();

    if (wpsSuccess)
    {
        String newSSID = WiFi.SSID();
        if (DEBUG_WIFI)
        {
            Serial.println(WiFi.psk());
        }
        if (newSSID.length() > 0)
        {
            // WPSConfig has already connected in STA mode successfully to the new station.
            if (DEBUG_WIFI)
            {
                Serial.printf("WPS finished. Connected successfull to SSID '%s'\r\n", newSSID.c_str());
            }
        }
        else
        {
            wpsSuccess = false;
        }
    }

    if (wpsSuccess == false)
    {
        if (DEBUG_WIFI)
        {
            Serial.println("Failed to connect with WPS :-(");
        }
    }

    return wpsSuccess;
}

void WIFI_Connect(void)
{
    if (DEBUG_WIFI)
    {
        Serial.println(WiFi.SSID());
        Serial.println(WiFi.psk());
    }

    String hostname = "SonOff_";
    hostname += WiFi.macAddress();
    WiFi.hostname(hostname);
    WiFi.begin(WiFi.SSID().c_str(), WiFi.psk().c_str());

}

bool WIFI_IsConnected(void)
{
    return (WiFi.status() == WL_CONNECTED);
}

bool WIFI_IsConnectedFailed(void)
{
    return (WiFi.status() == WL_CONNECT_FAILED);
}

bool WIFI_IsDisconnected(void)
{
    return (WiFi.status() == WL_DISCONNECTED);
}

void WIFI_PrintMyIP(void)
{
    if (DEBUG_WIFI)
    {
        Serial.println(WiFi.localIP());
    }
}

void WIFI_PrintServerIP(void)
{
    if (DEBUG_WIFI)
    {
        Serial.println(WiFi.gatewayIP().toString());
    }
}

IPAddress WIFI_GetServerIp(void)
{
    return WiFi.gatewayIP();
}

String WIFI_GetMacAddress(void){
    return WiFi.macAddress();
}