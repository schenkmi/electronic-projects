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
 * V1.0     2024.04.21 Start develop
 */


#include "mcc_generated_files/system/system.h"


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
    .filter_rolloff = TI_Slow,
};

/* External Oscillator Selection bits: Oscillator not enabled otherwise RA5 is CLKIN */
 

static void init(volatile Instance_t* instance)
{

    LED_D5_SetHigh();
    LED_D4_SetHigh();
    LED_D8_SetHigh();

    

    
    __delay_ms(100);
    RESET_SetLow();
    __delay_ms(100);
    RESET_SetHigh();
    __delay_ms(10);
    
#if 0
    if (IO_RA2_GetValue()) {
        src4392.output_word_length = OWL24Bit;
    } else {
        src4392.output_word_length = OWL20Bit;
    }
#endif

    src4392_init(&src4392);
    pcm1792a_init(&pcm1792a);

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
            LED_D4_SetDigitalInput();
             __delay_ms(250);  
            /* LED off */
            LED_D4_SetDigitalOutput();
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
    LED_D5_Toggle();
}


/**
 * Main application
 */
int main(void)
{
    SYSTEM_Initialize();

    /* weak pull-up so safe to call without connected rotary board */
    factory_reset();



    /* install irq handlers */
    TMR0_OverflowCallbackRegister(rotary_encoder_timer_callback);
    //TMR0_OverflowCallbackRegister(test_timer_callback);

            
    /* Enable the Global Interrupts */
    INTERRUPT_GlobalInterruptEnable();

    /* Enable the Peripheral Interrupts */
    INTERRUPT_PeripheralInterruptEnable();

    TMR0_Start();
    
    /* IRQs need to be enabled for I2C */
    init(&instance);
    
    
    //pcm1792a_set_attenuation(0xff, 0xff);
    
    while(1) {
        __delay_ms(500);  
    }    
}
