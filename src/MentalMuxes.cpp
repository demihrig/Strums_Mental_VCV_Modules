///////////////////////////////////////////////////
//
//   Multiplexers VCV Module
//
//   Strum 2017
//
///////////////////////////////////////////////////

#include "mental.hpp"

struct MentalMuxes : Module {
	enum ParamIds {
		NUM_PARAMS
	};  
	enum InputIds {		
		INPUT_1A,
    INPUT_2A,
    SELECT_A,
    INPUT_1B,
    INPUT_2B,
    SELECT_B, 
    INPUT_1C,
    INPUT_2C,
    INPUT_3C,
    INPUT_4C,
    SELECT_C,     
		NUM_INPUTS
	};
	enum OutputIds {
		OUTPUT_A,
    OUTPUT_B,
    OUTPUT_C,        
		NUM_OUTPUTS
	};
  enum LightIds {
    LEVEL_LED_A1,
    LEVEL_LED_A2,
    LEVEL_LED_B1,
    LEVEL_LED_B2,
    LEVEL_LED_C1,
    LEVEL_LED_C2,
    LEVEL_LED_C3,
    LEVEL_LED_C4,    
    NUM_LIGHTS
  };
  
	MentalMuxes() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);}
	void step() override;
};

void MentalMuxes::step()
{
  
  float signal_in_a1 = inputs[INPUT_1A].value;
  float signal_in_a2 = inputs[INPUT_2A].value;
  float select_a = inputs[SELECT_A].value;
  
  if (select_a > 0.0 )
  {
    outputs[OUTPUT_A].value = signal_in_a2;    
    lights[LEVEL_LED_A2].value = std::abs((signal_in_a2 / 3));
    lights[LEVEL_LED_A1].value = 0.0;
  }
  else
  {
    outputs[OUTPUT_A].value = signal_in_a1;    
    lights[LEVEL_LED_A1].value = std::abs((signal_in_a1 / 3));
    lights[LEVEL_LED_A2].value = 0.0;
  }
  float signal_in_b1 = inputs[INPUT_1B].value;
  float signal_in_b2 = inputs[INPUT_2B].value;
  float select_b = inputs[SELECT_B].value;
  
  if (select_b > 0.0 )
  {
    outputs[OUTPUT_B].value = signal_in_b2;    
    lights[LEVEL_LED_B2].value = std::abs((signal_in_b2 / 3));
    lights[LEVEL_LED_B1].value = 0.0;
  }
  else
  {
    outputs[OUTPUT_B].value = signal_in_b1;    
    lights[LEVEL_LED_B1].value = std::abs((signal_in_b1 / 3));
    lights[LEVEL_LED_B2].value = 0.0;
  }
  
  float signal_in_c1 = inputs[INPUT_1C].value;
  float signal_in_c2 = inputs[INPUT_2C].value;
  float signal_in_c3 = inputs[INPUT_3C].value;
  float signal_in_c4 = inputs[INPUT_4C].value;
  float select_c = inputs[SELECT_C].value;
  int selector = round(std::abs(select_c));
  if (selector > 3) selector = 3;
    
  if (selector == 0 )
  {
    outputs[OUTPUT_C].value = signal_in_c1;    
    lights[LEVEL_LED_C1].value = std::abs((signal_in_c1 / 3));
    lights[LEVEL_LED_C2].value = 0.0;
    lights[LEVEL_LED_C3].value = 0.0;
    lights[LEVEL_LED_C4].value = 0.0;
       
  }
  if (selector == 1 )
  {
    outputs[OUTPUT_C].value = signal_in_c2;    
    lights[LEVEL_LED_C2].value = std::abs((signal_in_c2 / 3));
    lights[LEVEL_LED_C1].value = 0.0;
    lights[LEVEL_LED_C3].value = 0.0;
    lights[LEVEL_LED_C4].value = 0.0;
  }
  if (selector == 2 )
  {
    outputs[OUTPUT_C].value = signal_in_c3;    
    lights[LEVEL_LED_C3].value = std::abs((signal_in_c3 / 3));
    lights[LEVEL_LED_C2].value = 0.0;
    lights[LEVEL_LED_C2].value = 0.0;
    lights[LEVEL_LED_C4].value = 0.0;    
  }
  if (selector == 3 )
  {
    outputs[OUTPUT_C].value = signal_in_c4;    
    lights[LEVEL_LED_C4].value = std::abs((signal_in_c4 / 3));
    lights[LEVEL_LED_C1].value = 0.0;
    lights[LEVEL_LED_C2].value = 0.0;
    lights[LEVEL_LED_C3].value = 0.0;
  }
}

///////////////////////////////////////////////////////////////////////////////////////////////
struct MentalMuxesWidget : ModuleWidget {
  MentalMuxesWidget(MentalMuxes *module);
};

MentalMuxesWidget::MentalMuxesWidget(MentalMuxes *module) : ModuleWidget(module)
{
  //TODO make this better somehow

  setPanel(SVG::load(assetPlugin(pluginInstance, "res/MentalMuxes.svg")));
  if(module == nullptr) {
    return;
  }
	int group_offset = 90;
  addInput(createPort<GateInPort>(Vec(3, 75), PortWidget::INPUT, module, MentalMuxes::SELECT_A));  
	addInput(createPort<InPort>(Vec(3, 25), PortWidget::INPUT, module, MentalMuxes::INPUT_1A));
  addInput(createPort<InPort>(Vec(3, 50), PortWidget::INPUT, module, MentalMuxes::INPUT_2A));  
  
  addOutput(createPort<OutPort>(Vec(33, 75), PortWidget::OUTPUT, module, MentalMuxes::OUTPUT_A));
  
  addChild(createLight<MedLight<BlueLED>>(Vec(41, 32), module, MentalMuxes::LEVEL_LED_A1));
  addChild(createLight<MedLight<BlueLED>>(Vec(41, 58), module, MentalMuxes::LEVEL_LED_A2));
  
  addInput(createPort<GateInPort>(Vec(3, group_offset + 75), PortWidget::INPUT, module, MentalMuxes::SELECT_B));  
	addInput(createPort<InPort>(Vec(3, group_offset + 25), PortWidget::INPUT, module, MentalMuxes::INPUT_1B));
  addInput(createPort<InPort>(Vec(3, group_offset + 50), PortWidget::INPUT, module, MentalMuxes::INPUT_2B));  
  
  addOutput(createPort<OutPort>(Vec(33,group_offset + 75), PortWidget::OUTPUT, module, MentalMuxes::OUTPUT_B));
  
  addChild(createLight<MedLight<BlueLED>>(Vec(41,group_offset + 32), module, MentalMuxes::LEVEL_LED_B1));
  addChild(createLight<MedLight<BlueLED>>(Vec(41,group_offset + 58), module, MentalMuxes::LEVEL_LED_B2));
  
  addInput(createPort<CVInPort>(Vec(3, group_offset * 2 + 125), PortWidget::INPUT, module, MentalMuxes::SELECT_C));  
	addInput(createPort<InPort>(Vec(3, group_offset * 2 + 25), PortWidget::INPUT, module, MentalMuxes::INPUT_1C));
  addInput(createPort<InPort>(Vec(3, group_offset * 2 + 50), PortWidget::INPUT, module, MentalMuxes::INPUT_2C));
  addInput(createPort<InPort>(Vec(3, group_offset * 2 + 75), PortWidget::INPUT, module, MentalMuxes::INPUT_3C));
  addInput(createPort<InPort>(Vec(3, group_offset * 2 + 100), PortWidget::INPUT, module, MentalMuxes::INPUT_4C));    
  
  addOutput(createPort<OutPort>(Vec(33,group_offset * 2 + 125), PortWidget::OUTPUT, module, MentalMuxes::OUTPUT_C));
  
  addChild(createLight<MedLight<BlueLED>>(Vec(41,group_offset * 2 + 32), module, MentalMuxes::LEVEL_LED_C1));
  addChild(createLight<MedLight<BlueLED>>(Vec(41,group_offset * 2 + 58), module, MentalMuxes::LEVEL_LED_C2));
  addChild(createLight<MedLight<BlueLED>>(Vec(41,group_offset * 2 + 82), module, MentalMuxes::LEVEL_LED_C3));
  addChild(createLight<MedLight<BlueLED>>(Vec(41,group_offset * 2 + 108), module, MentalMuxes::LEVEL_LED_C4));
	  
}

Model *modelMentalMuxes = createModel<MentalMuxes, MentalMuxesWidget>("MentalMuxes");