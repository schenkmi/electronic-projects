/**
 * PIC16F18056 based async sample rate converter
 * for SRC4392
 *
 * Copyright (c) 2024-2025, Michael Schenk
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
 * V7.0     2025.05.04 Using PIC16F18056-I/SS MPLAB-X 6.25
 */

#include "mcc_generated_files/system/system.h"
#include "rotary_encoder.h"
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
#ifdef __USE_PCM1702__
    .output_word_length = OWL20Bit,
#else
    .output_word_length = OWL24Bit,
#endif
};

#ifdef __USE_PCM1792A__
PCM1792A_t pcm1792a = {
    .filter_rolloff = TI_Slow,
};
#endif


static void init(volatile Instance_t* instance)
{

    LED_RA5_SetHigh();
    LED_RA6_SetHigh();
    LED_RA7_SetHigh();

    

    
    __delay_ms(100);
    RESET_SetLow();
    __delay_ms(100);
    RESET_SetHigh();
    __delay_ms(10);

    src4392_init(&src4392);
    
#ifdef __USE_PCM1792A__
    pcm1792a_init(&pcm1792a);
#endif
    /* read last used channel, channels attenuation will be handler inside process_channel() */
    instance->channel = eeprom_read(EEPROM_ADDR_CHANNEL);

    /* read default attenuation for each channel and assign to channel attenuation */
    for (uint8_t cnt = 0; cnt <= ROTARY_MAX_CHANNEL; cnt++) {
        instance->channel_attenuation[cnt].attenuation = instance->channel_attenuation[cnt].default_attenuation = eeprom_read(cnt);
    }
}


/* Factory reset */
static void factory_reset() {
    if (ENC1_SWITCH_GetValue() == 0) {
        while(ENC1_SWITCH_GetValue() == 0) {
            __delay_ms(100);  
        }

        for (int cnt = 0; cnt < 10; cnt++) {
            /* LED on */
            LED_RA5_SetDigitalInput();
             __delay_ms(250);  
            /* LED off */
            LED_RA5_SetDigitalOutput();
            __delay_ms(250);  
        }

        eeprom_write(0x00, ROTARY_MIN_ATTENUATION);
        eeprom_write(0x01, ROTARY_MIN_ATTENUATION);
        eeprom_write(0x02, ROTARY_MIN_ATTENUATION);
        eeprom_write(0x03, ROTARY_MIN_ATTENUATION);
        eeprom_write(0x04, ROTARY_MIN_CHANNEL);
    }
}

void test_timer_callback(void) {   
    LED_RA5_Toggle();
}

static void process_channel(volatile Instance_t* instance)
{
  if (instance->channel != instance->last_channel)  {
    if (instance->last_channel != -1) {
      /* store current used attenuation on channel */
      instance->channel_attenuation[instance->last_channel].attenuation = instance->attenuation;
    }


    src4392_set_input( instance->channel);

    instance->last_channel = instance->channel;
    instance->eeprom_save_status_counter = EEPROM_SAVE_STATUS_VALUE;
  }
}


static void process_attenuation(volatile Instance_t* instance) {
  if (instance->attenuation != instance->last_attenuation) {
      instance->last_attenuation = instance->attenuation;
  }
}

/**
 * Main application
 */
int main(void)
{
    /* External Oscillator Selection bits: Oscillator not enabled otherwise RA5 is CLKIN */
    SYSTEM_Initialize();

    __delay_ms(STARTUP_WAIT);  
    
    /* if rotary enc board not connected, don't call this */
    factory_reset();

    /* install irq handlers */
    TMR0_OverflowCallbackRegister(rotary_encoder_timer_callback);
 
    /* Enable the Global Interrupts */
    INTERRUPT_GlobalInterruptEnable();

    /* Enable the Peripheral Interrupts */
    INTERRUPT_PeripheralInterruptEnable();

    TMR0_Start();
    
    /* IRQs need to be enabled for I2C */
    init(&instance);

    while (1) {
      process_channel(&instance);
      process_attenuation(&instance);
      process_encoder_button(&instance);
      eeprom_save_status(&instance);
      __delay_ms(MAIN_LOOP_WAIT);
    } 
}