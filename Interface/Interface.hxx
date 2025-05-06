#ifndef INTERFACE_HXX
#define INTERFACE_HXX

#include <iostream>
#include <Migrant.hxx> 
#include <List.hxx>
#include <Database.hxx>

class Interface {
private:
    Database unit;
    void displayMenu(void);
    void getMigrant(Migrant& unit);
    int removeMigrant(void);
    void clearInputBuffer(void);
    Date getDateFromUser(const std::string& prompt);
public:
    Interface(void) = default;
    Interface(const Interface& unit) = delete;
    Interface& operator=(const Interface& unit) = delete;
    ~Interface(void) noexcept = default;
    void pool(void);
};

#endif // INTERFACE_HXX