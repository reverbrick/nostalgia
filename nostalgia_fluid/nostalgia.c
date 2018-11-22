//==================================
//= Playable Electronics Nostalgia =
//= Hybrid Multi-sample Instrument =
//=     v1.0 2018 Daniel Górny     =
//==================================
#include <stdlib.h>
#include <stdio.h>
#include <fluidsynth.h>

int main(){

  fluid_settings_t *settings;
  fluid_synth_t *synth;
  fluid_midi_router_t* router;
  fluid_audio_driver_t *adriver;
  fluid_midi_driver_t* mdriver;
  int sfont_id;
  int i, key;
  int n;

  /* Create the settings. */
  settings = new_fluid_settings();
  fluid_settings_setstr(settings, "audio.driver", "alsa");
  fluid_settings_setstr(settings, "midi.autoconnect", 1);
  fluid_settings_setstr(settings, "midi.driver", "alsa_seq");

  /* Create the synthesizer. */
  synth = new_fluid_synth(settings);

  /* Create the audio driver.  */
  adriver = new_fluid_audio_driver(settings, synth);

  mdriver = new_fluid_midi_driver(settings, fluid_synth_handle_midi_event, synth);

  /* Create the MIDI router and pass events to the synthesizer */
  //router = new_fluid_midi_router (settings, fluid_synth_handle_midi_event, synth);

  /* Load a SoundFont and reset presets */
  sfont_id = fluid_synth_sfload(synth, "sf2/VintageDreamsWaves-v2.sf2", 1);

  fluid_synth_noteon(synth, 0, 60, 80);
  sleep(1);
  fluid_synth_noteoff(synth, 0, 60);

  printf("press <Enter> to stop\n");
  n = getchar();

  /* Clean up */
  delete_fluid_audio_driver(adriver);
  delete_fluid_midi_driver(mdriver);
  //delete_fluid_midi_router(router);
  delete_fluid_synth(synth);
  delete_fluid_settings(settings);
  return 0;

}
