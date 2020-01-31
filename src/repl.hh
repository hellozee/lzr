#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <vector>

namespace lzr{
    
    class commander{
    public:
        commander() = default;

        std::string execute(std::string, std::vector<int>)
        {
            return std::string("UK!");
        }
    };
    
    enum class mode{
        normal,
        silly
    };
    
    class repl{
    private:
        commander m_commander;
        mode m_mode;
    public:
        repl() = default;
        
        void run()
        {
            std::string input;
            while(true){
                std::cout << ">> ";
                std::cin >> input;
                
                if(m_mode == mode::silly){
                    input = std::string(input.rbegin(), input.rend());
                }
                
                if(input == "ESM"){
                    m_mode = mode::silly;
                    continue;
                }
                
                if(input == "DSM"){
                    m_mode = mode::normal;
                    continue;
                }
                
                auto args = get_args(input);
                
                std::cout << m_commander.execute(input, args) << std::endl;
            }
        }
        
    private:
        /* lzr::repl::get_args takes the input and returns the `int` arguments
         * as a vector without the command itself. 
         */
        std::vector<int> get_args(std::string input)
        {
            std::vector<int> args;
            std::string arg;
            std::istringstream stream(input);
            
            bool is_command = true;
            
            while (std::getline(stream, arg, '|')) {
                
                if(is_command){
                    is_command = false;
                    continue;
                }
                
                args.push_back(std::stoi(arg));
            }
            return args;
        }
    };
}
