///////////////////////////////////////////////////
//
//   8 to 1 Mux with Binary Decoder selector VCV Module
//
//   Strum 2017
//
///////////////////////////////////////////////////

#include "mental.hpp"

struct MentalMux8 : Module {
	enum ParamIds {
    NUM_PARAMS
	};  
	enum InputIds {
    INPUT_1,
    INPUT_2,
    INPUT_4,
    SIG_INPUT,		  
		NUM_INPUTS = SIG_INPUT + 8
	};
	enum OutputIds {
    OUTPUT,    
		NUM_OUTPUTS
	};
  enum LightIds {
    INPUT_LEDS,
    NUM_LIGHTS = INPUT_LEDS + 8
  };
    
  float in_1 = 0.0;
  float in_2 = 0.0;
  float in_4 = 0.0;
  
  int one, two, four, decoded;
  
	MentalMux8() {
		config(NUM_PARAMS, NUM_INPUTS, NUM_OUTPUTS, NUM_LIGHTS);}
	void step() override;  
};

void MentalMux8::step()
{
  for ( int i = 0 ; i < 8 ; i ++)
  {
    lights[INPUT_LEDS + i].value = 0.0;   
  }
  outputs[OUTPUT].value = 0.0;
  
  in_1 = inputs[INPUT_1].value;
  in_2 = inputs[INPUT_2].value;
  in_4 = inputs[INPUT_4].value;
  
  if (in_1 > 0.0 ) 
  {
    one = 1;
  } else
  {
    one = 0;
  }
  if (in_2 > 0.0) 
  {
    two = 2;
  } else
  {
    two = 0;
  }
  if (in_4 > 0.0) 
  {
    four = 4;
  } else
  {
    four = 0;
  }
  
  decoded = one + two + four;  
  outputs[OUTPUT].value = inputs[SIG_INPUT + decoded].value;
  lights[INPUT_LEDS + decoded].value = 1.0; 
}

//////////////////////////////////////////////////////////////
struct MentalMux8Widget : ModuleWidget {
  MentalMux8Widget(MentalMux8 *module);
};

MentalMux8Widget::MentalMux8Widget(MentalMux8 *module) : ModuleWidget(module)
{

  setPanel(SVG::load(assetPlugin(pluginInstance, "res/MentalMux8.svg")));
	
  int spacing = 25; 
  int top_space = 15;
  
  addInput(createPort<GateInPort>(Vec(3, top_space), PortWidget::INPUT, module, MentalMux8::INPUT_1));
  addInput(createPort<GateInPort>(Vec(3, top_space + spacing), PortWidget::INPUT, module, MentalMux8::INPUT_2));
  addInput(createPort<GateInPort>(Vec(3, top_space + spacing * 2), PortWidget::INPUT, module, MentalMux8::INPUT_4));
  
  for (int i = 0; i < 8 ; i++)
  {  
   addInput(createPort<InPort>(Vec(3, top_space + spacing * i + 100), PortWidget::INPUT, module, MentalMux8::SIG_INPUT + i));   	 
   addChild(createLight<MedLight<BlueLED>>(Vec(33, top_space +  spacing * i + 8 + 100), module, MentalMux8::INPUT_LEDS + i));
  }
  
  addOutput(createPort<OutPort>(Vec(30, top_space + spacing), PortWidget::OUTPUT, module, MentalMux8::OUTPUT));  
  
}

Model *modelMentalMux8 = createModel<MentalMux8, MentalMux8Widget>("MentalMux8");