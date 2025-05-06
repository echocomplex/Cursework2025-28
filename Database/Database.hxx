#ifndef DATABASE_HXX
#define DATABASE_HXX

#include <List.hxx>
#include <Migrant.hxx>
#include <Filer.hxx>
#include <iostream>
#include <map>
#include <vector>
#include <Crypter.hxx>
#include <ctime>

class Database {
protected:
    Filer file;
    std::string filename;
    std::string filename_enc;
    List<Migrant> data;
    Crypter crypter;
public:
    Database(void);
    Database(const std::string& filename);
    Database(const List<Migrant>& unit, const std::string& filename);
    Database(const Database& unit);
    ~Database(void);
    Database& operator=(const Database& unit) noexcept;
    Migrant& operator[](const unsigned int index) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const Database& unit);
    const Migrant& operator[](const unsigned int index) const noexcept;
    void append(const Migrant& unit) noexcept;
    void remove(const unsigned int index) noexcept;
    unsigned int size(void) noexcept;
    void getActiveMigrants(List<Migrant>& results) const noexcept;
    void getRegionsByNationality(std::vector<std::pair<std::string, std::map<std::string, int>>>& regionsStats) const noexcept;
    unsigned short countDepartedMigrants(const std::string& region, 
                                       const Date& startDate, 
                                       const Date& endDate) const noexcept;
};

#endif // DATABASE_HXX