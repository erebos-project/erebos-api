#ifndef EREBOS_EARGS_H
#define EREBOS_EARGS_H

#include <vector>
#include <string>
#include <map>

namespace erebos {
    class args {
    public:
        struct __expected_args {
            std::string longopt;
            char shortopt;
            bool value_required : 1;
            bool required : 1; //depends on value_required
        };

        using supplied = std::map<std::string, std::string>;

        args(bool exit_fail = true,
             bool show_message_fail = true,
             bool show_help_fail = false);

        void add(const std::string& longopt,
                 const char& shortopt,
                 const std::string& description = "",
                 const bool& value_required = false,
                 const bool& required = false);

        supplied parse(const int& argc, char** argv) const;

        inline const std::string& help() const {
            return helpString;
        }
    private:
        std::vector <__expected_args> _Args;
        std::string helpString; //update this on each add()
    };
} //namespace erebos

#endif //EREBOS_EARGS_H
