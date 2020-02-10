//================================================================================================//
//                                                                                                //
// PROJET       : DBM620                                                                          //
// MODULE       : Board                                                                           //
// DESCRIPTION  :                                                                                 //
// CREATION     : 18/12/2017                                                                      //
// HISTORIQUE   :                                                                                 //
//                                                                                                //
//================================================================================================//

#ifndef _BOARD_
#define _BOARD_

//================================================================================================//
//                                        FICHIERS INCLUS                                         //
//================================================================================================//

#include <Arduino.h>

//================================================================================================//
//                                            DEFINES                                             //
//================================================================================================//

#define GPIO_PIN_BUILTIN_LED 13
#define GPIO_BUILTIN_LED_ON() digitalWrite(GPIO_PIN_BUILTIN_LED, LOW)
#define GPIO_BUILTIN_LED_OFF() digitalWrite(GPIO_PIN_BUILTIN_LED, HIGH)
#define GPIO_BUILTIN_LED(X) digitalWrite(GPIO_PIN_BUILTIN_LED, X)

#define GPIO_PIN_RELAI_1 12
#define GPIO_RELAI_1_ON() digitalWrite(GPIO_PIN_RELAI_1, LOW)
#define GPIO_RELAI_1_OFF() digitalWrite(GPIO_PIN_RELAI_1, HIGH)
#define GPIO_RELAI_1(X) digitalWrite(GPIO_PIN_RELAI_1, X)

#define GPIO_PIN_RELAI_2 5
#define GPIO_RELAI_2_ON() digitalWrite(GPIO_PIN_RELAI_2, LOW)
#define GPIO_RELAI_2_OFF() digitalWrite(GPIO_PIN_RELAI_2, HIGH)
#define GPIO_RELAI_2(X) digitalWrite(GPIO_PIN_RELAI_2, X)

#define GPIO_WRITE(X,Y) digitalWrite(X, Y)

#define GPIO_PIN_BUTTON 0
#define GPIO_BUTTON_VAL() !digitalRead(GPIO_PIN_BUTTON)

#define GPIO_PIN_BUTTON_DUAL 10
#define GPIO_BUTTON_DUAL_VAL() !digitalRead(GPIO_PIN_BUTTON_DUAL)

#define DEBUG_WIFI 1
#define DEBUG_MQTT 1

//================================================================================================//
//                                          ENUMERATIONS                                          //
//================================================================================================//

//================================================================================================//
//                                      STRUCTURES ET UNIONS                                      //
//================================================================================================//

//================================================================================================//
//                                VARIABLES ET FONCTION PARTAGEES                                 //
//================================================================================================//

//------------------------------------------------------------------------------------------------//
//---                                        Variables                                         ---//
//------------------------------------------------------------------------------------------------//

//------------------------------------------------------------------------------------------------//
//---                                        Fonctions                                         ---//
//------------------------------------------------------------------------------------------------//
void BOARD_Init(void);

#endif //--- _BOARD_
