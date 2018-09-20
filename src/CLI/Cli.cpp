#include "Cli.h"
#include <iostream>

namespace cli
{
/**
 * quit
 * Instantly exits the program.
 */
void quit()
{
    exit(EXIT_SUCCESS);
}

Cli::Cli() :
    menu_msg("'q' - έξοδος από το πρόγραμμα."),
    command_not_found_msg("Λάθος είσοδος."),
    commands(new std::map<std::string, std::function<void()>>)
{
    add_command("q", [](){quit();});
}

void Cli::set_menu_message(std::string message)
{
    menu_msg = message;
}

void Cli::add_command(std::string name, std::function<void()> handler)
{
    commands->emplace(name, handler);
}

void Cli::show_menu()
{
    std::cout << menu_msg << std::endl;
    show_prompt();
}

void Cli::show_error()
{
    std::cout << command_not_found_msg << std::endl;
}

void Cli::show_prompt()
{
    std::cout << "> ";
}

std::string Cli::parse_user_input()
{
    std::string user_in;
    std::cin >> user_in;

    return user_in;
}

void Cli::start()
{
    while (true)
    {
        show_menu();
        std::string user_in = parse_user_input();

        if (commands->find(user_in) == commands->end())
        {
            show_error();
        }
        else
        {
            commands->at(user_in)();
        }
    }
}
} // namespace cli