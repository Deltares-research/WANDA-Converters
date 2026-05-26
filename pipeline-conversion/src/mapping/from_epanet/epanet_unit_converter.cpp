#include "epanet_unit_converter.h"
#include <epanet2.h>
#include <stdexcept>

EpanetUnitConverter::EpanetUnitConverter(const int flow_units, int headloss_formula) {

    // ---- Classify unit system once ----
    const bool is_si =
        (flow_units == EN_LPS ||
         flow_units == EN_LPM ||
         flow_units == EN_CMH ||
         flow_units == EN_CMD ||
         flow_units == EN_MLD ||
         flow_units == EN_CMS);

    // ---- Length / head ----
    if (is_si) {
        length_factor_ = 1.0;        // already meters
        head_factor_   = 1.0;        // already meters
        diameter_factor_ = 1.0 / 1000.0;  // mm → m
    } else {
        length_factor_ = 0.3048;     // ft → m
        head_factor_   = 0.3048;
        diameter_factor_ = 0.0254;        // inch → m
    }
    switch (headloss_formula) {
        case EN_HW:
            roughness_factor_ = 1.0; // Unit less factor
            break;
        case EN_DW:
            roughness_factor_ = length_factor_; // convert to meters
            break;
        case EN_CM:
            roughness_factor_ = 1.0; // Unit less factor
            break;
        default:
            throw std::runtime_error("Unsupported headloss formula");
    }
    // ---- Flow ----
    switch (flow_units) {
        case EN_CMS: flow_factor_ = 1.0; break;
        case EN_LPS: flow_factor_ = 1e-3; break;
        case EN_LPM: flow_factor_ = 1e-3 / 60.0; break;
        case EN_CMH: flow_factor_ = 1.0 / 3600.0; break;
        case EN_CMD: flow_factor_ = 1.0 / 86400.0; break;
        case EN_MLD: flow_factor_ = (1000.0 / 86400.0); break;
        case EN_GPM: flow_factor_ = 0.0000630902; break;
        case EN_CFS: flow_factor_ = 0.0283168; break;
        case EN_MGD: flow_factor_ = 0.043812636; break;
        case EN_IMGD: flow_factor_ = 0.0526168; break;
        case EN_AFD: flow_factor_ = 0.01427641; break;
        default:
            throw std::runtime_error("Unsupported flow units");
    }
}

double EpanetUnitConverter::convert_length_to_si(const double length_in_epanet_units) const {
    return length_factor_ * length_in_epanet_units;
}

double EpanetUnitConverter::convert_diameter_to_si(const double diameter_in_epanet_units) const {
    return diameter_factor_ * diameter_in_epanet_units;
}

double EpanetUnitConverter::convert_flow_to_si(double const flow_in_epanet_units) const {
    return flow_factor_ * flow_in_epanet_units;
}

double EpanetUnitConverter::convert_roughness_to_si(const double roughness_in_epanet_units) const {
    return roughness_factor_ * roughness_in_epanet_units;
}
