#pragma once

#include <vector>
#include <string>
#include "api.h"

class AutonSelector 
{
public:
  AutonSelector();
  AutonSelector(int start);
  ~AutonSelector();

  void display_autons();
  void iterate(); //called when a user presses a button to change the auton selection by 1
  void add(std::string name, std::string description, std::string description2);
  void add(std::string name, std::string description);
  void add(std::string name);

  int getSelected();

private:
  int selected;
  int numberOfAutons;

  std::vector<std::string> autons;
  std::vector<std::vector<std::string>> descriptions;
};