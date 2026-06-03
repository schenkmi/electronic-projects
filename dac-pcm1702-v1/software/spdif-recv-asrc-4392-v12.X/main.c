/**
 * PIC16F18056 based async sample rate converter
 * for AK4118 / AK4137
 *
 * Copyright (c) 2024-2026, Michael Schenk
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
 * commercially licensed software with Michael Schenks software
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


 /**
  * Save hex
  * cd /work/electronic-projects/spdif-recv-cs8416-ak4137/software
  * cp spdif-recv-cs8416-ak4137-v2.X/dist/default/production/spdif-recv-cs8416-ak4137-v2.X.production.hex hex/
  */

/**
 * History
 * V12.0    2026.05.18 Improved with IR
 * V7.0     2025.05.04 Using PIC16F18056-I/SS MPLAB-X 6.25
 */

#include "project_configuration.h"

#include "definitions.h"
#include "irq_routines.h"
#include "control_routines.h"
#include "cs8416.h"
#include "ak4118.h"
#include "ak4137.h"
#include "src4392.h"
#include "pcm1792a.h"


//#define __USE_PCM1792A__
//#define __USE_PCM1702__
#define __USE_PCM1704__

#define STARTUP_WAIT                    250 /* wait 250ms after SYSTEM_Initialize */

/* eeprom initialize 0x00..0x07 */
__EEPROM_DATA(ROTARY_MIN_ATTENUATION /* channel 0 attenuation initial */,
              ROTARY_MIN_ATTENUATION /* channel 1 attenuation initial */,
              ROTARY_MIN_ATTENUATION /* channel 2 attenuation initial */,
              ROTARY_MIN_ATTENUATION /* channel 3 attenuation initial */,
              ROTARY_MIN_CHANNEL     /* channel selection initial     */,
              0xff, 0xff, 0xff);


volatile Instance_t instance = {
  .mode = Single,
  .save_mode = { SaveOnLongPress /* Volume */ , SaveOnLongPress /* Channel */ },
  .save_action = NoSaveAction,
  .save_countdown_counter = -1,
  .channel = -1, .last_channel = -1,
  .attenuation = -1, .last_attenuation = -1,
  .channel_attenuation = {
    { .default_attenuation = ROTARY_MAX_ATTENUATION, .attenuation = -1 },
    { .default_attenuation = ROTARY_MAX_ATTENUATION, .attenuation = -1 },
    { .default_attenuation = ROTARY_MAX_ATTENUATION, .attenuation = -1 },
    { .default_attenuation = ROTARY_MAX_ATTENUATION, .attenuation = -1 },
  },
  .control =  Volume,
  .ms_counter = 0,
  .encoder = {
    { .direction = DIR_NONE,  .encoder_count = { 0, 0 },  .rotary_encoder_state = 0, 
      .button = {
        .button_pressed = 0, .waiting_for_double = 0, .click_count= 0, .press_time = 0, .release_time = 0, .press = NoPress, 
       }, 
    },
    { .direction = DIR_NONE,  .encoder_count = { 0, 0 },  .rotary_encoder_state = 0, 
      .button = {
        .button_pressed = 0, .waiting_for_double = 0, .click_count= 0, .press_time = 0, .release_time = 0, .press = NoPress, 
       }, 
    },
  },
};

#ifdef __USE_SRC4392__
SRC4392_t src4392 = {
    .deemphases = DeEmphasisAuto,
    .digital_audio_interface_transmitter = DITUpsample,
    .upsample_rate = UpsamplingTo192kHz,
#ifdef __USE_PCM1702__
    .output_word_length = OWL20Bit,
#else
    .output_word_length = OWL24Bit,
#endif
};
#endif

#ifdef __USE_CS8416__
CS8416_t cs8416 = {
    .output_format = CS_I2S,
    .output_word_length = CS_OWL24Bit,
};
#endif

#ifdef __USE_AK4118__
AK4118_t ak4118 = {
    .data_format = AK4118_24Bit_Right,
    .previous = { .input = 0xff, .sampling_rate = 0xff, .status_register = 0xff },
};
#endif

#ifdef __USE_AK4137__
AK4137_t ak4137 = {
    .input_format = AK_LSB24Bit,
    .digital_filter = AK_ShortDelaySharpRollOff,
    .output_format = AK_I2S,
    .output_sampling_frequency = AK_FS384kHz, 
#ifdef __USE_PCM1702__
    .output_word_length = AK_OWL20Bit, 
#else
    .output_word_length = AK_OWL24Bit,
#endif
};

#endif

#ifdef __USE_PCM1792A__
PCM1792A_t pcm1792a = {
    .filter_rolloff = TI_Slow,
};
#endif





/* channel selection relay are on RB0...RB3 */


/* attenuator relay are on RA0...RA5 */

/**
 * Main application
 */
int main(void)
{
    SYSTEM_Initialize();

    __delay_ms(STARTUP_WAIT);  
    
  /* weak pull-up so safe to call without connected rotary board */
  factory_reset();

    /* install irq handlers */
    TMR0_PeriodMatchCallbackRegister(encoder_timer_callback);
 #if __USE_IR__
    TMR2_PeriodMatchCallbackRegister(ir_timer_callback);
#endif
  /* Enable the Global Interrupts */
  INTERRUPT_GlobalInterruptEnable();

  /* Enable the Peripheral Interrupts */
  INTERRUPT_PeripheralInterruptEnable();


    
    /* IRQs need to be enabled for I2C */
    init(&instance);
    
#if __USE_IR__
      irmp_init();
    irmp_set_callback_ptr(led_callback);
#endif
  
    printf("Hello\r\n");

    
    while (1) {

#if __USE_IR__
      process_ir(&instance);
#endif
    process_channel(&instance);
    process_attenuation(&instance);
    process_encoder_button(&instance);
    eeprom_save_status(&instance);
      
      
#if 1
      __delay_ms(MAIN_LOOP_WAIT);
#else
      __delay_ms(1000);
      ak4118_print_input();
      ak4118_print_samplerate();
      ak4118_print_spdif_status();
#endif
    } 
}