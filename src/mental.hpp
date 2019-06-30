#include "rack0.hpp"

using namespace rack;

extern Plugin *pluginInstance;

////////////////////
// module widgets
////////////////////

/// 06 versions

extern Model *modelMentalMults;
extern Model *modelMentalSubMixer;
extern Model *modelMentalMixer;
extern Model *modelMentalFold;
extern Model *modelMentalClip;
extern Model *modelMentalGates;
extern Model *modelMentalABSwitches;
extern Model *modelMentalQuantiser;
extern Model *modelMentalChord;
extern Model *modelMentalMuxes;
extern Model *modelMentalLogic;
extern Model *modelMentalButtons;
extern Model *modelMentalSums;
extern Model *modelMentalPitchShift;
extern Model *modelMentalClockDivider;
extern Model *modelMentalCartesian;
extern Model *modelMentalPatchMatrix;
extern Model *modelMentalBinaryDecoder;
extern Model *modelMentalSwitch8;
extern Model *modelMentalMux8;
extern Model *modelMentalCounters;
extern Model *modelMentalKnobs;
extern Model *modelMentalGateMaker;
extern Model *modelMentalMasterClock;
extern Model *modelMentalQuadLFO;
extern Model *modelMentalRadioButtons;


/////////////////////////////////////////////
// ports

#define SVG_LOAD(thing) APP->window->loadSvg(thing)

struct OutPort : SVGPort {
	OutPort() {
		sw->svg = SVG_LOAD(asset::plugin(pluginInstance, "res/components/OutPort.svg"));
		sw->wrap();
		box.size = sw->box.size;
	}
};

struct InPort : SVGPort {
	InPort() {
		sw->svg = SVG_LOAD(asset::plugin(pluginInstance, "res/components/InPort.svg"));
		sw->wrap();
		box.size = sw->box.size;
	}
};

struct CVInPort : SVGPort {
	CVInPort() {
		sw->svg = SVG_LOAD(asset::plugin(pluginInstance, "res/components/CVInPort.svg"));
		sw->wrap();
		box.size = sw->box.size;
	}
};

struct CVOutPort : SVGPort {
	CVOutPort() {
		sw->svg = SVG_LOAD(asset::plugin(pluginInstance, "res/components/CVOutPort.svg"));
		sw->wrap();
		box.size = sw->box.size;
	}
};

struct GateInPort : SVGPort {
	GateInPort() {
		sw->svg = SVG_LOAD(asset::plugin(pluginInstance, "res/components/GateInPort.svg"));
		sw->wrap();
		box.size = sw->box.size;
	}
};

struct GateOutPort : SVGPort {
	GateOutPort() {
		sw->svg = SVG_LOAD(asset::plugin(pluginInstance, "res/components/GateOutPort.svg"));
		sw->wrap();
		box.size = sw->box.size;
	}
};

// Knobs

struct LrgKnob : RoundKnob {
	LrgKnob() {
		setSVG(SVG_LOAD(asset::plugin(pluginInstance, "res/components/LrgKnob.svg")));
		box.size = Vec(42,42);

	}
};

struct MedKnob : RoundKnob {
	MedKnob() {
		setSVG(SVG_LOAD(asset::plugin(pluginInstance, "res/components/MedKnob.svg")));
		box.size = Vec(24,24);

	}
};

struct SmlKnob : RoundKnob {
	SmlKnob() {
		setSVG(SVG_LOAD(asset::plugin(pluginInstance, "res/components/SmlKnob.svg")));
		box.size = Vec(20,20);
	}
};

// switches

struct ThreeWaySwitch : SvgSwitch /*ToggleSwitch*/ {
	ThreeWaySwitch() {
		addFrame(SVG_LOAD(asset::plugin(pluginInstance,"res/components/Three_2.svg")));
		addFrame(SVG_LOAD(asset::plugin(pluginInstance,"res/components/Three_1.svg")));
		addFrame(SVG_LOAD(asset::plugin(pluginInstance,"res/components/Three_0.svg")));
	}
};

// lights

/// lights

struct MentalLight : GrayModuleLightWidget{
	MentalLight() { bgColor = nvgRGB(0x40, 0x40, 0x40); }
};
struct RedLED : MentalLight {
 	RedLED() {
 		addBaseColor(nvgRGB(0xff, 0x00, 0x00)); }
};

struct BlueLED : MentalLight {
 	BlueLED() {
 		addBaseColor(nvgRGB(0x00, 0x47, 0x7e)); }
};

struct OrangeLED : MentalLight {
 	OrangeLED() {
 		addBaseColor(COLOR_ORANGE); }
};

template <typename BASE>
 struct TinyLight : BASE {
 	TinyLight() {
 		this->box.size = Vec(4, 4);
 	}
 };

template <typename BASE>
 struct SmlLight : BASE {
 	SmlLight() {
 		this->box.size = Vec(8, 8);
 	}
 };

template <typename BASE>
 struct MedLight : BASE {
 	MedLight() {
 		this->box.size = Vec(10, 10);
 	}
 };
