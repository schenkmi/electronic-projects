/**
 * PIC16F18056 based input channel selection + attenuator
 *
 * Copyright (c) 2025-2025, Michael Schenk
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

#include "definitions.h"

void led_toggel(void) {
  LED_Toggle();
}

void led_callback(uint_fast8_t on) {
  /* inverse, default is LED on */
  if (on) {
    LED_SetLow();
  } else {
    LED_SetHigh();
  }
}

void init(volatile Instance_t* instance) {
  /* Set LED on */
  LED_SetHigh();

  /* mute output */
  PORTB &= ~CHAN_SEL_MASK;
  __delay_ms(RELAIS_MAX_SETUP_TIME);

  /* max possible attenuation on attenuation */
  PORTA = ((PORTA & ~ROTARY_MAX_ATTENUATION) | ROTARY_MAX_ATTENUATION);

  /* one channel after the others */
  for (int cnt = 0; cnt <= ROTARY_MAX_CHANNEL; cnt++) {
    uint8_t in = ((1 << cnt) & 0xff);
    PORTB |= in;
    __delay_ms(500);
    PORTB &= ~in;
  }

  /* read last used channel, channels attenuation will be handler inside process_channel() */
  instance->channel = eeprom_read(EEPROM_ADDR_CHANNEL);

  /* read default attenuation for each channel and assign to channel attenuation */
  for (uint8_t cnt = 0; cnt <= ROTARY_MAX_CHANNEL; cnt++) {
    instance->channel_attenuation[cnt].attenuation = instance->channel_attenuation[cnt].default_attenuation = eeprom_read(cnt);
  }
}

void factory_reset() {
  if (ENC2SWITCH_GetValue() == 0) {
    while(ENC2SWITCH_GetValue() == 0) {
      __delay_ms(100);
    }

    for (int cnt = 0; cnt < 10; cnt++) {
      /* LED on */
      LED_Toggle();
      __delay_ms(500);
    }

    eeprom_write(0x00, ROTARY_MAX_ATTENUATION);
    eeprom_write(0x01, ROTARY_MAX_ATTENUATION);
    eeprom_write(0x02, ROTARY_MAX_ATTENUATION);
    eeprom_write(0x03, ROTARY_MAX_ATTENUATION);
    eeprom_write(0x04, ROTARY_MIN_CHANNEL);
  }
}

/* channel selection relay are on RB0...RB3 */
void process_channel(volatile Instance_t* instance) {
  if (instance->channel != instance->last_channel)  {
    if (instance->last_channel != -1) {
      /* store current used attenuation on channel */
      instance->channel_attenuation[instance->last_channel].attenuation = instance->attenuation;
    }

    /* mute output */
     PORTB &= ~CHAN_SEL_MASK;
    __delay_ms(RELAIS_MAX_SETUP_TIME);

    /* always start with last attenuation used for this channel */
    instance->last_attenuation = instance->attenuation = instance->channel_attenuation[instance->channel].attenuation;
    PORTA = ((PORTA & ~ROTARY_MAX_ATTENUATION) | ((unsigned char)instance->attenuation & ROTARY_MAX_ATTENUATION));

    /* clear and set new channel */
    PORTB = ((PORTB & ~CHAN_SEL_MASK) | ((1 << instance->channel) & CHAN_SEL_MASK));
    __delay_ms(RELAIS_MAX_SETUP_TIME);
    
    /* no save on first start (e.g last_channel == -1) */
    if (instance->last_channel != -1) {
     //  instance->eeprom_save_status_counter = EEPROM_SAVE_STATUS_VALUE; 
       
      if (instance->channel_save_mode == OnChange) {
          
        printf("process_channel instance->channel_save_mode == OnChange \r\n");  
        instance->eeprom_save_status_counter[(instance->mode == Dual) ? Channel : Combined] = EEPROM_SAVE_STATUS_VALUE;
      }
               
               
       
    }
    

    instance->last_channel = instance->channel;
    
  }
}

/* attenuator relay are on RA0...RA5 */
void process_attenuation(volatile Instance_t* instance) {
  if (instance->attenuation != instance->last_attenuation) {
    uint8_t attenuation = ((uint8_t)instance->attenuation & ROTARY_MAX_ATTENUATION);

    if ((PORTA & ROTARY_MAX_ATTENUATION) != attenuation) {
      /* something needs to be changed */
#if ATT_CTRL == ATT_CTRL_DIRECTION
       if (instance->attenuation < instance->last_attenuation) {
        /**
         * quieter -> louder (decrease of attenuation)
         * Set LSB to MSB relay to avoid peak level 000000
         * 48dB -> 46.5dB / 100000 -> 011111
         */
        for (int cnt = 0; cnt < ROTARY_ATTENUATION_BITS; cnt++) {
          uint8_t bit = ((1 << cnt) & 0xff);

          if ((PORTA & bit) != (attenuation & bit)) {
            /* port bit needs to be changed */
            if (attenuation & bit) {
              PORTA |= bit;
            } else {
              PORTA &= ~bit;
            }
            /* changed relay, wait a bit */
            __delay_ms(RELAIS_MAX_SETUP_TIME);
          }
        }
      } else {
        /**
         * louder -> quieter (increase of attenuation)
         * Set MSB to LSB relay to avoid peak level 000000
         * 48dB -> 46.5dB / 100000 -> 011111
         * 46.5dB -> 48dB / 011111 -> 100000
         */
        for (int cnt = (ROTARY_ATTENUATION_BITS - 1); cnt >= 0; cnt--) {
          uint8_t bit = ((1 << cnt) & 0xff);

          if ((PORTA & bit) != (attenuation & bit)) {
            /* port bit needs to be changed */
            if (attenuation & bit) {
              PORTA |= bit;
            } else {
              PORTA &= ~bit;
            }
            /* changed relay, wait a bit */
            __delay_ms(RELAIS_MAX_SETUP_TIME);
          }
        }
      }
#elif ATT_CTRL == ATT_CTRL_MAKE_BEFORE_BREAK
      /* 1th do make operation */
      for (int cnt = 0; cnt < ROTARY_ATTENUATION_BITS; cnt++) {
        uint8_t bit = ((1 << cnt) & 0xff);

        if ((PORTA & bit) != (attenuation & bit)) {
          /* port bit needs to be changed */
          if (attenuation & bit) {
            PORTA |= bit;
          }
          /* changed relay, wait a bit */
          __delay_ms(RELAIS_MAX_SETUP_TIME);
        }
      }

      /* 2nd do the break operation */
      for (int cnt = 0; cnt < ROTARY_ATTENUATION_BITS; cnt++) {
        uint8_t bit = ((1 << cnt) & 0xff);

        if ((PORTA & bit) != (attenuation & bit)) {
          /* port bit needs to be changed */
          if ((attenuation & bit) == 0) {
            PORTA &= ~bit;
          }
          /* changed relay, wait a bit */
          __delay_ms(RELAIS_MAX_SETUP_TIME);
        }
      }
#else
      #error Unkown ATT_CTRL
#endif
      instance->last_attenuation = instance->attenuation;
    }
  }
}

void eeprom_save_status(volatile Instance_t* instance) {
    
#if 0
  if (instance->mode == Dual) { /* both encoders are used encoder1 for attenuation, encoder2 for channel */
    if (instance->eeprom_save_status_counter[Volume] != -1) {
      if (--instance->eeprom_save_status_counter[Volume] == 0) {
          
        printf("Save volume\r\n");  
          
        /* if default value for channel changed, store it */
        if (eeprom_read((unsigned char) instance->channel) != (unsigned char) instance->channel_attenuation[instance->channel].default_attenuation) {
          /* store current default attenuation which is applied after a channel switch */
          eeprom_write((unsigned char) instance->channel, (unsigned char) instance->channel_attenuation[instance->channel].default_attenuation);
        }
        
        instance->eeprom_save_status_counter[Volume] = -1; /* no action */
      }
    }
    
    if (instance->eeprom_save_status_counter[Channel] != -1) {
      if (--instance->eeprom_save_status_counter[Channel] == 0) {
        
          printf("Save channel\r\n");  
          
          /* if stored default channel not equal current one, update default channel */
        if (eeprom_read(EEPROM_ADDR_CHANNEL) != (unsigned char) instance->channel) {
          eeprom_write(EEPROM_ADDR_CHANNEL, (unsigned char) instance->channel);
        }
        
        instance->eeprom_save_status_counter[Channel] = -1; /* no action */
      }
    }
  } else {
      
      
        if (instance->eeprom_save_status_counter[Combined] != -1) {
      
      printf("eeprom_save_status_counter[Combined] %d\r\n", instance->eeprom_save_status_counter[Combined]);
    if (--instance->eeprom_save_status_counter[Combined] == 0) {
      
        printf("Save\r\n");
        
        /* if stored default channel not equal current one, update default channel */
      if (eeprom_read(EEPROM_ADDR_CHANNEL) != (unsigned char) instance->channel) {
        eeprom_write(EEPROM_ADDR_CHANNEL, (unsigned char) instance->channel);
      }

      /* if default value for channel changed, store it */
      if (eeprom_read((unsigned char) instance->channel) != (unsigned char) instance->channel_attenuation[instance->channel].default_attenuation) {
        /* store current default attenuation which is applied after a channel switch */
        eeprom_write((unsigned char) instance->channel, (unsigned char) instance->channel_attenuation[instance->channel].default_attenuation);
      }
      instance->eeprom_save_status_counter[Combined] = -1; /* not action */
    }
  }
        
  } 
  
#endif

}

void process_encoder_button(volatile Instance_t* instance) {
#if 0
  if (instance->mode == Dual) { /* both encoders are used encoder1 for attenuation, encoder2 for channel */
    /* Encoder 1 attenuation */
    if (instance->encoder[Volume].encoder_push_action) {
      if (instance->encoder[Volume].encoder_push_counter >= STORE_DEFAULT_ATTENUATION_TIME) {
        /* store current attenuation as default value */
        instance->channel_attenuation[instance->channel].default_attenuation = instance->attenuation;
        instance->eeprom_save_status_counter[Volume] = EEPROM_SAVE_STATUS_VALUE;
        
        printf("instance->encoder[Volume].encoder_push_action %d encoder_push_counter %d\r\n", instance->encoder[Volume].encoder_push_action, instance->encoder[Volume].encoder_push_counter);
      } else {
        /* no short press function for now */
      }
      
      
      
      /* reset after operation */
      instance->encoder[Volume].encoder_push_counter = instance->encoder[Volume].encoder_push_action = 0;
    }

    /* Encoder 2 channel */
    if (instance->encoder[Channel].encoder_push_action) {
      if (instance->encoder[Channel].encoder_push_counter >= STORE_DEFAULT_ATTENUATION_TIME) {
        /* store current attenuation as default value */
        //instance->channel_attenuation[instance->channel].default_attenuation = instance->attenuation;
        instance->eeprom_save_status_counter[Channel] = EEPROM_SAVE_STATUS_VALUE;
        
        printf("instance->encoder[Channel].encoder_push_action %d encoder_push_counter %d\r\n", instance->encoder[Channel].encoder_push_action, instance->encoder[Channel].encoder_push_counter);
        
      } else {
        /* no short press function for now */
      }
      
        
        
        
      /* reset after operation */
      instance->encoder[Channel].encoder_push_counter = instance->encoder[Channel].encoder_push_action = 0;
    }
  } else {
    if (instance->encoder[Combined].encoder_push_action) {
      if (instance->encoder[Combined].encoder_push_counter >= STORE_DEFAULT_ATTENUATION_TIME) {
        /* store current attenuation as default value */
        instance->channel_attenuation[instance->channel].default_attenuation = instance->attenuation;
        instance->eeprom_save_status_counter[Combined] = EEPROM_SAVE_STATUS_VALUE;
      } else {
        /* switch control mode */
        if (instance->control == Volume) {
          instance->control = Channel;
        } else {
          instance->control = Volume;
        }
        /* for debugging switching between attenuation and channel */
#if 0
        LED_Toggle();
#endif
        /* reset rotary encoder vars */
        instance->encoder[Combined].direction = DIR_NONE;
        instance->encoder[Combined].encoder_count[instance->control] = 0;
      }

      /* reset after operation */
      instance->encoder[Combined].encoder_push_counter = instance->encoder[Combined].encoder_push_action = 0;
    }
  }
#endif
}

void process_ir(Instance_t* instance) {
  if (irmp_get_data(&instance->ir.data)) {
    // ir signal decoded, do something here...
    // irmp_data.protocol is the protocol, see irmp.h
    // irmp_data.address is the address/manufacturer code of ir sender
    // irmp_data.command is the command code
    // irmp_protocol_names[irmp_data.protocol] is the protocol name (if enabled, see irmpconfig.h)
    printf("proto %u addr %u cmd %u flags %u\r\n", instance->ir.data.protocol, instance->ir.data.address, instance->ir.data.command, instance->ir.data.flags);

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
              instance->channel_attenuation[instance->channel].default_attenuation = instance->attenuation;
             // instance->eeprom_save_status_counter = 1;
              
              
              if (instance->mode == Dual) {
              instance->eeprom_save_status_counter[Volume] = 1;
              //instance->eeprom_save_status_counter[Volume] = 1;
              } else {
                  
              }
              
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
