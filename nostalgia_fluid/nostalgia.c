//==================================
//= Playable Electronics Nostalgia =
//= Hybrid Multi-sample Instrument =
//=     v1.0 2018 Daniel Górny     =
//==================================
#include <stdlib.h>
#include <stdio.h>
#include <fluidsynth.h>

int main(int argc, char *argv[]){

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
  fluid_settings_setstr(settings, "audio.driver",                 "alsa");
  fluid_settings_setint(settings, "audio.periods",                2);
  fluid_settings_setint(settings, "audio.period-size",            128);
  fluid_settings_setint(settings, "audio.realtime-prio",          99);
  fluid_settings_setint(settings, "midi.autoconnect",             1);
  //autoconnect
  //fluid_settings_setstr(settings, "midi.driver",                  "alsa_raw");
  //fluid_settings_setstr(settings, "midi.alsa.device",             "hw:1,0,0");
  //manual
  fluid_settings_setstr(settings, "midi.driver",                  "alsa_seq");
  fluid_settings_setint(settings, "midi.realtime-prio",           50);
  fluid_settings_setint(settings, "synth.polyphony",              16);
  fluid_settings_setint(settings, "synth.reverb.active",          0);
  fluid_settings_setint(settings, "synth.chorus.active",          0);
  fluid_settings_setint(settings, "synth.cpu-cores",              4);
  fluid_settings_setint(settings, "synth.threadsafe-api",         1);
  fluid_settings_setint(settings, "synth.dynamic-sample-loading", 0);
  fluid_settings_setint(settings, "synth.gain",                   1);

  /* Create the synthesizer. */
  synth = new_fluid_synth(settings);

  /* Create the audio driver.  */
  adriver = new_fluid_audio_driver(settings, synth);

  mdriver = new_fluid_midi_driver(settings, fluid_synth_handle_midi_event, synth);

  /* Create the MIDI router and pass events to the synthesizer */
  //router = new_fluid_midi_router(settings, fluid_synth_handle_midi_event, synth);

  /* Load a SoundFont and reset presets */
  sfont_id = fluid_synth_sfload(synth, argv[1], 1);

  fluid_synth_noteon(synth, 0, 60, 80);
  sleep(1);
  fluid_synth_noteoff(synth, 0, 60);
  //sleep(1);

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
