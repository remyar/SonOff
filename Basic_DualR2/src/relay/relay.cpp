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

#include "relay.h"

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
static s_RELAIS sRelais[MAX_RELAIS] = {
    { pin : GPIO_PIN_RELAI_1 , state : LOW},
    { pin : GPIO_PIN_RELAI_2 , state : LOW},
};

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
void RELAI_TaskInit(void)
{
    for ( int i = 0 ; i < MAX_RELAIS ; i++ ){
        sRelais[i].state = LOW;
    }
}

void RELAI_TaskRun(void)
{
    for ( int i = 0 ; i < MAX_RELAIS ; i++ ){
        GPIO_WRITE(sRelais[i].pin , sRelais[i].state);
    }
}

void RELAI_SetSate(byte relai , bool state)
{
    sRelais[relai].state = state;
}

bool RELAI_GetState(byte relai){
    return sRelais[relai].state;
}