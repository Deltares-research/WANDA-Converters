#pragma once
#include <license_manager.h>

#include <future>
#include <string>


#ifdef WANDAMODEL_EXPORT
#define WANDAMODEL_API __declspec(dllexport)
#else
#define WANDAMODEL_API __declspec(dllimport)
#endif
//! \Enum class that describes the value of a component-class license.
enum class license_comp_class
{
    all, none, custom
};

/*!
 * \struct wanda_license wanda_license.hpp
 * \brief Struct that contains information on the software license.
 * The wanda_license class contains members that describe the various
 * features of the software that are enabled by the license.
 *
 * This structure is returned by the wanda_license_manager class.
 */
struct WANDAMODEL_API wanda_license
{
    float wanda_version = 0.0; /*!< Minimum Wanda version */

    bool liquid_module; /*!< Liquid module */
    bool heat_module; /*!< Heat module */
    bool multi_species_module; /*!< MultiSpecies module */
    bool gas_module; /*!< Gas module */
    bool control_module; /*!< Control module */
    bool locks_module; /*!< Locks module */

    int num_physical_components; /*!< Maximum number of physical components */
    int num_control_components; /*!< Maximum number of control components */

    license_comp_class special_components = license_comp_class::none; /*!< Special components */
    license_comp_class prototype_components = license_comp_class::none; /*!< Prototype components */

    std::vector<std::string> special_components_list;
    /*!< If special_components equals True, this list contains the class-sort keys of special components */
    std::vector<std::string> prototype_components_list;
    /*!< If prototype_components equals True, this list contains the class-sort keys of prototype components   */

    bool wanda_model_engine; /*!< Indicates if this license gives access to the Wanda model engine */

    bool is_server_license; /*!< Indicates if this is a floating/server license*/
    std::string license_expiration_date; /*!< License expiration date */
    std::string main_vendor_string; /*!< Vendor string */
};

/*!
 * \struct license_feature_strings wanda_license.hpp
 * \brief Struct that contains the feature strings used in the license manager.
 * The license_feature_strings class contains the feature strings used in the
 * license manager.
 */
struct license_feature_strings
{
    std::string_view system_featstr = "WANDA_SYSTEM"; /*!< \private Feature string for WANDA_SYSTEM */
    std::string_view version_featstr = "WANDA_VERSION"; /*!< \private Feature string for WANDA_VERSION */
    std::string_view module_featstr = "WANDA_MODULE"; /*!< \private Feature string for WANDA_MODULE */
    std::string_view max_physcomp_featstr = "WANDA_MAX_PHYSCOMP"; /*!< \private Feature string for WANDA_MAX_PHYSCOMP */
    std::string_view max_ctrlcomp_featstr = "WANDA_MAX_CTRLCOMP"; /*!< \private Feature string for WANDA_MAX_CTRLCOMP */
    std::string_view specials_featstr = "WANDA_SPECIALS"; /*!< \private Feature string for WANDA_SPECIALS */
    std::string_view prototypes_featstr = "WANDA_PROTOTYPES"; /*!< \private Feature string for WANDA_PROTOTYPES */
    std::string_view engine_featstr = "WANDA_ENGINE"; /*!< \private Feature string for WANDA_ENGINE */
};

/*!
 * \class wanda_license_manager wanda_license.hpp
 * \brief Provides information contained in the software license.
 * The wanda_license_manager class reads the license information from the
 * license manager and checks if the license is valid. The license information is read
 * from the DS_Flex subsystem (FlexLM). The license information is stored in a wanda_license
 * structure and can be retrieved by the user.
 *
 * The wanda_license_manager contains some hard-coded values/references:
 * - The default license file path (set to "" for automatic detection)
 * - The default version number (set to "4.0")
 * - The license feature names (e.g. "WANDA_SYSTEM")
 */
class WANDAMODEL_API wanda_license_manager
{
public:
    /*!
     * \brief Constructor of the wanda_license_manager class.
     * Locks WANDA_SYSTEM and WANDA_VERSION features and
     * prepares license info struct.
     */
    wanda_license_manager();
    /*!
     * \brief Destructor of the wanda_license_manager class.
     * Releases WANDA_SYSTEM and WANDA_VERSION features.
     */
    ~wanda_license_manager();

    /*!
     * \brief Returns a wanda_license structure, containing the license information.
     * \returns A wanda_license structure, containing the license information.
     */
    wanda_license get_license_data();

    /*!
     * \brief Checks if a license is (still) valid.
     * \returns True if the license is valid, false otherwise.
     */
    bool check_license_valid() const noexcept;

private:
    std::shared_future<wanda_license> license_data_future_; /*!< \private Future object for license data */
    // wanda_license license_data_;     /*!< \private Contains the license information */
    license_manager *dauth; /*!< \private Pointer to the license manager */
};

wanda_license read_license_information(license_manager *dauth);
/*!< Reads the license information from the license manager */