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

#include "keyboard.h"
#include "../relay/relay.h"

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
static bool _pushed = false;
static bool _longPush = false;
static unsigned long _ms = millis();
static bool _isBasic = false;
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
void KEYBOARD_TaskInit(void)
{
    _pushed = false;
    _longPush = false;
    _ms = millis();
}

void KEYBOARD_TaskRun(void)
{

    if ((GPIO_BUTTON_VAL() == true) || (GPIO_BUTTON_DUAL_VAL() == true))
    {
        _isBasic = (GPIO_BUTTON_VAL() == true);
        if (_pushed == false)
        {
            _ms = millis();
        }
        _pushed = true;
        if ((millis() - _ms) >= 3000)
        {
            _longPush = true;
        }
    }
    else
    {
        if (_pushed == true && (_longPush == false))
        {
            if (((millis() - _ms) >= 500) && (_isBasic == false))
            {
                RELAI_SetSate(RELAI_2, RELAI_GetState(RELAI_2) ^ 1);
            }
            else if ((millis() - _ms) >= 100)
            {
                RELAI_SetSate(RELAI_1, RELAI_GetState(RELAI_1) ^ 1);
            }
        }
        _pushed = false;
        _longPush = false;
    }
}

bool KEYBOARD_IsPushed(void)
{
    return _pushed;
}

bool KEYBOARD_IsLongPush(void)
{
    return _longPush;
}