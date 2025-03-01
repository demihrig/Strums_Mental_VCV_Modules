///////////////////////////////////////////////////
//
//   A/B Switches VCV Module
//
//   Strum 2017
//
///////////////////////////////////////////////////

#include "mental.hpp"

//#include "dsp/digital.hpp"

/////////////////////////////////////////////////
struct MentalABSwitches : Module {
	enum ParamIds {
      BUTTON_PARAM,
      NUM_PARAMS = BUTTON_PARAM + 4
	};

	enum InputIds {
      INPUT,
      SEL_INPUT = INPUT + 4,
      NUM_INPUTS = SEL_INPUT + 4
	};
	enum OutputIds {
      OUTPUT_A,
      OUTPUT_B = OUTPUT_A + 4,
      NUM_OUTPUTS = OUTPUT_B + 4
	};
  enum LightIds {
		BUTTON_LIGHTS,
    A_LEDS = BUTTON_LIGHTS + 4,
    B_LEDS = A_LEDS + 4,
		NUM_LIGHTS = B_LEDS + 4
	};

  SchmittTrigger button_triggers[4];
  bool button_on[4] = {0,0,0,0};
      
	MentalABSwitches() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);}
	void step() override;
  
  json_t *dataToJson() override
  {
		json_t *rootJ = json_object();
    
    // button states
		json_t *button_statesJ = json_array();
		for (int i = 0; i < 4; i++)
    {
			json_t *button_stateJ = json_integer((int) button_on[i]);
			json_array_append_new(button_statesJ, button_stateJ);
		}
		json_object_set_new(rootJ, "buttons", button_statesJ);    
    return rootJ;
  }
  
  void dataFromJson(json_t *rootJ) override
  {
    // button states
		json_t *button_statesJ = json_object_get(rootJ, "buttons");
		if (button_statesJ)
    {
			for (int i = 0; i < 4; i++)
      {
				json_t *button_stateJ = json_array_get(button_statesJ, i);
				if (button_stateJ)
					button_on[i] = !!json_integer_value(button_stateJ);
			}
		}  
  }
};

/////////////////////////////////////////////////////
void MentalABSwitches::step() {

  for (int i = 0 ; i < 4 ; i++)
  {
    float signal = inputs[INPUT + i].value;
    float sel = inputs[SEL_INPUT + i].value;
  
    if (button_triggers[i].process(params[BUTTON_PARAM + i].value))
    {
	    button_on[i] = !button_on[i];
    }
    if (button_on[i] || ( sel > 0.0))
    {
      outputs[OUTPUT_A + i].value = 0.0;
      outputs[OUTPUT_B + i].value = signal;
      
      lights[B_LEDS + i].value = 1.0;
      lights[A_LEDS + i].value = 0.0;
    }
    else
    {
      outputs[OUTPUT_A + i].value = signal;
      outputs[OUTPUT_B + i].value = 0.0;
      
      lights[B_LEDS + i].value = 0.0;
      lights[A_LEDS + i].value = 1.0;
    }
  }
}

//////////////////////////////////////////////////////////////////
struct MentalABSwitchesWidget : ModuleWidget {
  MentalABSwitchesWidget(MentalABSwitches *module);
};

MentalABSwitchesWidget::MentalABSwitchesWidget(MentalABSwitches *module) : ModuleWidget(module)
{


  setPanel(SVG::load(assetPlugin(pluginInstance, "res/MentalABSwitches.svg")));
  //TODO make this better some how
  if(module == nullptr) {
    return;
  }
  int group_spacing = 85;
  
  for (int i = 0 ; i < 4 ; i++)
  {
	  addInput(createPort<InPort>(Vec(3, group_spacing * i + 25), PortWidget::INPUT, module, MentalABSwitches::INPUT + i));
    addInput(createPort<GateInPort>(Vec(3, group_spacing * i + 75), PortWidget::INPUT, module, MentalABSwitches::SEL_INPUT + i));
  
    addOutput(createPort<OutPort>(Vec(33, group_spacing * i + 25), PortWidget::OUTPUT, module, MentalABSwitches::OUTPUT_A + i));
    addOutput(createPort<OutPort>(Vec(33, group_spacing * i + 50), PortWidget::OUTPUT, module, MentalABSwitches::OUTPUT_B + i));

    addChild(createLight<MedLight<BlueLED>>(Vec(62, group_spacing * i + 34), module, MentalABSwitches::A_LEDS + i ));
    addChild(createLight<MedLight<BlueLED>>(Vec(62, group_spacing * i + 59), module, MentalABSwitches::B_LEDS + i));
  
    addParam(createParam<LEDButton>(Vec(6, group_spacing * i + 54), module, MentalABSwitches::BUTTON_PARAM + i, 0.0, 1.0, 0.0));
	  addChild(createLight<MedLight<BlueLED>>(Vec(6+5, group_spacing * i + 54+5), module, MentalABSwitches::BUTTON_LIGHTS + i));
  }
}

//Model *modelMentalABSwitches = createModel<MentalABSwitches, MentalABSwitchesWidget>("mental", "MentalABSwitches", "A/B Switches", SWITCH_TAG, UTILITY_TAG);
Model *modelMentalABSwitches = createModel<MentalABSwitches, MentalABSwitchesWidget>("MentalABSwitches");