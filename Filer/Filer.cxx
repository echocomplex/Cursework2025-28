#include "Filer.hxx"

Filer::Filer(const std::string& path, const bool createNew) {
    if (createNew) {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) {
            this->file.open(path, std::ios::out);
            this->file.close();
            this->file.open(path, std::ios::in);
            if (!this->file.is_open()) throw std::runtime_error("Failed to create the file.");
        }
    }
    else {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) throw std::runtime_error("File cannot be opened or does not exists");
    }
    this->path = path;
}

Filer::~Filer(void) noexcept {
    if (this->file.is_open()) this->file.close();
}

void Filer::open(const std::string& path, const bool createNew) {
    if (createNew) {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) {
            this->file.open(path, std::ios::out);
            this->file.close();
            this->file.open(path, std::ios::in);
            if (!this->file.is_open()) throw std::runtime_error("Failed to create the file.");
        }
    }
    else {
        this->file.open(path, std::ios::in);
        if (!this->file.is_open()) throw std::runtime_error("File cannot be opened or does not exists");
    }
    this->path = path;
}

void Filer::read(std::string& str) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    
    this->mutex.lock();
    this->file.close();
    this->file.open(this->path, std::ios::in);
    std::string temp;
    while (std::getline(this->file, temp)) str += temp + '\n';
    this->mutex.unlock();
}

void Filer::readToList(List<Migrant>& unit) {
    if (!this->file.is_open()) throw std::runtime_error("File does not open now");
    
    this->mutex.lock();
    this->file.close();
    this->file.open(this->path, std::ios::in);
    std::string temp;
    Migrant node;
    while (std::getline(this->file, temp)) {
        node = Migrant();
        this->stringToMigrant(node, temp);
        unit.append(node);
    }
    this->mutex.unlock();
}

void Filer::writeBack(std::string& string) {
    if (!this->file.is_open() || string.empty()) return;
    this->mutex.lock();
    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::app);
    this->file << string << '\n';
    this->file.flush();
    this->mutex.unlock();
}

void Filer::writeBackFromMigrant(const Migrant& unit) {
    if (!this->file.is_open()) return;
    this->mutex.lock();
    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::app);
    this->file << unit.getRegion() << "$$"
               << unit.getRegistrationDate().getDay() << "$$"
               << unit.getRegistrationDate().getMonth() << "$$"
               << unit.getRegistrationDate().getYear() << "$$"
               << unit.getLastName() << "$$"
               << unit.getInitials() << "$$"
               << unit.getNationality() << "$$"
               << unit.getBirthYear() << "$$"
               << unit.getPassport() << "$$"
               << unit.getPurpose() << "$$"
               << unit.getDeregistrationDate().getDay() << "$$"
               << unit.getDeregistrationDate().getMonth() << "$$"
               << unit.getDeregistrationDate().getYear() << '\n';
    this->file.flush();
    this->mutex.unlock();
}

void Filer::rewrite(std::string& string) {
    if (!this->file.is_open() || string.empty()) return;
    this->mutex.lock();
    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::trunc);
    this->file << string << '\n';
    this->file.flush();
    this->mutex.unlock();
}

void Filer::rewriteFromList(const List<Migrant>& unit) {
    if (!this->file.is_open() || unit.length() == 0) return;
    this->mutex.lock();
    this->file.close();
    this->file.open(this->path, std::ios::out | std::ios::trunc);
    for (unsigned int i = 0; i < unit.length(); ++i) {
        this->file << unit[i].getRegion() << "$$"
                   << unit[i].getRegistrationDate().getDay() << "$$"
                   << unit[i].getRegistrationDate().getMonth() << "$$"
                   << unit[i].getRegistrationDate().getYear() << "$$"
                   << unit[i].getLastName() << "$$"
                   << unit[i].getInitials() << "$$"
                   << unit[i].getNationality() << "$$"
                   << unit[i].getBirthYear() << "$$"
                   << unit[i].getPassport() << "$$"
                   << unit[i].getPurpose() << "$$"
                   << unit[i].getDeregistrationDate().getDay() << "$$"
                   << unit[i].getDeregistrationDate().getMonth() << "$$"
                   << unit[i].getDeregistrationDate().getYear() << '\n';
    }
    this->file.flush();
    this->mutex.unlock();
}

void Filer::stringToMigrant(Migrant& unit, const std::string& str) {
    if (str.empty()) return;

    std::string arr[13];
    unsigned short count = 0;
    for (size_t i = 0; i < str.size() && count < 13; ++i) {
        if (i + 1 < str.size() && str[i] == '$' && str[i+1] == '$') {
            ++count;
            ++i;
        } else {
            arr[count].push_back(str[i]);
        }
    }

    unit.setRegion(arr[0]);
    
    Date reg_date, dereg_date;
    try {
        reg_date.setDay(std::stoul(arr[1]));
        reg_date.setMonth(std::stoul(arr[2]));
        reg_date.setYear(std::stoul(arr[3]));
        unit.setRegistrationDate(reg_date);
    } catch(...) {
        reg_date.setDay(1); reg_date.setMonth(1); reg_date.setYear(2000);
        unit.setRegistrationDate(reg_date);
    }
    
    unit.setLastName(arr[4]);
    unit.setInitials(arr[5]);
    unit.setNationality(arr[6]);
    
    try {
        unit.setBirthYear(std::stoul(arr[7]));
    } catch(...) {
        unit.setBirthYear(0);
    }
    
    unit.setPassport(arr[8]);
    unit.setPurpose(arr[9]);
    
    try {
        dereg_date.setDay(std::stoul(arr[10]));
        dereg_date.setMonth(std::stoul(arr[11]));
        dereg_date.setYear(std::stoul(arr[12]));
        unit.setDeregistrationDate(dereg_date);
    } catch(...) {
        dereg_date.setDay(1); dereg_date.setMonth(1); dereg_date.setYear(2000);
        unit.setDeregistrationDate(dereg_date);
    }
}