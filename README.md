# Polyphonic Vocoder

This vocoder is a (relatively) special type of vocoder. Usually when using a vocoder and forming a chord you combine the oscillators into one carrier signal and then modulate it with the modulator. This application does it a little differently; it takes every oscillator, modulates it with the modulator, and *then* it combines all the vocoder signals into one. It *is* a lot less computationally efficient, but it reduces aliasing errors and artifacting in the final output.

## Implementation

This program is written in C++ and uses [jack](https://jackaudio.org/) as its audio backend. It runs as a standalone application you feed audio and midi data into. This is because it is the easiest to create and provides a great deal of flexibility. 

This project uses CMake as a build system so the standard
```
cmake . 
make 
make install
```
should work just fine.