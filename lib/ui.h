#ifndef UI_H
#define UI_H

#include "storage.h"

namespace ui
{
  storage::User loginUI(storage::Database<storage::User> userData);
  
}

#endif