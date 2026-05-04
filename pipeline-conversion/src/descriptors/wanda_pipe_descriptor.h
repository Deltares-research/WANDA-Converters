#pragma once

/**
 * @brief Data descriptor holding the physical properties of a WANDA pipe.
 *
 * Fields (all in SI / meters):
 * - inner_diameter_m : Inner diameter of the pipe [m].
 * - length_m         : Length of the pipe [m].
 * - wall_roughness_m : Wall roughness of the pipe [m].
 */
struct WandaPipeDescriptor {
  double inner_diameter_m{0.0};
  double length_m{0.0};
  double wall_roughness_m{0.0};
};
