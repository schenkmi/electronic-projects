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
  * cd /work/electronic-projects/input-sel-attenuator/software/v6
  * cp ./input-sel-attenuator.X/dist/default/production/input-sel-attenuator.X.production.hex hex
  */

/**
 * History
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

volatile Instance_t instance = {
  .mode = Dual, .channel = -1, .last_channel = -1,
  .attenuation = -1, .last_attenuation = -1,
  .eeprom_save_status_counter = -1,
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
  
  irmp_init();
  irmp_set_callback_ptr(led_callback);
  
  while (1) {
      process_ir(&instance);
#if 0
    if (irmp_get_data(&instance.ir.data)) {
      /**
       * One For All
       * TV Hitachi 2676
       * irmp_data.protocol : 00007 (IRMP_RC5_PROTOCOL)
       * irmp_data.address  : 1 (0x0001)
       * irmp_data.command:
       * 1 => Key 1
       * 2 => Key 2
       * 3 => Kex 3
       * 4 => Key 4
       * 53 => Key OK
       * 32 => CH+
       * 33 => CH-
       * 16 => VOL+
       * 17 => VOL-
       * 13 => Mute
       */
      if (instance.ir.data.protocol == IRMP_NEC_PROTOCOL && instance.ir.data.address == IR_REMOTE_ADDRESS) {
          int channel = instance.channel;
          int attenuation = instance.attenuation;

          if (instance.ir.data.flags == 0x00) {
            switch (instance.ir.data.command) {
              case 0:
                channel++;
                break;
              case 1:
                channel--;
                break;
              case 2:
                attenuation--;
                break;
              case 3:
                attenuation++;
                break;
              case 14:
                instance.channel_attenuation[instance.channel].default_attenuation = instance.attenuation;
                instance.eeprom_save_status_counter = 1;
                break;
              case 17:
                channel = 0;
                break;
              case 18:
                channel = 1;
                break;
              case 19:
                channel = 2;
                break;
              case 20:
                channel = 3;
                break;
            }
        } else {
          switch (instance.ir.data.command) {
            case 2:
              attenuation--;
              break;
            case 3:
              attenuation++;
              break;
          }
        }

        /* channel is rotating */
        if (channel > ROTARY_MAX_CHANNEL) {
          instance.channel = 0;
        } else if (channel < ROTARY_MIN_CHANNEL) {
          instance.channel = ROTARY_MAX_CHANNEL;
        } else {
          instance.channel = channel;
        }

        /* for attenuation stop on max or min */
        if (attenuation > ROTARY_MAX_ATTENUATION) {
          instance.attenuation = ROTARY_MAX_ATTENUATION;
        } else if (attenuation < ROTARY_MIN_ATTENUATION) {
          instance.attenuation = 0;
        } else {
          instance.attenuation = attenuation;
        }
      }
    }
#endif
    process_channel(&instance);
    process_attenuation(&instance);
    process_encoder_button(&instance);
    eeprom_save_status(&instance);

    __delay_ms(MAIN_LOOP_WAIT);    
  }
}
