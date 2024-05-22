#pragma once

#include "storage.h"
#include <iomanip>
#include <functional>

namespace ui
{
  // handle the login process for a user. It takes a Database object of User type as an argument
  storage::User loginUI(storage::Database<storage::User>);
  void createHeader(std::string, int = 60, int = 2);
  void createLine(char = '=', int = 60);

  class UIMaster
  {
  protected:
    storage::User userInfo;
    storage::Database<storage::BillSplit> billSplit;
    storage::Database<storage::BillSplit> requestedBillSplit;
    ui::UIMaster *master = nullptr;

    void getOption(
        std::vector<char>,
        std::vector<std::string>,
        std::vector<std::function<void()>>,
        bool = false);

  public:
    explicit UIMaster(
        storage::User,
        storage::Database<storage::BillSplit> &,
        storage::Database<storage::BillSplit> &);

    explicit UIMaster(ui::UIMaster *);
    virtual void display() {}
  };

  class ViewUser : UIMaster
  {
    storage::Database<storage::User>* userDatabase;
    using UIMaster::UIMaster;
    void displayUserList();
    void displayUserRow(std::string, std::string, std::string, std::string);
    void displayUserTable();
    void createUser();
    void deleteUser();

  public:
    void display() override;
  };

  class MainMenu : UIMaster
  {
  public:
    using UIMaster::UIMaster;
    void display() override;
  };
}