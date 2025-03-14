#include <filesystem>
#include <string>

namespace htap {
    std::string execute_command(const std::string& command);
    std::string execute_temp_cpp(const std::string& code);
    void process_htap(const std::filesystem::path& path);
    void generate_html(const std::filesystem::path& path);
} // namespace htap
