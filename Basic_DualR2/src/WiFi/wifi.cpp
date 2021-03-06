//================================================================================================//
//                                                                                                //
// PROJET       : DongleWifi GoodRace                                                             //
// MODULE       : Board                                                                           //
// DESCRIPTION  :                                                                                 //
// CREATION     : 27/01/2020                                                                      //
// HISTORIQUE   :                                                                                 //
//                                                                                                //
//================================================================================================//

//================================================================================================//
//                                        FICHIERS INCLUS                                         //
//================================================================================================//

#include "./wifi.h"
#include "../keyboard/keyboard.h"

//================================================================================================//
//                                            DEFINES                                             //
//================================================================================================//

//================================================================================================//
//                                          ENUMERATIONS                                          //
//================================================================================================//
typedef enum
{
    WIFI_CONNECT = 0,
    WIFI_CONNECT_IN_PROGRESS,
    WIFI_CONNECT_SUCCESS,
    WIFI_WPS_START,
} e_WIFI_STATE;

//================================================================================================//
//                                      STRUCTURES ET UNIONS                                      //
//================================================================================================//

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                 VARIABLES PRIVEES ET PARTAGEES                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------------------------//
//---                                         Privees                                          ---//
//------------------------------------------------------------------------------------------------//
static e_WIFI_STATE eWifiState = WIFI_CONNECT;
static unsigned long _ms = millis();
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
// FONCTION    : KEYBOARD_Init
//
// DESCRIPTION : Initialisation de la carte : GPIO, Clocks, Interruptions...
//--------------------------------------------------------------------------------------------------
void WIFI_TaskInit(void)
{
    WIFI_Init();
    _ms = millis();
}

void WIFI_TaskRun(void)
{

    if (KEYBOARD_IsPushed() && KEYBOARD_IsLongPush())
    {
        eWifiState = WIFI_WPS_START;
    }

    switch (eWifiState)
    {
    case (WIFI_CONNECT):
    {
        WIFI_Connect();
        _ms = millis();
        eWifiState = WIFI_CONNECT_IN_PROGRESS;
        if (DEBUG_WIFI)
        {
            Serial.println("WIFI_CONNECT_IN_PROGRESS");
        }
        break;
    }
    case (WIFI_CONNECT_IN_PROGRESS):
    {
        if (WIFI_IsConnected())
        {
            WIFI_PrintMyIP();
            WIFI_PrintServerIP();
            eWifiState = WIFI_CONNECT_SUCCESS;
            if (DEBUG_WIFI)
            {
                Serial.println("WIFI_CONNECT_SUCCESS");
            }
        }
        else if (WIFI_IsConnectedFailed() || ((millis() - _ms) >= 60000))
        {
            eWifiState = WIFI_CONNECT;
            if (DEBUG_WIFI)
            {
                Serial.println("WIFI_CONNECT_FAILED : Retry");
            }
        }
        break;
    }
    case (WIFI_CONNECT_SUCCESS):
    {
        if (WIFI_IsDisconnected())
        {
            eWifiState = WIFI_CONNECT;
            if (DEBUG_WIFI)
            {
                Serial.println("WIFI_DISCONNECTED");
            }
        }
        break;
    }
    case (WIFI_WPS_START):
    {
        GPIO_BUILTIN_LED(LOW);
        WIFI_WPSProcess();
        eWifiState = WIFI_CONNECT;
        break;
    }
    }
}
