///////////////////////////////////////////////////
//
//   Pitch Shifter VCV Module
//
//   Strum 2017
//
///////////////////////////////////////////////////

#include "mental.hpp"

//////////////////////////////////////////////////////
struct MentalPitchShift : Module {
	enum ParamIds {
    OCTAVE_SHIFT_1,
    OCTAVE_SHIFT_2,
    SEMITONE_SHIFT_1,
    SEMITONE_SHIFT_2,    
    NUM_PARAMS
	};
	enum InputIds {
		OCTAVE_SHIFT_1_INPUT,
    OCTAVE_SHIFT_2_INPUT,
    SEMITONE_SHIFT_1_INPUT,
    SEMITONE_SHIFT_2_INPUT, 
    OCTAVE_SHIFT_1_CVINPUT,
    OCTAVE_SHIFT_2_CVINPUT,
    SEMITONE_SHIFT_1_CVINPUT,
    SEMITONE_SHIFT_2_CVINPUT, 
    NUM_INPUTS
	};
	enum OutputIds {
		OCTAVE_SHIFT_1_OUTPUT,
    OCTAVE_SHIFT_2_OUTPUT,
    SEMITONE_SHIFT_1_OUTPUT,
    SEMITONE_SHIFT_2_OUTPUT, 
    NUM_OUTPUTS
	};

	MentalPitchShift() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);}
  
  float octave_1_out = 0.0;
  float octave_2_out = 0.0;
  float semitone_1_out = 0.0;
  float semitone_2_out = 0.0;  
  
	void step() override;
};

/////////////////////////////////////////////////////
void MentalPitchShift::step() {

  octave_1_out = inputs[OCTAVE_SHIFT_1_INPUT].value + round(params[OCTAVE_SHIFT_1].value) + round(inputs[OCTAVE_SHIFT_1_CVINPUT].value/2);
  octave_2_out = inputs[OCTAVE_SHIFT_2_INPUT].value + round(params[OCTAVE_SHIFT_2].value) + round(inputs[OCTAVE_SHIFT_1_CVINPUT].value/2);
  semitone_1_out = inputs[SEMITONE_SHIFT_1_INPUT].value + round(params[SEMITONE_SHIFT_1].value)*(1.0/12.0) + round(inputs[SEMITONE_SHIFT_1_CVINPUT].value/2)*(1.0/12.0);
  semitone_2_out = inputs[SEMITONE_SHIFT_2_INPUT].value + round(params[SEMITONE_SHIFT_2].value)*(1.0/12.0) + round(inputs[SEMITONE_SHIFT_2_CVINPUT].value/2)*(1.0/12.0);
    
  outputs[OCTAVE_SHIFT_1_OUTPUT].value = octave_1_out;
  outputs[OCTAVE_SHIFT_2_OUTPUT].value = octave_2_out;
  outputs[SEMITONE_SHIFT_1_OUTPUT].value = semitone_1_out;
  outputs[SEMITONE_SHIFT_2_OUTPUT].value = semitone_2_out;

}

//////////////////////////////////////////////////////////////////
struct MentalPitchShiftWidget : ModuleWidget {
  MentalPitchShiftWidget(MentalPitchShift *module);
};

MentalPitchShiftWidget::MentalPitchShiftWidget(MentalPitchShift *module) : ModuleWidget(module)
{
  

  setPanel(SVG::load(assetPlugin(pluginInstance, "res/MentalPitchShift.svg")));
  //TODO make this better somehow
  if(module == nullptr) {
    return;
  }
  addParam(createParam<MedKnob>(Vec(2, 20), module, MentalPitchShift::OCTAVE_SHIFT_1, -4.5, 4.5, 0.0));
  addParam(createParam<MedKnob>(Vec(2, 80), module, MentalPitchShift::OCTAVE_SHIFT_2, -4.5, 4.5, 0.0));
  addParam(createParam<MedKnob>(Vec(2, 140), module, MentalPitchShift::SEMITONE_SHIFT_1, -6.5, 6.5, 0.0));
  addParam(createParam<MedKnob>(Vec(2, 200), module, MentalPitchShift::SEMITONE_SHIFT_2, -6.5, 6.5, 0.0));

  addInput(createPort<CVInPort>(Vec(3, 50), PortWidget::INPUT, module, MentalPitchShift::OCTAVE_SHIFT_1_INPUT));
	addInput(createPort<CVInPort>(Vec(3, 110), PortWidget::INPUT, module, MentalPitchShift::OCTAVE_SHIFT_2_INPUT));
  addInput(createPort<CVInPort>(Vec(3, 170), PortWidget::INPUT, module, MentalPitchShift::SEMITONE_SHIFT_1_INPUT));
	addInput(createPort<CVInPort>(Vec(3, 230), PortWidget::INPUT, module, MentalPitchShift::SEMITONE_SHIFT_2_INPUT));
  
  addInput(createPort<CVInPort>(Vec(33, 20), PortWidget::INPUT, module, MentalPitchShift::OCTAVE_SHIFT_1_CVINPUT));
	addInput(createPort<CVInPort>(Vec(33, 80), PortWidget::INPUT, module, MentalPitchShift::OCTAVE_SHIFT_2_CVINPUT));
  addInput(createPort<CVInPort>(Vec(33, 140), PortWidget::INPUT, module, MentalPitchShift::SEMITONE_SHIFT_1_CVINPUT));
	addInput(createPort<CVInPort>(Vec(33, 200), PortWidget::INPUT, module, MentalPitchShift::SEMITONE_SHIFT_2_CVINPUT));

  addOutput(createPort<CVOutPort>(Vec(33, 50), PortWidget::OUTPUT, module, MentalPitchShift::OCTAVE_SHIFT_1_OUTPUT));
  addOutput(createPort<CVOutPort>(Vec(33, 110), PortWidget::OUTPUT, module, MentalPitchShift::OCTAVE_SHIFT_2_OUTPUT));
  addOutput(createPort<CVOutPort>(Vec(33, 170), PortWidget::OUTPUT, module, MentalPitchShift::SEMITONE_SHIFT_1_OUTPUT));
  addOutput(createPort<CVOutPort>(Vec(33, 230), PortWidget::OUTPUT, module, MentalPitchShift::SEMITONE_SHIFT_2_OUTPUT));

}

Model *modelMentalPitchShift = createModel<MentalPitchShift, MentalPitchShiftWidget>("MentalPitchShift");