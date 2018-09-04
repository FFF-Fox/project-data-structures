#include "Cli.h"

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
    commands(new std::map<std::string, void (*)()>)
{
    add_command("q", quit);
}

void Cli::set_menu_message(std::string message)
{
    menu_msg = message;
}

void Cli::add_command(std::string name, void (*handler)())
{
    commands->emplace(name, handler);
}

void Cli::start()
{
    // while (true)
    // {
    //     show_menu();
    //     std::string usr_in = parse_user_input();
    //     // commands->find(usr_in);
    // }
}
} // namespace cli

/**
 * TODO:
 *  show_menu()
 *  parse_user_input()
 *  start()
 */