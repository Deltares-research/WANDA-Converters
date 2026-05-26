#ifndef PIPELINE_CONVERSION_EPANET_UNIT_CONVERTER_H
#define PIPELINE_CONVERSION_EPANET_UNIT_CONVERTER_H

/**
 * @brief Converts EPAnet quantities from their native units to SI units.
 *
 * Determines conversion factors based on the EPAnet flow unit system and headloss formula,
 * then applies them to length, diameter, flow, and roughness values.
 *
 * @param flow_units       EPAnet flow units code (e.g. EN_LPS, EN_GPM).
 * @param headloss_formula EPAnet headloss formula code (e.g. EN_HW, EN_DW, EN_CM).
 */
class EpanetUnitConverter {
public:
    EpanetUnitConverter(int flow_units, int headloss_formula);
    double convert_length_to_si(double length_in_epanet_units) const;
    double convert_diameter_to_si(double diameter_in_epanet_units) const;
    double convert_flow_to_si(double flow_in_epanet_units) const;
    double convert_roughness_to_si(double roughness_in_epanet_units) const;

private:
    double length_factor_ = 1.0;
    double diameter_factor_ = 1.0;
    double flow_factor_ = 1.0;
    double head_factor_ = 1.0;
    double roughness_factor_ = 1.0;
};




#endif //PIPELINE_CONVERSION_EPANET_UNIT_CONVERTER_H
