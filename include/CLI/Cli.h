#pragma once
#include <map>

namespace cli
{
void quit();

class Cli
{
  private:
    std::string menu_msg;
    std::string command_not_found_msg;
    std::map<std::string, void (*)()> *commands;

  public:
    Cli();

    void set_menu_message(std::string message);
    void add_command(std::string name, void (*handler)());

    void show_menu();
    void show_error();
    std::string parse_user_input();
    void start();
};

} // namespace cli