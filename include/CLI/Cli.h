#pragma once
#include <map>
#include <functional>

namespace cli
{
void quit();

class Cli
{
private:
  std::string menu_msg;
  std::string command_not_found_msg;
  std::map<std::string, std::function<void()>> *commands;

public:
  Cli();

  void set_menu_message(std::string message);
  void add_command(std::string name, std::function<void()> handler);

  void show_menu();
  void show_error();
  void show_prompt();
  std::string parse_user_input();
  void start();
};

} // namespace cli