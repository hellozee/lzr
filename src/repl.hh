#pragma once

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <functional>
#include "laser.hh"

namespace lzr{
    
    class commander{
    private:
        std::map<std::string, std::function<std::string(commander*, std::vector<int>)>> m_worker;
        lzr::laser m_laser;
        
    public:
        commander()
        {
            m_worker["STR"] = &commander::command_str;
            m_worker["STP"] = &commander::command_stp;
            m_worker["ST?"] = &commander::command_st;
            m_worker["KAL"] = &commander::command_kal;
            m_worker["PW?"] = &commander::command_pwq;
            m_worker["PW="] = &commander::command_pws;
        }

        std::string 
        execute(std::string command, std::vector<int>args)
        {
            auto iterator = m_worker.find(command);
            if(iterator != m_worker.end()){
                return iterator->second(this, args);
            }
            return std::string("UK!");
        }
        
    private:
        std::string 
        command_str(std::vector<int>)
        {
            return "str";
        }
        
        std::string 
        command_stp(std::vector<int>)
        {
            return "str";
        }
        
        std::string 
        command_st(std::vector<int>)
        {
            return "str";
        }
        
        std::string 
        command_kal(std::vector<int>)
        {
            return "str";
        }
        
        std::string 
        command_pwq(std::vector<int>)
        {
            return "str";
        }
        
        std::string 
        command_pws(std::vector<int>)
        {
            return "str";
        }
    };
    
    enum class mode{
        normal,
        silly
    };
    
    class repl{
    private:
        lzr::commander m_commander;
        mode m_mode;
    public:
        repl() = default;
        
        void 
        run()
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
                
                auto [command, args] = get_args(input);
                
                std::cout << m_commander.execute(command, args) << std::endl;
            }
        }
        
    private:
        /* lzr::repl::get_args takes the input and returns the `int` arguments
         * as a vector without the command itself. Use boost/qt if available.
         * Adapted from https://www.fluentcpp.com/2017/04/21/how-to-split-a-string-in-c/
         */
        std::tuple<std::string, std::vector<int>>
        get_args(std::string input)
        {
            std::vector<int> args;
            std::string arg, command;
            std::istringstream stream(input);
            
            bool is_command = true;
            
            while (std::getline(stream, arg, '|')) {
                
                if(is_command){
                    is_command = false;
                    command = arg;
                    continue;
                }
                
                args.push_back(std::stoi(arg));
            }
            return {command, args};
        }
    };
}
