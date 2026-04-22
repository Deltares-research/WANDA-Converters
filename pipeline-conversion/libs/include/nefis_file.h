#ifndef NEFIS_FILE
#define NEFIS_FILE

#include <array>
#include <string>
#include <vector>
#include <memory>

#ifdef WANDAMODEL_EXPORT
#define WANDAMODEL_API __declspec(dllexport)
#else
#define WANDAMODEL_API __declspec(dllimport)
#endif

struct nefis_uindex
{
    int start = 1;
    int end = 1;
    int step = 1;
};

// Note that NEFIS is NOT thread-safe!!
class WANDAMODEL_API nefis_file
{
  public:
    nefis_file() : file_name(""){};
    nefis_file(std::string const &file, bool read_only = false) : file_name(file), _read_only(read_only)
    {
    }
    void set_file(std::string const &file);
    bool is_open() const;
    int open();
    int open(char access_modifier);
    int close();
    void flush();
    int get_int_attribute(std::string_view, std::string_view) const;
    void set_int_attribute(std::string_view groupname, std::string_view attributename, int value);
    void get_string_element(const std::string &groupname, const std::string &elementname, nefis_uindex uindex,
                            int stringlength, std::vector<std::string> &results) const;
    void get_string_element(std::string_view grpname, std::string_view elmname, const nefis_uindex &uindex_1st_dim,
                            const nefis_uindex &uindex_2nd_dim, int stringlength,
                            std::vector<std::vector<std::string>> &results) const;
    int get_string_length(std::string_view elementname_);
    void get_int_element(std::string_view, std::string_view, nefis_uindex uindex, std::vector<int> &) const;
    void get_int_element(std::string_view, std::string_view, const nefis_uindex &uindex_1st_dim,
                         const nefis_uindex &uindex_2nd_dim,
                         std::vector<std::vector<int>> &) const;
    void get_float_element(std::string_view, std::string_view, nefis_uindex uindex, std::vector<float> &) const;
    void get_float_element(std::string_view, std::string_view, const nefis_uindex &uindex_1st_dim,
                           const nefis_uindex &uindex_2nd_dim,
                           std::vector<std::vector<float>> &, bool transpose = false) const;
    void write_float_elements(std::string_view, std::string_view, const nefis_uindex &uindex, std::vector<float>&);
    void write_float_elements(std::string_view, std::string_view, const nefis_uindex &uindex_1st_dim,
                              const nefis_uindex &uindex_2nd_dim,
                              std::vector<std::vector<float>>&);
    void write_int_elements(std::string_view, std::string_view, const nefis_uindex &uindex, const std::vector<int>&);
    void write_string_elements(std::string_view, std::string_view, const nefis_uindex &uindex, int,
                               std::vector<std::string>&);
    void write_string_elements(std::string_view, std::string_view, const nefis_uindex &uindex_1st_dim,
                               const nefis_uindex &uindex_2nd_dim, int, const std::vector<std::vector<std::string>> &);
    int get_group_dim(std::string_view) const;
    int get_maxdim_index(std::string_view groupname) const;
    std::string get_cel_name(std::string_view grpname) const;
    std::vector<std::string> get_element_names(std::string) const;
    std::string get_element_type(std::string_view elnam) const;
    std::string get_first_groupname() const;
    std::string get_next_groupname() const;
    std::string get_first_int_attribute(std::string_view) const;
    std::string get_filename() const
    {
        return file_name;
    }
    int get_element_size(std::string_view element) const;
    int get_element_dimension(std::string_view element) const;
    static std::string get_last_error() noexcept;

    constexpr static nefis_uindex single_elem_uindex = {1, 1, 1};
    constexpr static std::array std_order = {1, 2, 3, 4, 5};

  private:
    mutable int file_pointer = 0; // mutable because the file pointer is passed as a bare non-const pointer to the C
                                  // interface. It's not modifed by Nefis
    std::string file_name;
    bool file_status_open = false;
    bool _read_only = false;
};

#endif
