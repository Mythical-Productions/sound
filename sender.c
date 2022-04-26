#include <alsa/asoundlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

snd_seq_t *open_seq();

snd_seq_t *open_seq() {

  snd_seq_t *seq_handle;
  int portid;

  if (snd_seq_open(&seq_handle, "hw", SND_SEQ_OPEN_DUPLEX, 0) < 0) {
    fprintf(stderr, "Error opening ALSA sequencer.\n");
    exit(1);
  }
  snd_seq_set_client_name(seq_handle, "ALSA Sender");
  if ((portid = snd_seq_create_simple_port(
           seq_handle, "ALSA Sequencer Demo",
           SND_SEQ_PORT_CAP_WRITE | SND_SEQ_PORT_CAP_SUBS_WRITE,
           SND_SEQ_PORT_TYPE_APPLICATION)) < 0) {
    fprintf(stderr, "Error creating sequencer port.\n");
    exit(1);
  }
  return (seq_handle);
}

void midi_action(snd_seq_t *seq_handle, int *oportid) {

  snd_seq_event_t *ev;

  do {
    snd_seq_event_input(seq_handle, &ev);
    switch (ev->type) {

    case SND_SEQ_EVENT_CONTROLLER:
      fprintf(stderr, "Control event on Channel %2d, param %d: %5d       \n",
              ev->data.control.channel, ev->data.control.param,
              ev->data.control.value);

      ev->data.control.param = (ev->data.control.param % 8) + 1;
      snd_seq_ev_set_source(ev, oportid[ev->data.control.channel]);
      snd_seq_ev_set_subs(ev);
      snd_seq_ev_set_direct(ev);
      snd_seq_event_output_direct(seq_handle, ev);

      break;
    case SND_SEQ_EVENT_PITCHBEND:
      fprintf(stderr, "Pitchbender event on Channel %2d: %5d   \n",
              ev->data.control.channel, ev->data.control.value);
      break;
    case SND_SEQ_EVENT_NOTEON:
      fprintf(stderr, "Note On event on Channel %2d: %5d, vel %d\n",
              ev->data.control.channel, ev->data.note.note,
              ev->data.note.velocity);
      break;
    case SND_SEQ_EVENT_NOTEOFF:
      fprintf(stderr, "Note Off event on Channel %2d: %5d      \n",
              ev->data.control.channel, ev->data.note.note);
      break;
    default:
      fprintf(stderr, "Unknown type %d\r", ev->type);
    }
    snd_seq_free_event(ev);
  } while (snd_seq_event_input_pending(seq_handle, 0) > 0);
}


int main(int argc, char *argv[]) {

  snd_seq_t *seq_handle;

  int oportid[16]; /* output ports */
  char txt[20];

  seq_handle = open_seq();

  /* open 16 output ports for the MIDI channels */
  for (int i = 0; i < 1; i++) {
    sprintf(txt, "MIDI Output %d", i);
    if ((oportid[i] = snd_seq_create_simple_port(
             seq_handle, txt,
             SND_SEQ_PORT_CAP_READ | SND_SEQ_PORT_CAP_SUBS_READ,
             SND_SEQ_PORT_TYPE_APPLICATION)) < 0) {
      fprintf(stderr, "fatal error: could not open output port.\n");
      return 1;
    }
  }

  int note = 0;
  int velocity = 0;
  int control_base = 0;
  int control_val = 0;

  while(1) {
    snd_seq_event_t ev;
    snd_seq_ev_clear(&ev);
    snd_seq_ev_set_source(&ev, oportid[0]);
    snd_seq_ev_set_subs(&ev);
    snd_seq_ev_set_direct(&ev);
    snd_seq_ev_set_noteon(&ev, 0, note, velocity);

    printf("Sending NOTE_ON to channel %d, note %d, velocity %d\n",
           ev.data.note.channel,
           ev.data.note.note,
           ev.data.note.velocity);
    snd_seq_event_output_direct(seq_handle, &ev);


    snd_seq_ev_clear(&ev);
    snd_seq_ev_set_source(&ev, oportid[0]);
    snd_seq_ev_set_subs(&ev);
    snd_seq_ev_set_direct(&ev);

    snd_seq_ev_set_controller(&ev, 0, control_base + 9, control_val);
    printf("Sending CC to channel %d, cc %d, val %d\n",
           ev.data.control.channel,
           ev.data.control.param,
           ev.data.control.value);
    snd_seq_event_output_direct(seq_handle, &ev);

    note = (note + 1) % 16;
    if (note == 0) {
      velocity = (velocity + 1) % 3;
    }
    control_base = ((control_base + 1) % 8);
    if (control_base == 0) {
      control_val = (control_val + 1) % 29;
    }

    if (note % 3 == 0 || control_base % 3 == 0) {
      sleep(1);
    }
  }

  return 0;
}
