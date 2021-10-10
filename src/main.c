#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "tinyc.h"
#include "softarcade.h"

/* Audio.
 *************************************************************/

#if SOFTARCADE_AUDIO_ENABLE

struct softarcade_synth synth={0};

int16_t tinyc_client_update_synthesizer() {
  return softarcade_synth_update(&synth);
}

static const int16_t *get_wave(uint8_t waveid,void *userdata) {
  return 0;
}

static uint16_t get_pcm(void *pcmpp,uint8_t waveid,void *userdata) {
  return 0;
}

#else
int16_t tinyc_client_update_synthesizer() { return 0; }
#endif

/* Video.
 ***********************************************************************/
 
SOFTARCADE_IMAGE_DECLARE(fb,96,64,0)
SOFTARCADE_IMAGE_DECLARE(bgbits,96,64,0)

static struct softarcade_font font={
  .metrics={
    96,53,105,181,124,181,184,41,85,85,181,181,83,167,47,181,149,117,149,117,149,149,149,149,149,
    149,46,83,117,142,117,153,149,149,149,117,149,149,149,149,149,117,149,149,117,181,181,181,149,
    149,149,149,181,149,181,181,181,181,117,85,181,85,173,175,108,149,149,114,149,149,117,150,149,
    50,89,117,85,175,143,146,150,150,146,149,117,143,175,175,111,150,114,117,53,117,174,0
  },
  .bits={
    0,3892314112,3019898880,1473639680,1584648192,2290649216,1158764852,3221225472,1782579200,
    2508193792,2881415808,557728256,218103808,4160749568,536870912,143165440,1805475840,3375235072,
    3781750784,3306946560,2582712320,4175552512,1760124928,4045684736,1768513536,1769017344,
    2684354560,1291845632,706871296,4042260480,2292711424,3781428224,1773694976,1777963008,
    3924418560,1917190144,3919175680,4176015360,4175986688,1756983296,2583269376,3912105984,
    286875648,2596966400,2454585344,2397771904,2389391488,1952651008,3924328448,1771794432,
    3924398080,2019680256,4178067968,2576965632,2354356736,2355844352,2324211840,2354856448,
    3847094272,3938451456,2181570688,3586129920,581042176,4063232,2290089984,1635348480,
    2297028608,1915748352,293171200,1776836608,732168192,1769037824,2297008128,2952790016,
    1163919360,2464808960,2856321024,3580493824,3918528512,1771438080,1776844800,1769017344,
    3918004224,2019680256,1268908032,2574254080,2324168704,2371092480,2860515328,2574344192,
    4017094656,1780875264,4160749568,3366715392,1162084352,0
  },
};


/* Game logic.
 **************************************************************/
 
//TODO

/* Main loop.
 ******************************************************************/

static double next_time=0.0;
static uint8_t noteid=0x40;
static uint8_t voiceid=0;
static uint8_t waveid=0;
static uint16_t songp=0;

void loop() {

  unsigned long now=millis();//TODO seems there is also "micros()"
  if (now<next_time) {
    delay(1);
    return;
  }
  next_time+=16.66666;
  if (next_time<now) {
    tinyc_usb_log("dropped frame\n");
    next_time=now+16.66666;
  }

  uint8_t input_state=tinyc_read_input();
  //TODO update game state

  memcpy(image_fb.v,image_bgbits.v,96*64);
  //TODO render sprites

  tinyc_send_framebuffer(image_fb.v);
}

/* Initialize.
 */

void setup() {

  #if SOFTARCADE_AUDIO_ENABLE
  softarcade_synth_init(&synth,22050,get_wave,get_pcm,0);
  #endif

  tinyc_init();

  tinyc_init_usb_log();
}
