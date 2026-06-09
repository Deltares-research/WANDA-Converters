#include "epanet_model_importer.h"
#include "epanet_node_importer.h"
#include "epanet_pipe_importer.h"
#include "epanet_reservoir_importer.h"
#include "epanet_unit_converter.h"
#include "epanet_valve_importer.h"

EpanetImporter::EpanetImporter(const std::string &model_file) : epanet_project(EN_Project()) {
    EN_createproject(&epanet_project);
    EN_open(epanet_project, model_file.c_str(), "", "");
}

EpanetImporter::~EpanetImporter() = default;

Network EpanetImporter::import() const {
    Network network;
    int epa_net_unit;
    EN_getflowunits(epanet_project, &epa_net_unit);

    double headloss_formula = 0.0;
    EN_getoption(epanet_project, EN_HEADLOSSFORM, &headloss_formula);
    int headloss = static_cast<int>(headloss_formula);
    EpanetUnitConverter unit_converter(epa_net_unit, headloss); // TODO: get actual flow units and headloss
    // formula from project options

    int link_count = 0;
    EN_getcount(epanet_project, EN_LINKCOUNT, &link_count);
    EpanetPipeImporter pipe_importer;
    for (int i = 1; i <= link_count; ++i) {
        int link_type = 0;
        EN_getlinktype(epanet_project, i, &link_type);
        switch (link_type) {
            case EN_PIPE:
            case EN_CVPIPE:
                network.pipes.push_back(pipe_importer.import(epanet_project, i, unit_converter));
                break;
            case EN_PRV:
            case EN_PSV:
            case EN_PBV:
            case EN_FCV:
            case EN_TCV:
            case EN_GPV:
            case EN_PCV:
                network.valves.push_back(EpanetValveImporter().import(epanet_project, i, unit_converter));
                break;
            default:
                continue;
        }
    }
    int node_count = 0;
    EN_getcount(epanet_project, EN_NODECOUNT, &node_count);
    EpanetNodeImporter node_importer;
    EpanetReservoirImporter reservoir_importer;
    for (int i = 1; i <= node_count; ++i) {
        int node_type = 0;
        EN_getnodetype(epanet_project, i, &node_type);
        switch (node_type) {
            case EN_JUNCTION:
                network.nodes.push_back(node_importer.import(epanet_project, i, unit_converter));
                break;
            case EN_RESERVOIR:
                network.reservoirs.push_back(reservoir_importer.import(epanet_project, i, unit_converter));
                network.nodes.push_back(
                    Node{.id = network.reservoirs.back().name, .position = network.reservoirs.back().position});
                break;
            default:
                continue;
        }
    }

    return network;
}
