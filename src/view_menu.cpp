#include "ui.h"

void ui::ViewUser::display()
{
  std::cout << "Hello World" << std::endl;
  this->master->display();
}