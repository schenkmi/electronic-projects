/**
 * PIC16F18446 based async sample rate converter
 * for TI/BB SRC4392/SRC4382
 * PCM1792A
 *
 * Copyright (c) 2021-2024, Michael Schenk
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
  * cd /work/electronic-projects/dac-pcm1792a/software/asrc-pcm1792a-v2.X
  * cp ./dist/default/production/asrc-pcm1792a-v2.X.production.hex hex/
  */

/**
 * History
 * V1.0     2024.04.01 First testable version
 */


#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"
#include "rotary_encoder.h"
#include "src4392.h"
#include "pcm1792a.h"

/* eeprom initialize 0x00..0x07 */
__EEPROM_DATA(ROTARY_MIN_ATTENUATION /* channel 0 attenuation initial */,
              ROTARY_MIN_ATTENUATION /* channel 1 attenuation initial */,
              ROTARY_MIN_ATTENUATION /* channel 2 attenuation initial */,
              ROTARY_MIN_ATTENUATION /* channel 3 attenuation initial */,
              ROTARY_MIN_CHANNEL     /* channel selection initial     */,
              0xff, 0xff, 0xff);

volatile Instance_t instance = {
  .mode = Single, .channel = -1, .last_channel = -1,
  .attenuation = -1, .last_attenuation = -1,
  .eeprom_save_status_counter = -1,
  .channel_attenuation = {
    { .default_attenuation = ROTARY_MIN_ATTENUATION, .attenuation = -1 },
    { .default_attenuation = ROTARY_MIN_ATTENUATION, .attenuation = -1 },
    { .default_attenuation = ROTARY_MIN_ATTENUATION, .attenuation = -1 },
    { .default_attenuation = ROTARY_MIN_ATTENUATION, .attenuation = -1 },
  },
  .control =  Channel,
  .encoder = {
    { .direction = DIR_NONE,  .encoder_count = { 0, 0 },  .rotary_encoder_state = 0,
      .encoder_push_debounce_counter = 0, .encoder_push_counter = 0, .encoder_push_action = 0  },
    { .direction = DIR_NONE,  .encoder_count = { 0, 0 },  .rotary_encoder_state = 0,
      .encoder_push_debounce_counter = 0, .encoder_push_counter = 0, .encoder_push_action = 0  },
  },
};

SRC4392_t src4392 = {
    .deemphases = DeEmphasisAuto,
    .digital_audio_interface_transmitter = DITUpsample,
    .upsample_rate = UpsamplingTo192kHz,
    .output_word_length = OWL24Bit,
};

PCM1792A_t pcm1792a = {
    .filter_rolloff = Slow,
};

static void init(volatile Instance_t* instance)
{
    
    LED_D4_SetDigitalInput();
    LED_D5_SetDigitalInput();
    LED_D4_SetLow();
    LED_D4_SetLow();

    __delay_ms(100);
    RESET_SetLow();
    __delay_ms(100);
    RESET_SetHigh();
    __delay_ms(10);
	
    
    
    
    
    
//      __delay_ms(500 /*MAIN_LOOP_WAIT*/);
//  for (int cnt = 0; cnt < 100; cnt++) {
//      src4392_test();
//      __delay_ms(100 /*MAIN_LOOP_WAIT*/);
//  }
  
    
    
//     __delay_ms(500 /*MAIN_LOOP_WAIT*/);
//     for (int cnt = 0; cnt < 10; cnt++) {
//    src4392_mute(true);
//     __delay_ms(100 /*MAIN_LOOP_WAIT*/);
//    src4392_mute(false);
//      __delay_ms(100 /*MAIN_LOOP_WAIT*/);
//     }
//    
//      __delay_ms(500 /*MAIN_LOOP_WAIT*/);
//    
    
    
src4392_init(&src4392);
    
pcm1792a_init(&pcm1792a);
    
  
 __delay_ms(1000 /*MAIN_LOOP_WAIT*/);


  /* read last used channel, channels attenuation will be handler inside process_channel() */
  instance->channel = eeprom_read(EEPROM_ADDR_CHANNEL);

  /* read default attenuation for each channel and assign to channel attenuation */
  for (uint8_t cnt = 0; cnt <= ROTARY_MAX_CHANNEL; cnt++) {
    instance->channel_attenuation[cnt].attenuation = instance->channel_attenuation[cnt].default_attenuation = eeprom_read(cnt);
  }
}

static void process_channel(volatile Instance_t* instance)
{
  if (instance->channel != instance->last_channel)  {
    if (instance->last_channel != -1) {
      /* store current used attenuation on channel */
      instance->channel_attenuation[instance->last_channel].attenuation = instance->attenuation;
    }

    src4392_mute(true);
    
    /* always start with last attenuation used for this channel */
    instance->last_attenuation = instance->attenuation = instance->channel_attenuation[instance->channel].attenuation;

    src4392_set_attenuation(instance->attenuation, instance->attenuation);
    src4392_set_input(instance->channel);
    
    src4392_mute(false);

    instance->last_channel = instance->channel;
    instance->eeprom_save_status_counter = EEPROM_SAVE_STATUS_VALUE;
  }
}


static void process_attenuation(volatile Instance_t* instance) {
  if (instance->attenuation != instance->last_attenuation) {
    unsigned char attenuation = ((unsigned char) instance->attenuation & ROTARY_MAX_ATTENUATION);

    src4392_set_attenuation(attenuation, attenuation);

    instance->last_attenuation = instance->attenuation;
  }
}

/**
 * Main application
 */
int main(void)
{
  SYSTEM_Initialize();
  
  
  /* TODO: Query rotary switch press and to a factory reset if so */





  init(&instance);

  /* install irq handlers */
  TMR0_SetInterruptHandler(rotary_encoder_timer_callback);
  

  /* Enable the Global Interrupts */
  INTERRUPT_GlobalInterruptEnable();

  /* Enable the Peripheral Interrupts */
  INTERRUPT_PeripheralInterruptEnable();

  
    LED_D5_SetDigitalOutput();
    LED_D4_SetDigitalOutput();
                    
  
  /* DAC */
  //set_upsample(src4392.upsample_rate);
  //set_dit_mode(&src4392, instance.channel, DITUpsample);
  //set_deemphasis(DeEmphasisAuto); 
  //set_input(instance.channel, DITUpsample);
  
  
  //int on = 1;
  
  //__delay_ms(500 /*MAIN_LOOP_WAIT*/);
  

  while (1) {
    process_channel(&instance);
    process_attenuation(&instance);
    process_encoder_button(&instance);
    eeprom_save_status(&instance);
//    __delay_ms(500 /*MAIN_LOOP_WAIT*/);
//    if (on) {
//            LED_D4_SetDigitalInput();
//    LED_D5_SetDigitalInput();
//    on = 0;
//    } else {
//            LED_D5_SetDigitalOutput();
//    LED_D4_SetDigitalOutput();
//    on = 1;
//    }
  }
}
