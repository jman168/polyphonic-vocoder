#include <iostream>
#include <unistd.h>
#include <cstring>

#include <jack/jack.h>

jack_port_t *input_port;
jack_port_t *output_port;
jack_port_t *midi_port;
jack_client_t *client;

jack_nframes_t sample_rate;
jack_nframes_t buffer_size;

int process(jack_nframes_t nframes, void *arg);
void jack_shutdown (void *arg);

int main() {
    jack_status_t status;
    
    const char *client_name = "polyphonic_vocoder";
    client = jack_client_open(client_name, JackNullOption, &status, NULL);
    if (client == NULL) {
		fprintf (stderr, "jack_client_open() failed, "
			 "status = 0x%2.0x\n", status);
		if (status & JackServerFailed) {
			fprintf (stderr, "Unable to connect to JACK server\n");
		}
		exit (1);
	}
    if (status & JackServerStarted) {
		fprintf (stderr, "JACK server started\n");
	}
	if (status & JackNameNotUnique) {
		client_name = jack_get_client_name(client);
		fprintf (stderr, "unique name `%s' assigned\n", client_name);
	}

    jack_set_process_callback (client, process, 0);

	jack_on_shutdown (client, jack_shutdown, 0);

    sample_rate = jack_get_sample_rate (client);
    buffer_size = jack_get_buffer_size (client);

    printf("Sample rate: %" PRIu32 " Buffer size: %" PRIu32 "\n", sample_rate, buffer_size);

    input_port = jack_port_register (client, "input",
					 JACK_DEFAULT_AUDIO_TYPE,
					 JackPortIsInput, 0);
	output_port = jack_port_register (client, "output",
					  JACK_DEFAULT_AUDIO_TYPE,
					  JackPortIsOutput, 0);
    midi_port = jack_port_register (client, "midi",
					  JACK_DEFAULT_MIDI_TYPE,
					  JackPortIsInput, 0);

    if ((input_port == NULL) || (output_port == NULL) || (midi_port == NULL)) {
		fprintf (stderr, "no more JACK ports available\n");
		exit (1);
	}

    if (jack_activate (client)) {
		fprintf (stderr, "cannot activate client");
		exit (1);
	}

    sleep (-1);

	jack_client_close (client);
	exit (0);
}

int process (jack_nframes_t nframes, void *arg)
{
	jack_default_audio_sample_t *in, *out;
	
	in = (jack_default_audio_sample_t *)jack_port_get_buffer (input_port, nframes);
	out = (jack_default_audio_sample_t *)jack_port_get_buffer (output_port, nframes);
	memcpy (out, in, sizeof (jack_default_audio_sample_t) * nframes);

	return 0;      
}

// Shutdown the program when jack exits
void jack_shutdown (void *arg)
{
	exit (1);
}