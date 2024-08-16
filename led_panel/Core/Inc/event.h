/*
 * event.h
 *
 *  Created on: Aug 16, 2024
 *      Author: han
 */

#ifndef INC_EVENT_H_
#define INC_EVENT_H_

#include "stm32f1xx_hal.h"


extern void on_button_pressed();
extern void on_button_held();
extern void on_button_released();

void on_event();



#endif /* INC_EVENT_H_ */
