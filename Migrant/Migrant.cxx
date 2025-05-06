#include "Migrant.hxx"

Date::Date(void) noexcept {
    this->day = 1;
    this->month = 1;
    this->year = 2000;
}

Date::Date(const unsigned short day, const unsigned short month, const unsigned short year) {
    if (1 <= day && day <= 31) this->day = day;
    else this->day = 1;

    if (1 <= month && month <= 12) this->month = month;
    else this->month = 1;

    if (1900 <= year) this->year = year;
    else this->year = 2000;
}

unsigned short Date::getDay(void) const noexcept {
    return this->day;
}

unsigned short Date::getMonth(void) const noexcept {
    return this->month;
}

unsigned short Date::getYear(void) const noexcept {
    return this->year;
}

void Date::setDay(const unsigned short day) noexcept {
    this->day = day;
}

void Date::setMonth(const unsigned short month) noexcept {
    this->month = month;
}

void Date::setYear(const unsigned short year) noexcept {
    this->year = year;
}

Migrant::Migrant(const std::string& region, const Date& reg_date, const std::string& last_name,
               const std::string& initials, const std::string& nationality, unsigned short birth_year,
               const std::string& passport, const std::string& purpose, const Date& dereg_date) noexcept 
    : region(region), registration_date(reg_date), last_name(last_name), initials(initials),
      nationality(nationality), birth_year(birth_year), passport(passport), purpose(purpose),
      deregistration_date(dereg_date) {}

Migrant& Migrant::operator=(const Migrant& unit) noexcept {
    this->region = unit.region;
    this->registration_date = unit.registration_date;
    this->last_name = unit.last_name;
    this->initials = unit.initials;
    this->nationality = unit.nationality;
    this->birth_year = unit.birth_year;
    this->passport = unit.passport;
    this->purpose = unit.purpose;
    this->deregistration_date = unit.deregistration_date;
    return *this;
}

std::ostream& operator<<(std::ostream& os, const Migrant& unit) {
    os << unit.region << ", "
       << Migrant::dateToString(unit.registration_date) << ", "
       << unit.last_name << ", "
       << unit.initials << ", "
       << unit.nationality << ", "
       << unit.birth_year << ", "
       << unit.passport << ", "
       << unit.purpose << ", "
       << Migrant::dateToString(unit.deregistration_date);
    return os;
}

std::string Migrant::getRegion(void) const noexcept { return region; }
Date Migrant::getRegistrationDate(void) const noexcept { return registration_date; }
std::string Migrant::getLastName(void) const noexcept { return last_name; }
std::string Migrant::getInitials(void) const noexcept { return initials; }
std::string Migrant::getNationality(void) const noexcept { return nationality; }
unsigned short Migrant::getBirthYear(void) const noexcept { return birth_year; }
std::string Migrant::getPassport(void) const noexcept { return passport; }
std::string Migrant::getPurpose(void) const noexcept { return purpose; }
Date Migrant::getDeregistrationDate(void) const noexcept { return deregistration_date; }

void Migrant::setRegion(const std::string& region) noexcept { this->region = region; }
void Migrant::setRegistrationDate(const Date& date) noexcept { this->registration_date = date; }
void Migrant::setLastName(const std::string& last_name) noexcept { this->last_name = last_name; }
void Migrant::setInitials(const std::string& initials) noexcept { this->initials = initials; }
void Migrant::setNationality(const std::string& nationality) noexcept { this->nationality = nationality; }
void Migrant::setBirthYear(unsigned short birth_year) noexcept { this->birth_year = birth_year; }
void Migrant::setPassport(const std::string& passport) noexcept { this->passport = passport; }
void Migrant::setPurpose(const std::string& purpose) noexcept { this->purpose = purpose; }
void Migrant::setDeregistrationDate(const Date& date) noexcept { this->deregistration_date = date; }

std::string Migrant::dateToString(const Date& date) noexcept {
    return std::to_string(date.getDay()) + "." + 
           std::to_string(date.getMonth()) + "." + 
           std::to_string(date.getYear());
}