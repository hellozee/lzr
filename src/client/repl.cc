#include "repl.hh"

lzr::repl::repl(std::string server_ip)
    : m_client(lzr::client(server_ip))
{
}

void
lzr::repl::run()
{
    std::string input;
    while (true) {
        std::cout << ">> ";
        std::getline(std::cin, input);

        if (m_mode == mode::silly) {
            input = std::string(input.rbegin(), input.rend());
        }

        if (input == "ESM") {
            m_mode = mode::silly;
            continue;
        }

        if (input == "DSM") {
            m_mode = mode::normal;
            continue;
        }

        m_client.send(input);

        auto output = m_client.receive();
        output.pop_back();

        std::cout << output << std::endl;
    }
}