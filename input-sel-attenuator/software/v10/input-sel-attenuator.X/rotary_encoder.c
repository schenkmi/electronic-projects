
/**
 * PIC16F18056 based input channel selection + attenuator
 *
 * Copyright (c) 2022-2025, Michael Schenk
 * All Rights Reserved
 *
 * Author: Michael Schenk
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * OEMs, ISVs, VARs and other distributors that combine and distribute
 * commercially licensed software with Michael Schenk software
 * and do not wish to distribute the source code for the commercially
 * licensed software under version 2, or (at your option) any later
 * version, of the GNU General Public License (the "GPL") must enter
 * into a commercial license agreement with Michael Schenk.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; see the file LICENSE.txt. If not, write to
 * the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 * http://www.gnu.org/licenses/gpl-2.0.html
 */

#include "mcc_generated_files/system/system.h"
#include "rotary_encoder.h"

/*
 * The below state table has, for each state (row), the new state
 * to set based on the next encoder output. From left to right in,
 * the table, the encoder outputs are 00, 01, 10, 11, and the value
 * in that position is the new state to set.
 */
#define R_START 0x0

#if 1 /* ENABLE_HALF_STEP */
/* Half-step state table. Emits a code at both 00 and 11, i.e. one event every
   2 edges, so 2 events per full quadrature cycle. The fitted
   PEC11R-4220F-S0012 is 12 PPR / 24 detents, so 48 edges and 24 detents per
   rev: 2 edges per detent, which makes this table emit exactly ONE EVENT PER
   DETENT. One event is one mechanical click, so ROTARY_MULTI_* in
   definitions.h count clicks as well as events. Both encoders share this
   table, so the flag also sets attenuator resolution. The full-step table
   below emits once per cycle and would therefore only step every 2nd detent,
   halving the resolution; it is not in use. */
#define R_CCW_BEGIN   0x1
#define R_CW_BEGIN    0x2
#define R_START_M     0x3
#define R_CW_BEGIN_M  0x4
#define R_CCW_BEGIN_M 0x5

const unsigned char ttable[][4] = {
  // 00                  01              10            11
  {R_START_M,           R_CW_BEGIN,     R_CCW_BEGIN,  R_START},           // R_START (00)
  {R_START_M | DIR_CCW, R_START,        R_CCW_BEGIN,  R_START},           // R_CCW_BEGIN
  {R_START_M | DIR_CW,  R_CW_BEGIN,     R_START,      R_START},           // R_CW_BEGIN
  {R_START_M,           R_CCW_BEGIN_M,  R_CW_BEGIN_M, R_START},           // R_START_M (11)
  {R_START_M,           R_START_M,      R_CW_BEGIN_M, R_START | DIR_CW},  // R_CW_BEGIN_M
  {R_START_M,           R_CCW_BEGIN_M,  R_START_M,    R_START | DIR_CCW}  // R_CCW_BEGIN_M
};
#else
/* Use the full-step state table (emits a code at 00 only) */
#define R_CW_FINAL   0x1
#define R_CW_BEGIN   0x2
#define R_CW_NEXT    0x3
#define R_CCW_BEGIN  0x4
#define R_CCW_FINAL  0x5
#define R_CCW_NEXT   0x6

const unsigned char ttable[][4] = {
  // 00         01           10           11
  {R_START,    R_CW_BEGIN,  R_CCW_BEGIN, R_START},           // R_START
  {R_CW_NEXT,  R_START,     R_CW_FINAL,  R_START | DIR_CW},  // R_CW_FINAL
  {R_CW_NEXT,  R_CW_BEGIN,  R_START,     R_START},           // R_CW_BEGIN
  {R_CW_NEXT,  R_CW_BEGIN,  R_CW_FINAL,  R_START},           // R_CW_NEXT
  {R_CCW_NEXT, R_START,     R_CCW_BEGIN, R_START},           // R_CCW_BEGIN
  {R_CCW_NEXT, R_CCW_FINAL, R_START,     R_START | DIR_CCW}, // R_CCW_FINAL
  {R_CCW_NEXT, R_CCW_FINAL, R_CCW_BEGIN, R_START}            // R_CCW_NEXT
};
#endif

/**
 * Grab state of input pins, determine new state from the pins
 * and state table, and return the emit bits (ie the generated event).
 * @param rotary_encoder_state
 * @return 
 */
uint8_t encoder1_read(volatile uint8_t* rotary_encoder_state) {
  /* read CHANA and CHANB, CW => up, CCW => down */
  uint8_t pinstate = (uint8_t)((ENC1CHANA_GetValue() << 1) | ENC1CHANB_GetValue());
  *rotary_encoder_state = ttable[*rotary_encoder_state & 0xf][pinstate];
  return (*rotary_encoder_state & 0x30);
}

/**
 * Grab state of input pins, determine new state from the pins
 * and state table, and return the emit bits (ie the generated event).
 * @param rotary_encoder_state
 * @return 
 */
uint8_t encoder2_read(volatile uint8_t* rotary_encoder_state) {
  /* read CHANA and CHANB, CW => up, CCW => down */
  uint8_t pinstate = (uint8_t)((ENC2CHANA_GetValue() << 1) | ENC2CHANB_GetValue());
  *rotary_encoder_state = ttable[*rotary_encoder_state & 0xf][pinstate];
  return (*rotary_encoder_state & 0x30);
}
