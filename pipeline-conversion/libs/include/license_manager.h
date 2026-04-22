#ifndef LICENSEMANAGER
#define LICENSEMANAGER

#include <chrono>
#include <stdexcept>
#include <unordered_set>
#include <string>
#include <string_view>

#ifdef WANDAMODEL_EXPORT
#define WANDAMODEL_API __declspec(dllexport)
#else
#define WANDAMODEL_API __declspec(dllimport)
#endif
/*!
 * \exceptionLicenseException license_manager.hpp
 * \brief Exception class for license errors
 * The LicenseException class is used to throw exceptions when license errors occur.
 */
class LicenseException : public std::runtime_error
{
  public:
    /*!
     * \brief Constructor
     * \param msg The error message
     */
    LicenseException(const std::string &msg) : std::runtime_error(msg)
    {
    }
};

/*!
 * \class license_manager license_manager.hpp
 * \brief (internal) License manager class
 * The license_manager class is used internally to manage the software license. This
 * is a RAII wrapper around the Deltares license authentication library (dauth). It is
 * implemented as a singleton as the dauth library can only be initialized
 * (and cleanup'ed!) once in the application lifetime.
 */
class WANDAMODEL_API license_manager
{
public:
    /*!
     * \brief Get the license manager instance
     * Note that only the first call to this function will actually create an
     * instance of the license mananger. This means that if get_instance is called
     * a second time with different arguments, the arguments will be ignored and the
     * existing instance will be returned. This doesn't matter in most cases, a the
     * path to the license file should be left empty for automatic detection
     *
     * \param path The path to the license file. If empty, the manager will
     * search for the license file in the configured License-path.
     * \param version The license version identifier
     * \param show_dialogs Show error dialogs. Should be set to false in most cases.
     * \param heartbeat Enable the heartbeat mechanism. Should be enabled in most cases.
     * \return A pointer to the license_manager instance
     */
    static license_manager *get_instance(std::string_view path, std::string_view version, 
        bool show_dialogs = false, bool heartbeat = true)
    {
        static license_manager instance(path, version, show_dialogs,heartbeat);
        return &instance;
    }
    license_manager(license_manager &) = delete;
    license_manager &operator=(license_manager &) = delete;
    license_manager(license_manager &&) = delete;
    license_manager &operator=(license_manager &&) = delete;

    ~license_manager();

    /*!
     * \brief Requests/reservers a license-feature
     * \param feature_name The name of the feature to request
     * \return True if the license was granted, false otherwise
     */
    bool request_license(const std::string_view feature_name);

    /*!
     * \brief Get the vendor string for a feature
     * \param feature_name The name of the feature
     * \return The vendor string
     */
    std::string get_vendor_string(const std::string_view feature_name);

    /*!
     * \brief Check if a feature is provided by a floating/server license
     * \param feature_name The name of the feature
     * \return True if the feature is a server license, false otherwise
     */
    bool is_server_license(const std::string_view feature_name);

    /*!
     * \brief Get the expiration date of a license
     * \param feature_name The name of the feature
     * \return The expiration date
     */
    std::chrono::year_month_day get_license_date(const std::string_view feature_name);

    /*!
     * \brief Get the expiration date of a license as a string
     * \param feature_name The name of the feature
     * \return The expiration date
     */
    std::string get_license_date_str(const std::string_view feature_name);

    /*!
     * \brief Release a license-feature
     * \param feature_name The name of the feature to release
     */
    void release_license(const std::string_view feature_name);

    /*!
     * \brief Release all locked features
     */
    void release_all();

    /*!
     * \brief Get all locked features
     * \return A set of locked features
     */
    std::unordered_set<std::string> get_all_locked_features()
    {
        return locked_features_;
    }

private:
    license_manager(std::string_view path, std::string_view version, bool show_dialogs = false, bool heartbeat = true);
    static void check_errors(const char* name, bool result);
    bool checkout_license(const std::string &feature_name) const noexcept;
    bool checkin_license(const std::string &feature_name) const noexcept;
    std::chrono::year_month_day str_to_date(const std::string_view date_sv);

    std::unordered_set<std::string> locked_features_;
    std::string license_file_path_;
    std::string version_;
};

#endif