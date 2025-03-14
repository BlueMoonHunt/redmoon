#include "htap.hpp"
#include <fstream>
#include <iostream>
#include <array>

namespace htap {
    std::string execute_temp_cpp(const std::string& code) {
        std::filesystem::path temp_cpp_file = std::filesystem::temp_directory_path() / "temp_code.cpp";
        std::ofstream temp_cpp_stream(temp_cpp_file);

        if (!temp_cpp_stream.is_open())
            throw std::runtime_error("Failed to create temporary C++ file.");

        temp_cpp_stream << "#include <iostream>\nint main() {\n" << code << "\nreturn 0;\n}";
        temp_cpp_stream.close();

        std::filesystem::path temp_exe_file = std::filesystem::temp_directory_path() / "temp_code";
        std::string compile_command = "g++ -o " + temp_exe_file.string() + " " + temp_cpp_file.string() + " 2>&1";
        std::string compile_output = execute_command(compile_command);
        if (!compile_output.empty())
            throw std::runtime_error("Compilation failed: " + compile_output);

        std::string execute_command_str = temp_exe_file.string() + " 2>&1";
        std::string execute_output = execute_command(execute_command_str);

        std::filesystem::remove(temp_cpp_file);
        std::filesystem::remove(temp_exe_file);

        return execute_output;
    }

    void process_htap(const std::filesystem::path& path) {
        std::filesystem::path html_path = path;
        html_path.replace_extension(".html");

        std::ifstream input_file(html_path);
        std::ofstream output_file(html_path);

        if (!input_file.is_open() || !output_file.is_open())
            std::cerr << "Error: Could not open file:" << html_path << "\n";

        std::string line;
        bool in_code_block = false;
        std::stringstream code_buffer;


        while (std::getline(input_file, line)) {
            size_t start_pos = 0;
            while (start_pos < line.length()) {
                size_t percent_pos = line.find('%', start_pos);
                if (percent_pos == std::string::npos)
                    if (!in_code_block)
                        output_file << line.substr(start_pos) << "\n";
                    else
                        code_buffer << line.substr(start_pos) << "\n";
                else
                    if (!in_code_block) {
                        output_file << line.substr(start_pos, percent_pos - start_pos);
                        in_code_block = true;
                        code_buffer.str("");
                        code_buffer.clear();
                        start_pos = percent_pos + 1;
                    }
                    else {
                        code_buffer << line.substr(start_pos, percent_pos - start_pos);
                        in_code_block = false;
                        start_pos = percent_pos + 1;
                        try {
                            std::string code_output = execute_temp_cpp(code_buffer.str());
                            output_file << code_output;
                        }
                        catch (const std::runtime_error& e) {
                            std::cerr << "Errror Executing code: " << e.what() << "\n";
                            output_file << "\n";
                        }
                    }
            }

        }
        input_file.close();
        output_file.close();
        std::cout << "Converted " << path << " to " << html_path << "\n";
    }

    void generate_html(const std::filesystem::path& path) {
        if (std::filesystem::is_directory(path)) {
            for (const auto& entry : std::filesystem::recursive_directory_iterator(path))
                if (entry.is_regular_file() && entry.path().extension() == ".htap")
                    process_htap(entry.path());
        }
        else if (std::filesystem::is_regular_file(path) && path.extension() == ".htap")
            process_htap(path);
        else
            std::cerr << "Error: Invalid path. Must be a directory or a .htap file.\n";
    }

    std::string htap::execute_command(const std::string& command) {
        std::array<char, 128> buffer;
        std::string result;
        std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(command.c_str(), "r"), pclose);

        if (!pipe)
            throw std::runtime_error("popen() failed!");

        while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr)
            result += buffer.data();
            
        return result;
    }
} // namespace htap