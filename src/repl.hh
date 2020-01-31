#pragma once

#include <string>
#include <iostream>

namespace lzr{
    
    class commander{
    public:
        commander() = default;
        
        template<class ... T>
        std::string execute(std::string, T... args){
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
        
        void run(){
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
                
                std::cout << m_commander.execute(input) << std::endl;
            }
        }
    };
}
