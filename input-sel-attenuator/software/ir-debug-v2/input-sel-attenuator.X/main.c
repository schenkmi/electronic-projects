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

 /**
  * Save hex
  * cd /work/electronic-projects/input-sel-attenuator/software/ir-debug-v1
  * cp ./input-sel-attenuator.X/dist/default/production/input-sel-attenuator.X.production.hex hex
  */

/**
 * History
 * V2.4     2025.03.30 Fix missing __EEPROM_DATA
 * V2.3     2025.03.29 Implement make before break algorithm to control the attenuator relay
 * V2.2     2025.03.26 Improve detection of attenuation inc/dec for relay control
 * V2.1     2025.03.22 Little bit of cleanup
 * V2.0     2025.02.15 Add support for IR control (IRMP)
 * V1.5     2024.06.01 Add delay between SYSTEM_Initialize and factory reset
 * V1.4     2024.05.26 New MCC, factory reset
 * V1.3     2023.12.16 Improve usability
 * V1.2     2023.12.13 Set attenuator to maximum in init()
 * V1.1     2022.10.30 Implement default attenuation which can be set by pressing
 *                     encoder button for > 3 seconds
 */

 /**
  * Next steps
  * Implement mute via RC
  * Implement acceleration for volume control
  */

/**
 * On start the default attenuation for each channel will be read and set.
 * If default attenuation was never set the maximum attenuation will be used.
 *
 * The default attenuation for the current channel can be set by pressing
 * attenuation for more than 3 seconds.
 *
 * On channel change the current attenuation of this channel will be set and
 * the channel will be stored as default channel.
 */

#include "definitions.h"
#include "irq_routines.h"
#include "control_routines.h"

/* eeprom initialize 0x00..0x07 */
__EEPROM_DATA(ROTARY_MAX_ATTENUATION /* channel 0 attenuation initial */,
              ROTARY_MAX_ATTENUATION /* channel 1 attenuation initial */,
              ROTARY_MAX_ATTENUATION /* channel 2 attenuation initial */,
              ROTARY_MAX_ATTENUATION /* channel 3 attenuation initial */,
              ROTARY_MIN_CHANNEL     /* channel selection initial     */,
              0xff, 0xff, 0xff);

volatile Instance_t instance = {
  .mode = Dual, .channel_save_mode = OnLongPress, .volume_save_mode = OnLongPress,
  .channel = -1, .last_channel = -1,
  .attenuation = -1, .last_attenuation = -1,
  .eeprom_save_status_counter = { -1, -1 },
  .channel_attenuation = {
    { .default_attenuation = ROTARY_MAX_ATTENUATION, .attenuation = -1 },
    { .default_attenuation = ROTARY_MAX_ATTENUATION, .attenuation = -1 },
    { .default_attenuation = ROTARY_MAX_ATTENUATION, .attenuation = -1 },
    { .default_attenuation = ROTARY_MAX_ATTENUATION, .attenuation = -1 },
  },
  .control =  Volume,
  .encoder = {
    { .direction = DIR_NONE,  .encoder_count = { 0, 0 },  .rotary_encoder_state = 0,
      .encoder_push_debounce_counter = 0, .encoder_push_counter = 0, .encoder_push_action = 0  },
    { .direction = DIR_NONE,  .encoder_count = { 0, 0 },  .rotary_encoder_state = 0,
      .encoder_push_debounce_counter = 0, .encoder_push_counter = 0, .encoder_push_action = 0  },
  },
  .ms_counter = 0,
  .button = { .button_pressed = 0, .waiting_for_double = 0, .click_count= 0, .press_time = 0, .release_time = 0 , .result = 0},
  
  
  
};

/**
 * Main application
 */
int main(void) {
  SYSTEM_Initialize();

   __delay_ms(STARTUP_WAIT);  
   
  /* weak pull-up so safe to call without connected rotary board */
  factory_reset();

  /* install irq handlers */
  Timer0_OverflowCallbackRegister(encoder_timer_callback);
  Timer2_OverflowCallbackRegister(ir_timer_callback);

  /* Enable the Global Interrupts */
  INTERRUPT_GlobalInterruptEnable();

  /* Enable the Peripheral Interrupts */
  INTERRUPT_PeripheralInterruptEnable();

  init(&instance);
  
   printf("\r\n");
  
  irmp_init();
  irmp_set_callback_ptr(led_callback);
  
    int last_channel = -1;
  int last_attenuation = -1;
            

  while (1) {
    process_ir(&instance);
    process_channel(&instance);
    process_attenuation(&instance);
    process_encoder_button(&instance);
    
    
    if (instance.button.result == 1) {
        printf("Long press\r\n");  
        instance.button.result = 0;
    }
    if (instance.button.result == 2) {
        printf("Single click\r\n");  
        instance.button.result = 0;
    }
    if (instance.button.result == 3) {
        printf("Double click\r\n");  
        instance.button.result = 0;
    }
    
    
    
    eeprom_save_status(&instance);

        if (instance.channel != last_channel) {
        last_channel = instance.channel;
        printf("Channel %u\r\n", instance.channel);
    }
    
    if (instance.attenuation != last_attenuation) {
        last_attenuation = instance.attenuation;
        printf("Attenuation %u\r\n", instance.attenuation);
    }

    
    
    __delay_ms(MAIN_LOOP_WAIT);    
  }
}
