# Strum's Mental VCV Module Suite (fix)
strum@softhome.net

Simple but useful modules for VCVRack

Version : 1.0.0

Date : 27th April 2018

Based largely on the fundamental modules but I have also used some code from other module
developers and learned various ways of doing things from the other suites of modules as well.

The modules are mostly utilities, which you can never have enough of, and I have
focused on keeping them small to pack a lot of functionality into as little possible screen area.

Jack sockets are now colour coded, hopefully this should make using them more intitutive. 

## Notes

This is a port of Strums mental modules to the vcv version 1.0, based on [this wiki](https://vcvrack.com/manual/Migrate1.html#)
Anything not labeled *working/stable* is assumed to be broken

## Module List

**Chord** - 
  Inspired by Q-Bit chord Eurorack module, takes input pitch and builds a chord
  from it based on various parameters and logic inputs.

**Gates** - 
  Manual or remotely controllable gates

**Logic** - 
  Various logic gates

**Mults** - 
  Simple 2*5 Multiples

**Muxes** - 
  2 * 2 into 1 muxes and 1 4 into 1 mux

**Quantiser** - 
  Takes inputs pitchs and quantises to scale selected by buttons for each pitch
  Also functions as a pitch reference

**SubMixer** - 
  4 Channel stereo mixer with pan based on fundametal VCMixer

**A/B Switches** - 
  A/B switches

**Buttons** - 
  Buttons for controlling other modules manually
  7 On/off switches in the top section and 7 momentary buttons in the lower.
  
**Mixer** - 
  12 Channel Mixer with 2 auxiliary sends and returns and channel mutes.

**Clipper** - *working, not fully stable*
  Simple Clipping distortion

**Wave Folder** - *stable* - 
  Simple Waver folder
  
**Pitch Shifter** - 
  Shift pitches by octaves or semitones

**Sums** - 
  2 * 5 into 1 summing mixers, useful for adding cvs for pitch and modulation   

**Clock Divider** - 
  Based on autodafe's clock divider but I've simplified the code, made the gui
  smaller and added extra divisions 3,5,7 and 12
  
**Cartesian Sequencer** - 
  Cartesian sequencer similar to make noise rene.
  
**Patch Matrix** - 
  10 by 10 Patch matrix
  
**Binary decoder** - 
  3 bit binary decoder true at one of 8 outputs dependent on logic state of the 3 inputs
  
**8 way switch** - *working, has lag* -
 based on binary decoder, switches a signal to one of 8 outputs based on 3 bit selector inputs

**8 to 1 Mux** - *stable* -
   The reverse of the 8 way switch, 8 inputs 1 out selected with 3 logic inputs

**Dual Counters** - for euclidean rhythms

**Knobs** - Outputs constants continous or stepped by integer ro semitone, uni or bipolar

**Gate Maker** - Counter with delay before opening and after closing, cycle or one shot mode - BETA

**Patch notes** - add notes to a patch

**Master Clock** - Set a Tempo by BPM and time signature, outputs beat, bar and subdivisions of the beat

**Quad LFO** - 4 LFOs with cv control and 4 synced modes in a small panel 

## Extended Notes

### Why is this a thing?

I periodically use rack and its accompanying bridge VST in some of my music projects and unfortunately many of my presets broke as they depend on the Clipper and Wave folder from this plugin. In my stubborn nature (and because rack 0.6.2c is comparatively unstable) I've decided to pick up where the developer left off.

### Objectives

- [ ] All plugins at least work
- [ ] All plugins are stable
- [ ] Full port to the rack 1.x API
- [ ] Merge back into master
