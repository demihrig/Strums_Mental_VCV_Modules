///////////////////////////////////////////////////
//
//   Wave Folder VCV Module
//
//   Strum 2017
//
///////////////////////////////////////////////////

#include "mental.hpp"

//////////////////////////////////////////////////////
struct MentalFold : Module {
	enum ParamIds {
    THRESH_PARAM,
    GAIN_PARAM,
    THRESH_PARAM2,
    GAIN_PARAM2,
    NUM_PARAMS
	};
	enum InputIds {
		INPUT_1,
    THRESH_CV_INPUT,
    GAIN_CV_INPUT,
    INPUT_2,
    THRESH_CV_INPUT2,
    GAIN_CV_INPUT2,
    NUM_INPUTS
	};
	enum OutputIds {
		OUTPUT_1,
    OUTPUT_2,
    NUM_OUTPUTS
	};

	MentalFold() {
	  config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS);

    configParam(MentalFold::THRESH_PARAM, 0.0, 1.0, 1.0);
    configParam(MentalFold::GAIN_PARAM, 0.0, 1.0, 0.5);

    configParam(MentalFold::THRESH_PARAM2, 0.0, 1.0, 1.0);
    configParam(MentalFold::GAIN_PARAM2, 0.0, 1.0, 0.5);
  }
	void step() override;
};

/////////////////////////////////////////////////////
void MentalFold::step() {

  float signal_in_1 = inputs[INPUT_1].value;
  float signal_in_2 = inputs[INPUT_2].value;
  
  float threshold_fold = params[THRESH_PARAM].value * 6 + inputs[THRESH_CV_INPUT].value;
  float threshold_fold2 = params[THRESH_PARAM2].value * 6 + inputs[THRESH_CV_INPUT2].value;
  
  float gain = params[GAIN_PARAM].value * 5 + inputs[GAIN_CV_INPUT].value / 2;
  float gain2 = params[GAIN_PARAM2].value * 5 + inputs[GAIN_CV_INPUT2].value / 2;

  float modified = signal_in_1;
  float modified2 = signal_in_2;
  
  if (std::abs(signal_in_1) > threshold_fold )
  {
    if (signal_in_1 > 0)
    {
     modified = threshold_fold - (signal_in_1 - threshold_fold );
    } else
    {
     modified = - threshold_fold - (signal_in_1 + threshold_fold );
    }
  }
  
  if (std::abs(signal_in_2) > threshold_fold2 )
  {
    if (signal_in_2 > 0)
    {
     modified2 = threshold_fold2 - (signal_in_2 - threshold_fold2 );
    } else
    {
     modified2 = - threshold_fold2 - (signal_in_2 + threshold_fold2 );
    }
  }

  outputs[OUTPUT_1].value = modified * gain;
  outputs[OUTPUT_2].value = modified2 * gain2;

}

//////////////////////////////////////////////////////////////////
struct MentalFoldWidget : ModuleWidget {
  MentalFoldWidget(MentalFold *module);
};

MentalFoldWidget::MentalFoldWidget(MentalFold *module)
{
  setModule(module);
  setPanel(APP->window->loadSvg(asset::plugin(pluginInstance, "res/MentalFold.svg")));

  //params
  addParam(createParam<SmlKnob>(Vec(6, box.size.y / 2 - 169), module, MentalFold::THRESH_PARAM));
  addParam(createParam<SmlKnob>(Vec(6, box.size.y / 2 - 112), module, MentalFold::GAIN_PARAM));
  addParam(createParam<SmlKnob>(Vec(6, box.size.y - 177), module, MentalFold::THRESH_PARAM2));
  addParam(createParam<SmlKnob>(Vec(6, box.size.y - 120), module, MentalFold::GAIN_PARAM2));

  addInput(createInput<CVInPort>(Vec(3, box.size.y / 2 - 148), module, MentalFold::THRESH_CV_INPUT));
  addInput(createInput<CVInPort>(Vec(3, box.size.y / 2 - 91), module, MentalFold::GAIN_CV_INPUT));
  addInput(createInput<InPort>(Vec(3, box.size.y / 2 - 55), module, MentalFold::INPUT_1));

  addOutput(createOutput<OutPort>(Vec(3, box.size.y / 2 - 28), module, MentalFold::OUTPUT_1));

  addInput(createInput<CVInPort>(Vec(3, box.size.y - 156), module, MentalFold::THRESH_CV_INPUT2));
  // label
  addInput(createInput<CVInPort>(Vec(3, box.size.y - 99), module, MentalFold::GAIN_CV_INPUT2));
  // output  

  addInput(createInput<InPort>(Vec(3, box.size.y - 65), module, MentalFold::INPUT_2));
  addOutput(createOutput<OutPort>(Vec(3, box.size.y - 38), module, MentalFold::OUTPUT_2));

  if(module) {
    // label
    //addInput(createPort<CVInPort>(Vec(3, box.size.y / 2 - 148), PortWidget::INPUT, module, MentalFold::THRESH_CV_INPUT));
    // label
    //addInput(createPort<CVInPort>(Vec(3, box.size.y / 2 - 91), PortWidget::INPUT, module, MentalFold::GAIN_CV_INPUT));
    // output  
    //addInput(createPort<InPort>(Vec(3, box.size.y / 2 - 55), PortWidget::INPUT, module, MentalFold::INPUT_1));
    //addOutput(createPort<OutPort>(Vec(3, box.size.y / 2 - 28), PortWidget::OUTPUT, module, MentalFold::OUTPUT_1));


    // // label
    // addInput(createPort<CVInPort>(Vec(3, box.size.y - 156), PortWidget::INPUT, module, MentalFold::THRESH_CV_INPUT2));
    // // label
    // addInput(createPort<CVInPort>(Vec(3, box.size.y - 99), PortWidget::INPUT, module, MentalFold::GAIN_CV_INPUT2));
    // // output  

    // addInput(createPort<InPort>(Vec(3, box.size.y - 65), PortWidget::INPUT, module, MentalFold::INPUT_2));
    // addOutput(createPort<OutPort>(Vec(3, box.size.y - 38), PortWidget::OUTPUT, module, MentalFold::OUTPUT_2));
  }

}

Model *modelMentalFold = createModel<MentalFold, MentalFoldWidget>("MentalFold");