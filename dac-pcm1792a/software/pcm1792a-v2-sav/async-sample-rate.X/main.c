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

#include "mcc_generated_files/mcc.h"
#include "mcc_generated_files/examples/i2c1_master_example.h"






// Page 38 
#define SRC4392_I2C_SLAVE_ADDR              0x70


// SRC4392 control/status registers
#define SRC_REG01	0x01		// power down and reset
#define SRC_REG02	0x02		// global interrupt status
#define SRC_REG03	0x03		// port A control
#define SRC_REG04	0x04		// port A control
#define SRC_REG05	0x05		// port B control
#define SRC_REG06	0x06		// port B control
#define SRC_REG07	0x07		// DIT control
#define SRC_REG08	0x08		// DIT control
#define SRC_REG09	0x09		// DIT control
#define SRC_REG0A	0x0a		// SRC and DIT status
#define SRC_REG0B	0x0b		// SRC and DIT interrupt mask
#define SRC_REG0C	0x0c		// SRC and DIT interrupt mode
#define SRC_REG0D	0x0d		// DIR control
#define SRC_REG0E	0x0e		// DIR control
#define SRC_REG0F	0x0f		// DIR PLL configuration
#define SRC_REG10	0x10		// DIR PLL configuration
#define SRC_REG11	0x11		// DIR PLL configuration
#define SRC_REG12	0x12		// non-PCM audio detection
#define SRC_REG13	0x13		// DIR status
#define SRC_REG14	0x14		// DIR status
#define SRC_REG15	0x15		// DIR status
#define SRC_REG16	0x16		// DIR interrupt mask
#define SRC_REG17	0x17		// DIR interrupt mask
#define SRC_REG18	0x18		// DIR interrupt mode
#define SRC_REG19	0x19		// DIR interrupt mode
#define SRC_REG1A	0x1a		// DIR interrupt mode
#define SRC_REG1B	0x1b		// GP01
#define SRC_REG1C	0x1c		// GP02
#define SRC_REG1D	0x1d		// GP03
#define SRC_REG1E	0x1e		// GP04
#define SRC_REG1F	0x1f		// audio CD Q-channel subcode
#define SRC_REG20	0x20		// audio CD Q-channel subcode
#define SRC_REG21	0x21		// audio CD Q-channel subcode
#define SRC_REG22	0x22		// audio CD Q-channel subcode
#define SRC_REG23	0x23		// audio CD Q-channel subcode
#define SRC_REG24	0x24		// audio CD Q-channel subcode
#define SRC_REG25	0x25		// audio CD Q-channel subcode
#define SRC_REG26	0x26		// audio CD Q-channel subcode
#define SRC_REG27	0x27		// audio CD Q-channel subcode
#define SRC_REG28	0x28		// audio CD Q-channel subcode
#define SRC_REG29	0x29		// PC burst preamble, high byte
#define SRC_REG2A	0x2a		// PC burst preamble, low byte
#define SRC_REG2B	0x2b		// PD burst preamble, high byte
#define SRC_REG2C	0x2c		// PD burst preamble, low byte
#define SRC_REG2D	0x2d		// SRC control
#define SRC_REG2E	0x2e		// SRC control
#define SRC_REG2F	0x2f		// SRC control
#define SRC_REG30	0x30		// SRC control
#define SRC_REG31	0x31		// SRC control
#define SRC_REG32	0x32		// SRC input/output ratio
#define SRC_REG33	0x33		// SRC input/output ratio
#define SRC_REG7F	0x7f		// page selection



// Sample rate enums
#define SAMPLERATE_UNKNOWN	0	// unknown
#define SAMPLERATE_32KHZ	1	// 32.0KHz
#define SAMPLERATE_44KHZ	2	// 44.1KHz
#define SAMPLERATE_48KHZ	3	// 48.0KHz
#define SAMPLERATE_64KHZ	4	// 64.0KHz
#define SAMPLERATE_88KHZ	5	// 88.2KHz
#define SAMPLERATE_96KHZ	6	// 96.0KHz
#define SAMPLERATE_128KHZ	7	// 128.0KHz
#define SAMPLERATE_176KHZ	8	// 176.4KHz
#define SAMPLERATE_192KHZ	9	// 192.0KHz

/*
 * Upsampling enums
 */
#define UPSAMPLE_192KHZ		0	// 192KHz
#define UPSAMPLE_96KHZ		1	// 96KHz

/*
 * DIT routing mode enums
 */
#define DIT_UPSAMPLE		0	// upsample
#define DIT_LOOPOUT		1	// loop-back

/*
 * Digital de-emphasis enums
 */
#define DEEMPH_AUTO		0	// auto
#define DEEMPH_OFF		1	// off


uint8_t		upsample_rate = UPSAMPLE_192KHZ;
uint8_t		dit_mode = DIT_UPSAMPLE;


// input 0,1,2 or 3

#define INPUT_RX1   0
#define INPUT_RX2   1
#define INPUT_RX3   2
#define INPUT_RX4   3
#define MAX_INPUTS  INPUT_RX4

//#define SRC_OUTPUT_BITS 20
#define SRC_OUTPUT_BITS 24

#define __PCM1972A__


#define PCM1792A_I2C_SLAVE_ADDR              0x4c

// Register 18 => default

// Register 19 
//#define PCM1792A_REG19_VALUE        0x1302 /* 0x13 == Reg 19, 0x02 FLT = Slow rolloff */


#define PCM1792A_REG16        0x10 /* 0x10 == Reg 16, Digital Attenuation Level Setting left */
#define PCM1792A_REG16_VALUE        0xff /* 0dB, not attenuation */

#define PCM1792A_REG17        0x11 /* 0x11 == Reg 17, Digital Attenuation Level Setting left */
#define PCM1792A_REG17_VALUE        0xff /* 0dB, not attenuation */



#define PCM1792A_REG19        0x13 /* 0x13 == Reg 19 */
#define PCM1792A_REG19_VALUE        0x02 /* 0x02 FLT = Slow rolloff */






#define CHAN_SEL_MASK                  0x0f

#define EEPROM_ADDR_CHANNEL            0x04 /* EEPROM address of current channel */

#define ROTARY_MIN_CHANNEL                0 /* minimum channel */
#define ROTARY_MAX_CHANNEL                3 /* maximum channel */
#define ROTARY_MULTI_CHANNEL              3 /* on 12PPR this gaves 3 clicks */

#define ROTARY_ATTENUATION_BITS           6 /* 6 bits */
#define ROTARY_MIN_ATTENUATION            0 /* minimum attenuation */
#define ROTARY_MAX_ATTENUATION         ((1 << ROTARY_ATTENUATION_BITS) - 1) /* (0x3f) maximum attenuation */
#define ROTARY_MULTI_ATTENUATION          1 /* on 12PPR this gaves 1 clicks */

#define MAIN_LOOP_WAIT                    1 /* 1ms */
#define EEPROM_SAVE_STATUS_VALUE       1000 /* 1 seconds on a 1ms loop */
#define RELAIS_SETUP_TIME                 1 /* 1ms */

#define ROTARY_PUSH_DEBOUNCE             20 /* 20 ms on a 1ms timer IRQ */
#define STORE_DEFAULT_ATTENUATION_TIME ((3 /* seconds */ * 1000) / ROTARY_PUSH_DEBOUNCE) /* 3 seconds till storing default attenuation */

/* eeprom initialize 0x00..0x07 */
__EEPROM_DATA(ROTARY_MAX_ATTENUATION /* channel 0 attenuation initial */,
              ROTARY_MAX_ATTENUATION /* channel 1 attenuation initial */,
              ROTARY_MAX_ATTENUATION /* channel 2 attenuation initial */,
              ROTARY_MAX_ATTENUATION /* channel 3 attenuation initial */,
              ROTARY_MIN_CHANNEL     /* channel selection initial     */,
              0xff, 0xff, 0xff);

enum Control { Combined = 0, Volume = 0, Channel = 1};
enum Mode { Single = 0, Dual = 1 };

typedef struct {
  uint8_t direction;
  int encoder_count[2 /* Volume = 0,  Channel = 1 */];
  /* rotary encoder state */
  uint8_t rotary_encoder_state;
  /* encoder push button */
  int encoder_push_debounce_counter;
  int encoder_push_counter;
  int encoder_push_action;
} RotaryEncoder_t;

typedef struct {
  int default_attenuation;
  int attenuation;
} ChannelVolume_t;

typedef struct {
  enum Mode mode; /* single or dual encoder mode */
  int channel;
  int last_channel;
  int attenuation;
  int last_attenuation;
  int eeprom_save_status_counter;
  ChannelVolume_t channel_attenuation[ROTARY_MAX_CHANNEL + 1]; /* channel 0..3 */
  /* irq changed */
  volatile enum Control control;
  RotaryEncoder_t encoder[2 /* 0 = Combined/Volume, 1 = Channel */];
} Instance_t;

volatile Instance_t instance = {
  .mode = Single, .channel = -1, .last_channel = -1,
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

static void init(volatile Instance_t* instance)
{
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

    /* mute output */
     PORTB &= ~CHAN_SEL_MASK;
    __delay_ms(RELAIS_SETUP_TIME);

    /* always start with last attenuation used for this channel */
    instance->last_attenuation = instance->attenuation = instance->channel_attenuation[instance->channel].attenuation;
    PORTA = ((PORTA & ~ROTARY_MAX_ATTENUATION) | ((unsigned char)instance->attenuation & ROTARY_MAX_ATTENUATION));

    /* clear and set new channel */
    PORTB = ((PORTB & ~CHAN_SEL_MASK) | ((1 << instance->channel) & CHAN_SEL_MASK));
    __delay_ms(RELAIS_SETUP_TIME);

    instance->last_channel = instance->channel;
    instance->eeprom_save_status_counter = EEPROM_SAVE_STATUS_VALUE;
  }
}




/* attenuator relay are on RA0...RA5 */
static void process_attenuation(volatile Instance_t* instance) {
  if (instance->attenuation != instance->last_attenuation) {
    unsigned char attenuation = ((unsigned char) instance->attenuation & ROTARY_MAX_ATTENUATION);

    if ((PORTA & ROTARY_MAX_ATTENUATION) != attenuation) {
      /* something needs to be changed */
#if 1 /* improved setting algo, with direction in mind */
      if (instance->encoder[Volume].direction == DIR_CW) { /* clockwise, attenuation increase */
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
            __delay_ms(RELAIS_SETUP_TIME);
          }
        }
      } else { /* counter clockwise, attenuation decrease */
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
            __delay_ms(RELAIS_SETUP_TIME);
          }
        }
      }
#else
      /* mute output */
       PORTB &= ~CHAN_SEL_MASK;
      __delay_ms(RELAIS_SETUP_TIME);

      PORTA = ((PORTA & ~ROTARY_MAX_ATTENUATION) | ((unsigned char)instance->attenuation & ROTARY_MAX_ATTENUATION));
      __delay_ms(RELAIS_SETUP_TIME);
#endif
      instance->last_attenuation = instance->attenuation;
    }
  }
}

static void eeprom_save_status(volatile Instance_t* instance) {
  if (instance->eeprom_save_status_counter != -1) {
    if (--instance->eeprom_save_status_counter == 0) {
      /* if stored default channel not equal current one, update default channel */
      if (eeprom_read(EEPROM_ADDR_CHANNEL) != (unsigned char) instance->channel) {
        eeprom_write(EEPROM_ADDR_CHANNEL, (unsigned char) instance->channel);
      }

      /* if default value for channel changed, store it */
      if (eeprom_read((unsigned char) instance->channel) != (unsigned char) instance->channel_attenuation[instance->channel].default_attenuation) {
        /* store current default attenuation which is applied after a channel switch */
        eeprom_write((unsigned char) instance->channel, (unsigned char) instance->channel_attenuation[instance->channel].default_attenuation);
      }
      instance->eeprom_save_status_counter = -1; /* not action */
    }
  }
}

static void process_encoder_button(volatile Instance_t* instance) {
  if (instance->mode == Dual) { /* both encoders are used encoder1 for attenuation, encoder2 for channel */
    /* Encoder 1 attenuation */
    if (instance->encoder[Volume].encoder_push_action) {
      if (instance->encoder[Volume].encoder_push_counter >= STORE_DEFAULT_ATTENUATION_TIME) {
        /* store current attenuation as default value */
        instance->channel_attenuation[instance->channel].default_attenuation = instance->attenuation;
        instance->eeprom_save_status_counter = EEPROM_SAVE_STATUS_VALUE;
      } else {
        /* no short press function for now */
      }
      /* reset after operation */
      instance->encoder[Volume].encoder_push_counter = instance->encoder[Volume].encoder_push_action = 0;
    }

    /* Encoder 2 channel */
    if (instance->encoder[Channel].encoder_push_action) {
      /* reset after operation */
      instance->encoder[Volume].encoder_push_counter = instance->encoder[Volume].encoder_push_action = 0;
    }
  } else {
    if (instance->encoder[Combined].encoder_push_action) {
      if (instance->encoder[Combined].encoder_push_counter >= STORE_DEFAULT_ATTENUATION_TIME) {
        /* store current attenuation as default value */
        instance->channel_attenuation[instance->channel].default_attenuation = instance->attenuation;
        instance->eeprom_save_status_counter = EEPROM_SAVE_STATUS_VALUE;
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
}

static void timer_callback_process_dual(void) {
  /* encoder1 used for attenuation */
  uint8_t encoder_direction = encoder1_read(&instance.encoder[Volume].rotary_encoder_state);
  if (encoder_direction != DIR_NONE) {
    /* detect direction, if changed, reset rotary encoder vars */
    if (instance.encoder[Volume].direction != encoder_direction) {
      instance.encoder[Volume].encoder_count[0] = 0;
    }
    instance.encoder[Volume].direction = encoder_direction;

    if (encoder_direction == DIR_CW) {
      instance.encoder[Volume].encoder_count[0]++;
    } else if (encoder_direction == DIR_CCW) {
      instance.encoder[Volume].encoder_count[0]--;
    }

    /**
     * attenuation works inverse as it is a attenuator
     * 0   : 0dB attenuation
     * 255 : 127dB attenuation
     */
    int value = instance.attenuation;

    if (instance.encoder[Volume].encoder_count[0] >= ROTARY_MULTI_ATTENUATION) {
      value--;
      instance.encoder[Volume].encoder_count[0] = 0;
    } else if (instance.encoder[Volume].encoder_count[0] <= -ROTARY_MULTI_ATTENUATION) {
      value++;
      instance.encoder[Volume].encoder_count[0] = 0;
    }

    /* for attenuation stop on max or min */
    if (value > ROTARY_MAX_ATTENUATION) {
      instance.attenuation = ROTARY_MAX_ATTENUATION;
    } else if (value < ROTARY_MIN_ATTENUATION) {
      instance.attenuation = 0;
    } else {
      instance.attenuation = value;
    }
  }

  /* encoder2 used for channel */
  encoder_direction = encoder2_read(&instance.encoder[Channel].rotary_encoder_state);
  if (encoder_direction != DIR_NONE) {
    /* detect direction, if changed, reset rotary encoder vars */
    if (instance.encoder[Channel].direction != encoder_direction) {
      instance.encoder[Channel].encoder_count[0] = 0;
    }
    instance.encoder[Channel].direction = encoder_direction;

    if (encoder_direction == DIR_CW) {
      instance.encoder[Channel].encoder_count[0]++;
    } else if (encoder_direction == DIR_CCW) {
      instance.encoder[Channel].encoder_count[0]--;
    }

    int value = instance.channel;

    if (instance.encoder[Channel].encoder_count[0] >= ROTARY_MULTI_CHANNEL) {
      value++;
      instance.encoder[Channel].encoder_count[0] = 0;
    } else if (instance.encoder[Channel].encoder_count[0] <= -ROTARY_MULTI_CHANNEL) {
      value--;
      instance.encoder[Channel].encoder_count[0] = 0;
    }

    /* channel is rotary continuous */
    if (value > ROTARY_MAX_CHANNEL) {
      instance.channel = 0;
    } else if (value < ROTARY_MIN_CHANNEL) {
      instance.channel = ROTARY_MAX_CHANNEL;
    } else {
      instance.channel = value;
    }
  }

  if (instance.encoder[Volume].encoder_push_action != 1) {
    /* no push action pending */
    uint8_t encoder_switch_level = ENC1SWITCH_GetValue();
    if (encoder_switch_level == 0) {
      instance.encoder[Volume].encoder_push_counter =
          (++instance.encoder[Volume].encoder_push_debounce_counter / ROTARY_PUSH_DEBOUNCE);
    } else {
      if (instance.encoder[Volume].encoder_push_counter >= 1) {
        /* flag push action to be processed */
        instance.encoder[Volume].encoder_push_action = 1;
      }
      instance.encoder[Volume].encoder_push_debounce_counter = 0;
    }
  }

  if (instance.encoder[Channel].encoder_push_action != 1) {
    /* no push action pending */
    uint8_t encoder_switch_level = ENC2SWITCH_GetValue();
    if (encoder_switch_level == 0) {
      instance.encoder[Channel].encoder_push_counter =
          (++instance.encoder[Channel].encoder_push_debounce_counter / ROTARY_PUSH_DEBOUNCE);
    } else {
      if (instance.encoder[Channel].encoder_push_counter >= 1) {
        /* flag push action to be processed */
        instance.encoder[Channel].encoder_push_action = 1;
      }
      instance.encoder[Channel].encoder_push_debounce_counter = 0;
    }
  }
}

static void timer_callback_process_single(void) {
  uint8_t encoder_direction = encoder1_read(&instance.encoder[Combined].rotary_encoder_state);
  if (encoder_direction != DIR_NONE) {
    /* detect direction, if changed, reset rotary encoder vars */
    if (instance.encoder[Combined].direction != encoder_direction) {
      instance.encoder[Combined].encoder_count[instance.control] = 0;
    }
    instance.encoder[Combined].direction = encoder_direction;

    if (encoder_direction == DIR_CW) {
      instance.encoder[Combined].encoder_count[instance.control]++;
    } else if (encoder_direction == DIR_CCW) {
      instance.encoder[Combined].encoder_count[instance.control]--;
    }

    if (instance.control == Volume) {
      /**
       * attenuation works inverse as it is a attenuator
       * 0   : 0dB attenuation
       * 255 : 127dB attenuation
       */
      int value = instance.attenuation;

      if (instance.encoder[Combined].encoder_count[instance.control] >= ROTARY_MULTI_ATTENUATION) {
        value--;
        instance.encoder[Combined].encoder_count[instance.control] = 0;
      } else if (instance.encoder[Combined].encoder_count[instance.control] <= -ROTARY_MULTI_ATTENUATION) {
        value++;
        instance.encoder[Combined].encoder_count[instance.control] = 0;
      }

      /* for attenuation stop on max or min */
      if (value > ROTARY_MAX_ATTENUATION) {
        instance.attenuation = ROTARY_MAX_ATTENUATION;
      } else if (value < ROTARY_MIN_ATTENUATION) {
        instance.attenuation = 0;
      } else {
        instance.attenuation = value;
      }
    } else {
      int value = instance.channel;

      if (instance.encoder[Combined].encoder_count[instance.control] >= ROTARY_MULTI_CHANNEL) {
        value++;
        instance.encoder[Combined].encoder_count[instance.control] = 0;
      } else if (instance.encoder[Combined].encoder_count[instance.control] <= -ROTARY_MULTI_CHANNEL) {
        value--;
        instance.encoder[Combined].encoder_count[instance.control] = 0;
      }

      /* channel is rotary continous */
      if (value > ROTARY_MAX_CHANNEL) {
        instance.channel = 0;
      } else if (value < ROTARY_MIN_CHANNEL) {
        instance.channel = ROTARY_MAX_CHANNEL;
      } else {
        instance.channel = value;
      }
    }
  }

  if (instance.encoder[Combined].encoder_push_action != 1) {
    /* no push action pending */
    uint8_t encoder_switch_level = ENC1SWITCH_GetValue();
    if (encoder_switch_level == 0) {
      instance.encoder[Combined].encoder_push_counter = (++instance.encoder[Combined].encoder_push_debounce_counter / ROTARY_PUSH_DEBOUNCE);
    } else {
      if (instance.encoder[Combined].encoder_push_counter >= 1) {
        /* flag push action to be processed */
        instance.encoder[Combined].encoder_push_action = 1;
      }
      instance.encoder[Combined].encoder_push_debounce_counter = 0;
    }
  }
}

/* uses 10us time, measured with LED_Toggle();*/
void timer_callback(void)
{
/* use to measure irq call time */
#if 0
  LED_Toggle();
#endif
  if (instance.mode == Dual) {
    /* both encoders are used encoder1 for attenuation, encoder2 for channel */
    timer_callback_process_dual();
  } else {
    /* single encoder for both attenuation and channel */
    timer_callback_process_single();
  }
/* use for measure irq execution time (10us) */
#if 0
  LED_Toggle();
#endif
}
















volatile signed int encoder_count;


// Read one byte from the SRC4392
uint8_t src4392_read(uint8_t reg)
{
    return I2C1_Read1ByteRegister(SRC4392_I2C_SLAVE_ADDR, reg);   
}


// Write one byte to the SRC4392
void src4392_write(uint8_t reg, uint8_t val)
{
    I2C1_Write1ByteRegister(SRC4392_I2C_SLAVE_ADDR, reg, val);
}

#if 0
void pcm1792a_write(uint8_t reg, uint16_t val)
{
    I2C1_Write2ByteRegister(PCM1792A_I2C_SLAVE_ADDR, reg, val);
}
#else
void pcm1792a_write(uint8_t reg, uint8_t val)
{
    I2C1_Write2ByteRegister(PCM1792A_I2C_SLAVE_ADDR, reg, val);
}
#endif



// Set the digital de-emphasis mode
// mode: DEEMPH_AUTO or DEEMPH_OFF
void set_deemphasis(uint8_t mode)
{
	if (mode != DEEMPH_AUTO && mode != DEEMPH_OFF)
		return;		// error checking

	// Select SRC4392 page 0
	src4392_write(SRC_REG7F, 0x00);

	if (mode == DEEMPH_AUTO) {
		src4392_write(SRC_REG2E, 0x20);
	}
	else if (mode == DEEMPH_OFF) {
		src4392_write(SRC_REG2E, 0x00);
	}
}

// Set the upsample rate
// rate: UPSAMPLE_192KHZ or UPSAMPLE_96KHZ
void set_upsample(uint8_t rate)
{
	if (rate != UPSAMPLE_192KHZ && rate != UPSAMPLE_96KHZ)
		return;		// error checking

    // mute audio
    
	// Select SRC4392 page 0
	src4392_write(SRC_REG7F, 0x00);

	if (rate == UPSAMPLE_192KHZ) {
		// SRC4392 DIT setup:
		// - SRC as the input data source
		// - MCLK as master clock
		// - clock divider 128 to set the output frame rate
		// - block start is an output and valid audio is indicated
		// - c and u data will not be updated
		src4392_write(SRC_REG07, 0x1c);

		// set up for 192KHz output 
		src4392_write(SRC_REG08, 0x08);
		src4392_write(SRC_REG7F, 0x02);
		src4392_write(0x00, 0x80);
		src4392_write(0x01, 0x80);
		src4392_write(0x08, 0x18);
		src4392_write(0x09, 0x18);
		src4392_write(SRC_REG7F, 0x00);
		src4392_write(SRC_REG08, 0x00);

		// SRC4392 Port A setup:
		// - MCLK as clock source
		// - clock divider 128
		src4392_write(SRC_REG04, 0x00);
	}
	else if (rate == UPSAMPLE_96KHZ) {
		// SRC4392 DIT setup:
		// - SRC as the input data source
		// - MCLK as master clock
		// - clock divider 256 to set the output frame rate
		// - block start is an output and valid audio is indicated
		// - c and u data will not be updated
		src4392_write(SRC_REG07, 0x3c);

		// set up for 96KHz output 
		src4392_write(SRC_REG08, 0x08);
		src4392_write(SRC_REG7F, 0x02);
		src4392_write(0x00, 0x80);
		src4392_write(0x01, 0x80);
		src4392_write(0x08, 0x08);
		src4392_write(0x09, 0x08);
		src4392_write(SRC_REG7F, 0x00);
		src4392_write(SRC_REG08, 0x00);

		// SRC4392 Port A setup:
		// - MCLK as clock source
		// - clock divider 256
		src4392_write(SRC_REG04, 0x01);
	}

	// Un-mute audio
}

// Set the DIT (digital output) routing
// input: input number, mode: DIT_LOOPOUT or DIT_UPSAMPLE
void set_dit_mode(uint8_t input, uint8_t mode)
{
	uint8_t	val;

	if ((mode != DIT_UPSAMPLE && mode != DIT_LOOPOUT) ||
	    input > MAX_INPUTS)
		return;		// error checking

	// Select SRC4392 page 0
	src4392_write(SRC_REG7F, 0x00);

	if (mode == DIT_UPSAMPLE) {
		if (upsample_rate == UPSAMPLE_192KHZ) {
			// DIT setup
			// - SRC as the input data source
			// - MCLK as master clock
			// - clock divider 128 to set the output frame rate
			// - block start is an output and valid audio
			//   is indicated
			// - c and u data will not be updated
			src4392_write(SRC_REG07, 0x1c);

			// set up for 192KHz output 
			src4392_write(SRC_REG08, 0x08);
			src4392_write(SRC_REG7F, 0x02);
			src4392_write(0x00, 0x80);
			src4392_write(0x01, 0x80);
			src4392_write(0x08, 0x18);
			src4392_write(0x09, 0x18);
			src4392_write(SRC_REG7F, 0x00);
			src4392_write(SRC_REG08, 0x00);
		}
		else if (upsample_rate == UPSAMPLE_96KHZ) {
			// DIT setup
			// - SRC as the input data source
			// - MCLK as master clock
			// - clock divider 256 to set the output frame rate
			// - block start is an output and valid audio
			//   is indicated
			// - c and u data will not be updated
			src4392_write(SRC_REG07, 0x3c);

			// set up for 96KHz output 
			src4392_write(SRC_REG08, 0x08);
			src4392_write(SRC_REG7F, 0x02);
			src4392_write(0x00, 0x80);
			src4392_write(0x01, 0x80);
			src4392_write(0x08, 0x08);
			src4392_write(0x09, 0x08);
			src4392_write(SRC_REG7F, 0x00);
			src4392_write(SRC_REG08, 0x00);
		}
	}
	else if (mode == DIT_LOOPOUT) {
		// set both AES and TX outputs to receive their
		// data via the bypass multiplexor without going
		// through the DIT block.
		val = (uint8_t)((input) << 6 | 0x30);       
		src4392_write(SRC_REG08, val);
	}
}


// Set the input
// input: 0..4, mode: DIT_UPSAMPLE or DIT_LOOPOUT
void set_input(uint8_t input, uint8_t mode)
{
	uint8_t	val;

	if ((input > MAX_INPUTS) ||
	    (mode != DIT_UPSAMPLE && mode != DIT_LOOPOUT))
		return;		// error checking

	// Select page 0
	src4392_write(SRC_REG7F, 0x00);

    // - set DIR input source to the appropriate RX port
    // - use MCLK as clock source
    // - audio muted for loss of lock condition
    // - PLL free runs for loss of lock condition
    // - RXCKO output disabled
    val = 0x08 | input;
    src4392_write(SRC_REG0D, val);
    src4392_write(SRC_REG0E, 0x18);

    // set SRC input source to DIR
    src4392_write(SRC_REG2D, 0x02);

	// update DIT mode
	set_dit_mode(input, mode);
}

// Return the enum representing the current sample rate (SAMPLERATE_xxKHZ).
uint8_t get_sample_rate(void)
{
	uint8_t	val0, val1;

	// Select SRC4392 page 0
	src4392_write(SRC_REG7F, 0x00);

	val0 = src4392_read(SRC_REG32);
	val1 = src4392_read(SRC_REG33);

	if (upsample_rate == UPSAMPLE_192KHZ) {
		// for output sample rate = 192K
		if ((val0 == 0x07 && val1 == 0xff) ||
		    (val0 == 0x08 && val1 == 0x00)) {
			return SAMPLERATE_192KHZ;
		}
		else if (val0 == 0x07 && val1 == 0x59) {
			return SAMPLERATE_176KHZ;
		}
		else if (val0 == 0x05 && val1 == 0x55) {
			return SAMPLERATE_128KHZ;
		}
		else if ((val0 == 0x03 && val1 == 0xff) ||
			 (val0 == 0x04 && val1 == 0x00)) {
			return SAMPLERATE_96KHZ;
		}
		else if (val0 == 0x03 && val1 == 0xac) {
			return SAMPLERATE_88KHZ;
		}
		else if (val0 == 0x02 && val1 == 0xaa) {
			return SAMPLERATE_64KHZ;
		}
		else if ((val0 == 0x01 && val1 == 0xff) ||
			 (val0 == 0x02 && val1 == 0x00)) {
			return SAMPLERATE_48KHZ;
		}
		else if (val0 == 0x01 && val1 == 0xd6) {
			return SAMPLERATE_44KHZ;
		}
		else if (val0 == 0x01 && val1 == 0x55) {
			return SAMPLERATE_32KHZ;
		}
	}
	else if (upsample_rate == UPSAMPLE_96KHZ) {
		// for output sample rate of 96KHz
		if ((val0 == 0x0f && val1 == 0xff) ||
		    (val0 == 0x10 && val1 == 0x00)) {
			return SAMPLERATE_192KHZ;
		}
		else if (val0 == 0x0e && val1 == 0xb3) {
			return SAMPLERATE_176KHZ;
		}
		else if (val0 == 0x0a && val1 == 0xaa) {
			return SAMPLERATE_128KHZ;
		}
		else if ((val0 == 0x07 && val1 == 0xff) ||
			 (val0 == 0x08 && val1 == 0x00)) {
			return SAMPLERATE_96KHZ;
		}
		else if (val0 == 0x07 && val1 == 0x59) {
			return SAMPLERATE_88KHZ;
		}
		else if (val0 == 0x05 && val1 == 0x55) {
			return SAMPLERATE_64KHZ;
		}
		else if ((val0 == 0x03 && val1 == 0xff) ||
			 (val0 == 0x04 && val1 == 0x00)) {
			return SAMPLERATE_48KHZ;
		}
		else if (val0 == 0x03 && val1 == 0xac) {
			return SAMPLERATE_44KHZ;
		}
		else if (val0 == 0x02 && val1 == 0xaa) {
			return SAMPLERATE_32KHZ;
		}
	}

	return SAMPLERATE_UNKNOWN;
}


void init(void)
{   
    __delay_ms(100);
    RESET_SetLow();
    __delay_ms(100);
    RESET_SetHigh();
    __delay_ms(10);
	
    // Select page 0
	src4392_write(SRC_REG7F, 0x00);

	// DIR setup:
	// - set default input source
	// - use MCLK as clock source
	// - audio not muted for loss of lock condition
	// - PLL stops for loss of lock condition
	// - RXCKO output disabled
    
    // 000010 00
    // 00 => RXMUX1 / RXMUX0 => (RX1)
    // 0
    // 1 => RXCLK => MCLK
	src4392_write(SRC_REG0D, 0x08);	// default input source = RX1
	src4392_write(SRC_REG0E, 0x00);

	// PLL1 setup:
	// 24.576MHz, p = 2, j = 8, d = 0
	src4392_write(SRC_REG0F, 0x22);
	src4392_write(SRC_REG10, 0x00);
	src4392_write(SRC_REG11, 0x00);

	// Set GP01 for DIR non-audio flag
	src4392_write(SRC_REG1B, 0x06);
	// Set GP02 for DIR non-valid flag
	src4392_write(SRC_REG1C, 0x07);
	// Set GP03 for DIR emphasis flag
	src4392_write(SRC_REG1D, 0x05);
	// Set GP04 for DIR parity error flag
	src4392_write(SRC_REG1E, 0x0d);

	// SRC setup:
	// - DIR as the input data source
	// - use MCLK as clock source
	// - autodem enabled
	src4392_write(SRC_REG2D, 0x02);	// default input source = DIR
	src4392_write(SRC_REG2E, 0x20);

#if 0
#if SRC_OUTPUT_BITS == 24
    src4392_write(SRC_REG2F, 0x00); // SRC output 24 Bit
#elif SRC_OUTPUT_BITS == 20
    src4392_write(SRC_REG2F, 0x40); // SRC output 20 Bit
#else
    // default 24 Bit
    src4392_write(SRC_REG2F, 0x00); // SRC output 24 Bit
#endif
#else
    if (SEL_GetValue()) {
        src4392_write(SRC_REG2F, 0x00); // SRC output 24 Bit
    }
    else {
        src4392_write(SRC_REG2F, 0x40); // SRC output 20 Bit
    }
#endif
    
    
	src4392_write(SRC_REG30, 0x00);
	src4392_write(SRC_REG31, 0x00);

	// DIT setup:
	// - SRC as the input data source
	// - MCLK as master clock
	// - clock divider 128 to set the output frame rate
	// - block start is an output and valid audio is indicated
	// - c and u data will not be updated
    
    // 0x1c => 0001'1100
	src4392_write(SRC_REG07, 0x1c);
	src4392_write(SRC_REG08, 0x00);
	src4392_write(SRC_REG09, 0x00);

	// set up for 192KHz output
	src4392_write(SRC_REG08, 0x08);
	src4392_write(SRC_REG7F, 0x02);
	src4392_write(0x00, 0x80);
	src4392_write(0x01, 0x80);
	src4392_write(0x08, 0x18);
	src4392_write(0x09, 0x18);
	src4392_write(SRC_REG7F, 0x00);
	src4392_write(SRC_REG08, 0x00);

	// Power up all blocks
	src4392_write(SRC_REG01, 0x3f);

	// Port A setup:
	// - master with i2s data format
	// - SRC as input data source
	// - MCLK as clock source
	// - clock divider 128
	src4392_write(SRC_REG03, 0x39);
	src4392_write(SRC_REG04, 0x00);

	// Port B setup:
	// - slave with i2s data format
	src4392_write(SRC_REG05, 0x01);
	src4392_write(SRC_REG06, 0x00);
    

    
#ifdef __PCM1972A__
    pcm1792a_write(PCM1792A_REG19, PCM1792A_REG19_VALUE);
    
    // attenuation left -31.5dB
    //pcm1792a_write(PCM1792A_REG16, 0xc0);
    // attenuation right -31.5dB
    //pcm1792a_write(PCM1792A_REG17, 0xc0);
                 
#endif
    
}




static uint8_t get_chan_sel(void)
{
    uint8_t ret = 0xff;
    
#ifdef __ROTARY_ENCODER__
    if (encoder_count >= 0) {
        ret = (uint8_t)encoder_count / ROTARY_MULTI;
    }
#else
    /**
     * PORTB weak pull-up RB7..RB4
     * Input selector ties to GND so we invert the bits here
     */
    uint8_t input = (~(PORTB >> 4)) & 0x0f;
    
    switch (input) {
        case 0x01: /* INPUT 1, RB4 tie to GND */
            ret = 0;
            break;
        case 0x02: /* INPUT 2, RB5 tie to GND */
            ret = 1;
            break;
        case 0x04: /* INPUT 3, RB6 tie to GND */
            ret = 2;
            break;
        case 0x08: /* INPUT 4, RB7 tie to GND */
            ret = 3;
            break;
        default:
            break;
    }
#endif
    return ret;
}

#ifdef __ROTARY_ENCODER__
const signed char table[] = { 0, -1, +1, 0, +1, 0, 0, -1, -1, 0, 0, +1, 0, +1, -1, 0 };

void encoder_click(void)
{
    static unsigned char previous = 0;
    uint8_t tmp = 5;

    while(tmp--) { /* debounce */ ; }
 
    /* read CHANA and CHANB */
    tmp = (uint8_t)((ENCCHANB_GetValue() << 1) | ENCCHANA_GetValue());

    previous <<= 2;     /* shift the previous data left two places */ 
    previous |= tmp;    /* OR in the two new bits */

    encoder_count += table[(previous & 0x0f)];  /* Index into table */
  
#ifdef __ROTARY_CONTINUOUS__
  if (encoder_count >= ((ROTARY_MAX + 1) * ROTARY_MULTI)) {
    encoder_count = (ROTARY_MIN * ROTARY_MULTI); 
  }
  else if (encoder_count <= ((ROTARY_MIN - 1) * ROTARY_MULTI)) {
     encoder_count = (ROTARY_MAX * ROTARY_MULTI); 
  }
#else
  if (encoder_count > (ROTARY_MAX * ROTARY_MULTI)) {
    encoder_count = (ROTARY_MAX * ROTARY_MULTI); 
  }
  else if (encoder_count < (ROTARY_MIN * ROTARY_MULTI)) {
     encoder_count = (ROTARY_MIN * ROTARY_MULTI); 
  }
#endif
}
#endif


/*
                         Main application
 */
void main(void)
{
    uint8_t recv_status_reg2;
    uint8_t sr;
    uint8_t last_sr;
    
    uint8_t selected = 0xff;
    uint8_t last_selected = 0xff;
    
    // initialize the device
    SYSTEM_Initialize();

    encoder_count = 0;

#ifdef __ROTARY_ENCODER__
    IOCCF6_SetInterruptHandler(encoder_click);
    IOCCF7_SetInterruptHandler(encoder_click);
    
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
#else
    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();
#endif
    
#if 0
    LED_D5_SetLow();
    LED_D4_SetLow();
    
    LED_D5_SetDigitalOutput();
    
    __delay_ms(500);
    
    LED_D5_SetDigitalInput();
    
     __delay_ms(500);
    
        LED_D4_SetDigitalOutput();
    
    __delay_ms(500);
    
    LED_D4_SetDigitalInput();
#endif

    init();
    
    set_upsample(upsample_rate);
    
    set_dit_mode(INPUT_RX1, DIT_UPSAMPLE);
    
    set_deemphasis(DEEMPH_AUTO);
    
    set_input(INPUT_RX1, DIT_UPSAMPLE);
    
    while (1) {
#if 1
        __delay_ms(20);
        selected = get_chan_sel();
        if (selected == 0xff) {
            continue;
        }
        
        if (selected != last_selected) {
            set_input(selected, DIT_UPSAMPLE);
            last_selected = selected;
        }
#else
        __delay_ms(100);

        sr = get_sample_rate();
        if (last_sr != sr) {
            last_sr = sr;
            
            switch (last_sr) {
                case SAMPLERATE_192KHZ:
                    LED_D5_SetDigitalOutput();
                    LED_D4_SetDigitalOutput();
                    break;
                case SAMPLERATE_96KHZ:
                    LED_D5_SetDigitalInput();
                    LED_D4_SetDigitalOutput();
                    break; 
                case SAMPLERATE_44KHZ:
                    LED_D4_SetDigitalInput();
                    LED_D5_SetDigitalOutput();
                    break;
                default:
                    LED_D5_SetDigitalInput();
                    LED_D4_SetDigitalInput();
                    break;
            }
        }
        
        recv_status_reg2 =  src4392_read(SRC_REG0E);
        
        if (recv_status_reg2 & 0x4) {
            LED_D5_SetDigitalOutput();
        }
#endif
    }
}
/**
 End of File
*/