#ifndef DELTARES_HELPER_FUNCTIONS
#define DELTARES_HELPER_FUNCTIONS

#include "Wanda_windows.h"
#include <algorithm>
#include <format>
#include <functional>
#include <ranges>
#include <stdexcept>
#include <string>
#include <string_view>
#include <unordered_map>
#include <vector>
#include <wandaproperty.h>

#ifdef WANDAMODEL_EXPORT
#define WANDAMODEL_API __declspec(dllexport)
#else
#define WANDAMODEL_API __declspec(dllimport)
#endif

//! namespace with helper function which can be useful when using the WANDA Api
namespace wanda_helper_functions
{

template <typename Signature> [[nodiscard]] std::function<Signature> to_function(FARPROC f)
{
    return std::function<Signature>(reinterpret_cast<Signature *>(f));
}

template <typename T>
[[nodiscard]] std::function<T> loadDLLfunction(const HINSTANCE dllhandle, const std::string &function_name)
{
    if (!dllhandle)
    {
        // spdlog::error("DLL not loaded properly.");
        throw std::runtime_error("DLL not loaded properly.");
    }
    const FARPROC lpfnGetProcessID = GetProcAddress(dllhandle, function_name.c_str());
    if (!lpfnGetProcessID)
    {
        // spdlog::error("could not locate the function {}}\n", function_name);
        // spdlog::error("Error code={}", GetLastError());
        throw std::runtime_error("could not locate the function.");
    }
    // spdlog::debug("Loaded {}", function_name);
    return to_function<T>(lpfnGetProcessID);
}


bool FileExists(std::string filename);

WANDAMODEL_API
bool is_64bit_dll(const std::string &path);

//! split string in sections based on delimeter
std::vector<std::string> split(const std::string_view input, char delimiter);

//! split string in sections based on delimeter
std::vector<std::string> split(const std::string &input, char delimiter);

//! Loads data from a Wanda template file into memory so it can be used to set in the Wandamodel
/*!
 \param filename is the name and path of the template file to load.
 */
WANDAMODEL_API
std::unordered_map<std::string, wanda_prop_template> load_template(const std::string &filename);

void rtrim(std::string &s);
std::pair<int, int> convert_wanda_version_number(std::string version);

WANDAMODEL_API
std::vector<std::string> split_keywords(std::string keywords);

struct wanda_version_number
{
    // please note that order is important since we use default spaceship operator
    int major = 0;
    int minor = 0;
    int patch = 0;
    std::string remainder;

    // the first character in the string is the major version number,
    // the third element is the minor version number
    // -48 the ASCI number start at 48 see
    // https://stackoverflow.com/questions/5029840/convert-char-to-int-in-c-and-c
    // Version number is a string with point separating the different parts.
    constexpr static unsigned int ascii_offset = 48;
    wanda_version_number(std::string_view version_number)
        : major(version_number[0] - ascii_offset), minor(version_number[2] - ascii_offset),
          patch(version_number[4] - ascii_offset),
          remainder("")
    {
        int num_dots = 0;
        for (auto character : version_number)
        {
            if (character == '.')
            {
                num_dots++;
            }
        }

        if(num_dots > 2)        
        {
            remainder = version_number.substr(6);
        }      
    }
    wanda_version_number() = delete;
    /**
     * \brief 
     */

    
    auto operator<=>(const wanda_version_number &obj) const
    {
        return std::tie(major, minor, patch) <=> std::tie(obj.major, obj.minor, obj.patch);
    }
    auto operator==(const wanda_version_number &obj) const
    {
        return std::tie(major, minor, patch) == std::tie(obj.major, obj.minor, obj.patch);
    }

    std::string to_string() const
    {
        if (remainder.empty())
        {
            return std::format("{}.{}.{}", major, minor, patch);
        }
        return std::format("{}.{}.{}.{}", major, minor, patch, remainder);

    }
};

// private method
inline std::string string_to_lower(std::string str)
{
    std::ranges::transform(str, str.begin(), [](unsigned char c) { return static_cast<char>(std::tolower(c)); });
    return str;
}

}; // namespace wanda_helper_functions



#endif
