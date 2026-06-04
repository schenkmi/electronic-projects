/**
 * PIC16F18056 based async sample rate converter
 * for AK4118 / AK4137
 *
 * Copyright (c) 2025-2026, Michael Schenk
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

#include "project_configuration.h"
#include "definitions.h"

#include "src4392.h"
#include "ak4118.h"
#include "cs8416.h"
#include "ak4137.h"
#include "pcm1792a.h"

#ifdef __USE_AK4118__
extern AK4118_t ak4118;
#endif
#ifdef __USE_CS8416__
extern CS8416_t cs8416;
#endif
#ifdef __USE_AK4137__
extern AK4137_t ak4137;
#endif
#ifdef __USE_SRC4392__
extern SRC4392_t src4392;
#endif
#ifdef __USE_PCM1792A__
extern PCM1792A_t pcm1792a;
#endif


void led_toggel(void) {
//  LED_Toggle();
}

void led_callback(uint_fast8_t on) {
  /* inverse, default is LED on */
 // if (on) {
 //   LED_SetLow();
 // } else {
 //   LED_SetHigh();
 // }
}

void init(volatile Instance_t* instance) {
    LED_D3_SetHigh();
    __delay_ms(500);
    LED_D3_SetLow();
    LED_D4_SetHigh();
    __delay_ms(500);
    LED_D4_SetLow();
    /* External Oscillator Selection bits: Oscillator not enabled otherwise RA7 is CLKIN and LED D5 is not working*/
    LED_D5_SetHigh();
    __delay_ms(500);
    LED_D5_SetLow();

#ifdef __USE_AK4137__
    /* configure AK4137 pins which are read during reset of AK4137 */
    ak4137_preinit(&ak4137);
#endif

    __delay_ms(100);
    RESET_SetLow();
    __delay_ms(100);
    RESET_SetHigh();
    __delay_ms(10);

#ifdef __USE_AK4118__
    ak4118_init(&ak4118);
#endif
    
#ifdef __USE_CS8416__
    cs8416_init(&cs8416);
#endif
    
#ifdef __USE_AK4137__
    ak4137_init(&ak4137);
#endif
#ifdef __USE_SRC4392__
    src4392_init(&src4392);
#endif
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

void factory_reset() {
    if (ENC1SWITCH_GetValue() == 0) {
        while(ENC1SWITCH_GetValue() == 0) {
            __delay_ms(100);  
        }

        for (int cnt = 0; cnt < 10; cnt++) {
            /* LED on */
            LED_D3_SetHigh();
             __delay_ms(250);  
            /* LED off */
            LED_D3_SetLow();
            __delay_ms(250);  
        }

        eeprom_write(0x00, ROTARY_MIN_ATTENUATION);
        eeprom_write(0x01, ROTARY_MIN_ATTENUATION);
        eeprom_write(0x02, ROTARY_MIN_ATTENUATION);
        eeprom_write(0x03, ROTARY_MIN_ATTENUATION);
        eeprom_write(0x04, ROTARY_MIN_CHANNEL);
    }
}


/* attenuator relay are on RA0...RA5 */
void process_attenuation(volatile Instance_t* instance) {
  if (instance->attenuation != instance->last_attenuation) {
    uint8_t attenuation = ((uint8_t)instance->attenuation & ROTARY_MAX_ATTENUATION);

    //configure_attenuation(attenuation);
    
    if (instance->attenuation_callback) {
       instance->attenuation_callback(attenuation); 
    }
    
    instance->last_attenuation = instance->attenuation;
    
     //printf("attenuation %u\r\n", attenuation);
  }
}

/* channel selection relay are on RB0...RB3 */
void process_channel(volatile Instance_t* instance) {
  if (instance->channel != instance->last_channel)  {
    if (instance->last_channel != -1) {
      /* store current used attenuation on channel */
      instance->channel_attenuation[instance->last_channel].attenuation = instance->attenuation;
    }

    // printf("channel %u\r\n", instance->channel);
    
    if (instance->channel_callback) {
       instance->channel_callback(instance->channel); 
    }

        /* no save on first start (e.g last_channel == -1) */
    if (instance->last_channel != -1) {
      if (instance->save_mode[Volume] == SaveOnChange) {    
        instance->save_action |= SaveChannel;
        instance->save_countdown_counter = DEFAULT_SAVE_COUNTDOWN;
      }
    }
    
    instance->last_channel = instance->channel;
    
  }

}

void eeprom_save_status(volatile Instance_t* instance) {
  /* delayed save to prevent unneeded writes to the eeprom */
  if (instance->save_countdown_counter > 0) {
    instance->save_countdown_counter--;
    return;
  }
    
  if (instance->mode == Dual) { /* both encoders are used encoder1 for attenuation, encoder2 for channel */
    if (instance->save_action & SaveVolume) {
      instance->save_action &= ~SaveVolume;
      
      /* store current attenuation as default value */
      instance->channel_attenuation[instance->channel].default_attenuation = instance->attenuation;
  
      /* if default value for channel changed, store it */
      if (eeprom_read((unsigned char) instance->channel) != (unsigned char) instance->channel_attenuation[instance->channel].default_attenuation) {
        /* store current default attenuation which is applied after a channel switch */
        eeprom_write((unsigned char) instance->channel, (unsigned char) instance->channel_attenuation[instance->channel].default_attenuation);
      }
    }
      
    if (instance->save_action & SaveChannel) {
      instance->save_action &= ~SaveChannel;
     
      /* if stored default channel not equal current one, update default channel */
      if (eeprom_read(EEPROM_ADDR_CHANNEL) != (unsigned char) instance->channel) {
        eeprom_write(EEPROM_ADDR_CHANNEL, (unsigned char) instance->channel);
      }
    }
  } else {
      
  }
}

void process_encoder_button(volatile Instance_t* instance) {
  if (instance->mode == Dual) { /* both encoders are used encoder1 for attenuation, encoder2 for channel */
    if (instance->encoder[Volume].button.press != NoPress) {
      switch (instance->encoder[Volume].button.press) {
        case SinglePress: 
          break;
        case DoublePress: 
          break;
        case LongPress:
          if (instance->save_mode[Volume] == SaveOnLongPress) {
            instance->save_countdown_counter = DEFAULT_SAVE_COUNTDOWN;
            instance->save_action |= SaveVolume;
          }   
          break;
        default:
          break;
      }
        
      instance->encoder[Volume].button.press = NoPress;
    }

    if (instance->encoder[Channel].button.press != NoPress) {
      switch (instance->encoder[Channel].button.press) {
        case SinglePress:  
          break;
        case DoublePress:
          break;
        case LongPress:
          if (instance->save_mode[Channel] == SaveOnLongPress) {
            instance->save_countdown_counter = DEFAULT_SAVE_COUNTDOWN;
            instance->save_action |= SaveChannel;
          }   
          break;
        default:
          break;
      }
        
      instance->encoder[Channel].button.press = NoPress;
    }
  } else {
    if (instance->encoder[Combined].button.press != NoPress) {
      switch (instance->encoder[Combined].button.press) {
        case SinglePress:
            
            if (instance->control == Volume) {
                 instance->control = Channel;
            } else if (instance->control == Channel) {
                instance->control = Volume;
            }
            
          break;
        case DoublePress:
          break;
        case LongPress:
          break;
        default:
          break;
      }
        
      instance->encoder[Combined].button.press = NoPress;
    }
  }
}

void process_ir(Instance_t* instance) {
  if (irmp_get_data(&instance->ir.data)) {
    if (instance->ir.data.protocol == IR_PROTOCOL && instance->ir.data.address == IR_REMOTE_ADDRESS) {
      int channel = instance->channel;
      int attenuation = instance->attenuation;

      if (instance->ir.data.flags == 0x00) {
        switch (instance->ir.data.command) {
          case IR_KEY_CH_UP:
            channel++;
            break;
          case IR_KEY_CH_DOWN:
            channel--;
            break;
          case IR_KEY_VOL_UP:
            attenuation--;
            break;
          case IR_KEY_VOL_DOWN:
            attenuation++;
            break;
          case IR_KEY_OK:
            /* possible location to store current volume */
            break;
          case IR_KEY_1:
            channel = 0;
            break;
          case IR_KEY_2:
            channel = 1;
            break;
          case IR_KEY_3:
            channel = 2;
            break;
          case IR_KEY_4:
            channel = 3;
            break;
        }
      } else {
        switch (instance->ir.data.command) {
          case IR_KEY_VOL_UP:
            attenuation--;
            break;
          case IR_KEY_VOL_DOWN:
            attenuation++;
            break;
        }
      }

      /* channel is rotating */
      if (channel > ROTARY_MAX_CHANNEL) {
        instance->channel = 0;
      } else if (channel < ROTARY_MIN_CHANNEL) {
        instance->channel = ROTARY_MAX_CHANNEL;
      } else {
        instance->channel = channel;
      }

      /* for attenuation stop on max or min */
      if (attenuation > ROTARY_MAX_ATTENUATION) {
        instance->attenuation = ROTARY_MAX_ATTENUATION;
      } else if (attenuation < ROTARY_MIN_ATTENUATION) {
        instance->attenuation = 0;
      } else {
        instance->attenuation = attenuation;
      }
    }
  }
}
