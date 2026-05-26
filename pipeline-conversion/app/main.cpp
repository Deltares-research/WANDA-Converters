#include <iostream>
#include "model_converter.h"
int main() {
   /* std::string input_model_type = "WANDA";
    std::string input_file = R"(c:\work\repos\wanda\WANDA-Converters\pipeline-conversion\test_data\Sewage_transient.wdi)";
    std::string output_file = R"(c:\work\repos\wanda\WANDA-Converters\pipeline-conversion\test_data\Sewage_transient_new.wdi)";
    ModelConverter converter{input_file, input_model_type};
    converter.convert(output_file, input_model_type);*/
    std::cout << "Hello, Wanda!" << std::endl;
    std::string epanet_input_model_type = "EPAnet";
    std::string epa_net_input_file = R"(c:\work\repos\wanda\WANDA-Converters\pipeline-conversion\test_data\test_model.inp)";
    ModelConverter epanet2wanda(epa_net_input_file, epanet_input_model_type);
    std::string output_file = R"(c:\work\repos\wanda\WANDA-Converters\pipeline-conversion\test_data\epanet.wdi)";
    epanet2wanda.convert(output_file, "WANDA");

}
