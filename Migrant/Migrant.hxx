#ifndef MIGRANT_HXX
#define MIGRANT_HXX

#include <string>
#include <iostream>

class Date {
private: 
    unsigned short day, month, year;
public:
    Date(void) noexcept;
    Date(const unsigned short day, const unsigned short month, const unsigned short year);
    unsigned short getDay(void) const noexcept;
    unsigned short getMonth(void) const noexcept;
    unsigned short getYear(void) const noexcept;
    void setDay(const unsigned short day) noexcept;
    void setMonth(const unsigned short month) noexcept;
    void setYear(const unsigned short year) noexcept;
};

class Migrant {
private:
    std::string region;
    Date registration_date;
    std::string last_name;
    std::string initials;
    std::string nationality;
    unsigned short birth_year;
    std::string passport;
    std::string purpose;
    Date deregistration_date;
public:
    Migrant(void) noexcept = default;
    Migrant(const std::string& region, const Date& reg_date, const std::string& last_name, 
           const std::string& initials, const std::string& nationality, unsigned short birth_year,
           const std::string& passport, const std::string& purpose, const Date& dereg_date) noexcept;
    ~Migrant(void) noexcept = default;
    Migrant& operator=(const Migrant& unit) noexcept;
    friend std::ostream& operator<<(std::ostream& os, const Migrant& unit);
    
    std::string getRegion(void) const noexcept;
    Date getRegistrationDate(void) const noexcept;
    std::string getLastName(void) const noexcept;
    std::string getInitials(void) const noexcept;
    std::string getNationality(void) const noexcept;
    unsigned short getBirthYear(void) const noexcept;
    std::string getPassport(void) const noexcept;
    std::string getPurpose(void) const noexcept;
    Date getDeregistrationDate(void) const noexcept;
    void setRegion(const std::string& region) noexcept;
    void setRegistrationDate(const Date& date) noexcept;
    void setLastName(const std::string& last_name) noexcept;
    void setInitials(const std::string& initials) noexcept;
    void setNationality(const std::string& nationality) noexcept;
    void setBirthYear(unsigned short birth_year) noexcept;
    void setPassport(const std::string& passport) noexcept;
    void setPurpose(const std::string& purpose) noexcept;
    void setDeregistrationDate(const Date& date) noexcept;
    
    static std::string dateToString(const Date& date) noexcept;
};

#endif // MIGRANT_HXX