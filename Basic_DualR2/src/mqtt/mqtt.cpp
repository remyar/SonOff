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

#include "./mqtt.h"
#include "../WiFi/wifi.h"
#include "../relay/relay.h"

//================================================================================================//
//                                            DEFINES                                             //
//================================================================================================//

//================================================================================================//
//                                          ENUMERATIONS                                          //
//================================================================================================//
typedef enum
{
    MQTT_IDLE = 0,
    MQTT_CONNECT,
    MQTT_CONNECT_IN_PROGRESS,
    MQTT_CONNECT_SUCCESS
} e_MQTT_STATE;

//================================================================================================//
//                                      STRUCTURES ET UNIONS                                      //
//================================================================================================//

////////////////////////////////////////////////////////////////////////////////////////////////////
//                                 VARIABLES PRIVEES ET PARTAGEES                                 //
////////////////////////////////////////////////////////////////////////////////////////////////////

//------------------------------------------------------------------------------------------------//
//---                                         Privees                                          ---//
//------------------------------------------------------------------------------------------------//
static e_MQTT_STATE eMqttState = MQTT_IDLE;
WiFiClient espClient;
PubSubClient client(espClient);
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
void _processMessage(char *topic, byte *payload, unsigned int length)
{
    //-- topic
    String receivedTopic = String(topic);
    String macAddr = WIFI_GetMacAddress();
    macAddr.replace(":", "");
    receivedTopic.replace((macAddr + "/Switch").c_str(), "");
    receivedTopic.replace("/", "");

    int relai = atoi(receivedTopic.c_str());
    relai = (relai > 0) ? relai - 1 : relai;
    //-- valeur
    char tab[32];
    memset(tab, 0, 32);
    for (unsigned int i = 0; i < length; i++)
    {
        tab[i] = (char)payload[i];
    }
    bool state = atoi(tab);

    if (DEBUG_MQTT)
    {
        Serial.println("MQTT_MESSAGE_RECEIVED");
        Serial.println(topic);
        Serial.println(relai);
        Serial.println(state);
    }

    RELAI_SetSate(relai, state);
}

//------------------------------------------------------------------------------------------------//
//---                                        Partagees                                         ---//
//------------------------------------------------------------------------------------------------//

//--------------------------------------------------------------------------------------------------
// FONCTION    : MQTT_TaskInit
//
// DESCRIPTION : Initialisation de la carte : GPIO, Clocks, Interruptions...
//--------------------------------------------------------------------------------------------------
void MQTT_TaskInit(void)
{
    _ms = millis();
}

//--------------------------------------------------------------------------------------------------
// FONCTION    : MQTT_TaskRun
//
// DESCRIPTION : Initialisation de la carte : GPIO, Clocks, Interruptions...
//--------------------------------------------------------------------------------------------------
void MQTT_TaskRun(void)
{
    switch (eMqttState)
    {
    case (MQTT_IDLE):
    {
        if (WIFI_IsConnected())
        {
            client.setServer(WIFI_GetServerIp(), 1883); //Configuration de la connexion au serveur MQTT
            client.setCallback(_processMessage);
            eMqttState = MQTT_CONNECT;
            if (DEBUG_MQTT)
            {
                Serial.println("MQTT_CONNECT");
            }
        }
        break;
    }
    case (MQTT_CONNECT):
    {
        if (client.connected() == false)
        {
            client.connect(WIFI_GetMacAddress().c_str());
            eMqttState = MQTT_CONNECT_IN_PROGRESS;
            _ms = millis();
            if (DEBUG_MQTT)
            {
                Serial.println("MQTT_CONNECT_IN_PROGRESS");
            }
        }
        break;
    }
    case (MQTT_CONNECT_IN_PROGRESS):
    {
        if (client.connected() == true)
        {
            // subscribe to all topics
            String str = WIFI_GetMacAddress();
            str.replace(":", "");
            client.subscribe((str + "/Switch/#").c_str());
            client.subscribe((str + "/Switch").c_str());
            eMqttState = MQTT_CONNECT_SUCCESS;
            if (DEBUG_MQTT)
            {
                Serial.println("MQTT_CONNECT_SUCCESS");
                Serial.println((str + "/Switch").c_str());
            }
        }
        else if ((millis() - _ms) >= 60000)
        {
            if (DEBUG_MQTT)
            {
                Serial.println("MQTT_CONNECTING_TIMEOUT");
            }
            eMqttState = MQTT_IDLE;
        }
        break;
    }
    case (MQTT_CONNECT_SUCCESS):
    {
        if (client.connected() == false)
        {
            if (DEBUG_MQTT)
            {
                Serial.println("MQTT_DISCONNECTED");
            }

            eMqttState = MQTT_IDLE;
        }
        break;
    }
    }

    client.loop();
}

bool MQTT_IsConnected(void)
{
    return client.connected();
}

void MQTT_Publish(String topic, String value)
{
    client.publish(topic.c_str(), value.c_str());
}

void MQTT_SendRelaiState(bool value)
{

    String str = WIFI_GetMacAddress();
    str.replace(":", "");

    MQTT_Publish((str + "/set/Switch").c_str() ,value ? "1" : "0" );
}