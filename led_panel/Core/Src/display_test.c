/*
 * display_test.c
 *
 *  Created on: Aug 21, 2024
 *      Author: han
 */

#include "base.h"
#include "main.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

#if display_test



void on_ready() {
}
void on_update() {
	for (int r = 0; r < 1; ++r) {
		R1(0);
		G1(0);
		B1(0);
		R2(0);
		G2(0);
		B2(0);

		for (int i = 0; i < 128; ++i) {
			for (int var = 0; var < 2; ++var) {

			for (int gs = 0; gs < 16; ++gs) {
				R1(0);
				G1(0);
				B1(1);

				CLK_L;
				CLK_H;

				if (gs == 15) {
				}
			}
					LAT_H;
			LAT_L;

			for (int gsclk = 0; gsclk < 1/*65536*/; ++gsclk) {
				CLK_L;
				CLK_H;
				LAT_H;
				LAT_L;
				OE_H;
				OE_L;
			}


			HAL_Delay(1);
			}
		}

		ROW(r);
	}
}


#endif
