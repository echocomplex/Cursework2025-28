#include "Database.hxx"

Database::Database(void) {
    this->filename = "database.txt";
    this->filename_enc = "database.enc";
    this->crypter.decrypt(this->filename_enc, this->filename);
    this->file.open(this->filename, true);
    this->file.readToList(this->data);
}

Database::Database(const std::string& filename) {
    this->filename = filename + ".txt";
    this->filename_enc = filename + ".enc";
    this->crypter.encrypt(this->filename_enc, this->filename);
    this->file.open(filename);
    this->file.readToList(this->data);
}

Database::Database(const List<Migrant>& unit, const std::string& filename) {
    this->data = unit;
    this->filename = filename + ".txt";
    this->filename_enc = filename + ".enc";
    this->file.open(this->filename);
}

Database::Database(const Database& unit) {
    this->data = unit.data;
    this->file.open(unit.filename);
    this->filename = unit.filename;
    this->filename_enc = unit.filename_enc;
}

Database::~Database(void) {
    this->file.rewriteFromList(this->data);
    this->crypter.encrypt(this->filename, this->filename_enc);
}

Database& Database::operator=(const Database& unit) noexcept {
    if (this == &unit) return *this;
    this->data = unit.data;
    this->filename = unit.filename;
    this->filename_enc = unit.filename_enc;
    this->file.open(unit.filename);
    return *this;
}

Migrant& Database::operator[](const unsigned int index) noexcept {
    return this->data[index];
}

std::ostream& operator<<(std::ostream& os, const Database& unit) {
    for (unsigned int i = 0; i < unit.data.length(); ++i) 
        os << i + 1 << ' ' << unit[i] << std::endl;
    return os;
}

const Migrant& Database::operator[](const unsigned int index) const noexcept {
    return this->data[index];
}

void Database::append(const Migrant& unit) noexcept {
    this->data.append(unit);
}

void Database::remove(const unsigned int index) noexcept {
    this->data.remove(index);
}

unsigned int Database::size() noexcept {
    return this->data.length();
}

void Database::getActiveMigrants(List<Migrant>& results) const noexcept {
    std::time_t now = std::time(nullptr);
    std::tm* local = std::localtime(&now);
    Date currentDate(local->tm_mday, local->tm_mon + 1, local->tm_year + 1900);

    for (unsigned int i = 0; i < this->data.length(); ++i) {
        const Migrant& m = this->data[i];
        const Date& deregDate = m.getDeregistrationDate();
        
        if ((deregDate.getYear() == 2000 && deregDate.getMonth() == 1 && deregDate.getDay() == 1) ||
            (deregDate.getYear() > currentDate.getYear()) ||
            (deregDate.getYear() == currentDate.getYear() && deregDate.getMonth() > currentDate.getMonth()) ||
            (deregDate.getYear() == currentDate.getYear() && deregDate.getMonth() == currentDate.getMonth() && deregDate.getDay() > currentDate.getDay())) {
            results.append(m);
        }
    }
}

void Database::getRegionsByNationality(std::vector<std::pair<std::string, std::map<std::string, int>>>& regionsStats) const noexcept {
    std::map<std::string, std::map<std::string, int>> tempStats;

    for (unsigned int i = 0; i < this->data.length(); ++i) {
        const Migrant& m = this->data[i];
        tempStats[m.getRegion()][m.getNationality()]++;
    }

    regionsStats.assign(tempStats.begin(), tempStats.end());

    std::sort(regionsStats.begin(), regionsStats.end(),
        [](const auto& a, const auto& b) {
            int countA = 0, countB = 0;
            for (const auto& nat : a.second) countA += nat.second;
            for (const auto& nat : b.second) countB += nat.second;
            return countA > countB;
        });

    for (auto& region : regionsStats) {
        std::vector<std::pair<std::string, int>> sortedNats(region.second.begin(), region.second.end());
        std::sort(sortedNats.begin(), sortedNats.end(),
            [](const auto& a, const auto& b) { return a.second > b.second; });
        
        region.second.clear();
        for (const auto& nat : sortedNats) {
            region.second.insert(nat);
        }
    }
}

unsigned short Database::countDepartedMigrants(const std::string& region, 
                                             const Date& startDate, 
                                             const Date& endDate) const noexcept {
    unsigned short count = 0;
    
    for (unsigned int i = 0; i < this->data.length(); ++i) {
        const Migrant& m = this->data[i];
        const Date& deregDate = m.getDeregistrationDate();
        
        if (m.getRegion() == region) {
            if ((deregDate.getYear() > startDate.getYear() || 
                (deregDate.getYear() == startDate.getYear() && deregDate.getMonth() > startDate.getMonth()) ||
                (deregDate.getYear() == startDate.getYear() && deregDate.getMonth() == startDate.getMonth() && deregDate.getDay() >= startDate.getDay())) &&
                (deregDate.getYear() < endDate.getYear() ||
                (deregDate.getYear() == endDate.getYear() && deregDate.getMonth() < endDate.getMonth()) ||
                (deregDate.getYear() == endDate.getYear() && deregDate.getMonth() == endDate.getMonth() && deregDate.getDay() <= endDate.getDay()))) {
                count++;
            }
        }
    }
    
    return count;
}