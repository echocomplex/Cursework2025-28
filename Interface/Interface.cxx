#include "Interface.hxx"

void Interface::clearInputBuffer(void) {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

Date Interface::getDateFromUser(const std::string& prompt) {
    unsigned short day, month, year;
    std::cout << prompt << " (day month year): ";
    std::cin >> day >> month >> year;
    this->clearInputBuffer();
    return Date(day, month, year);
}

void Interface::getMigrant(Migrant& unit) {
    std::string temp;
    unsigned short temp_year;

    std::cout << "Enter the Region: ";
    std::getline(std::cin, temp);
    unit.setRegion(temp);
    
    Date regDate = getDateFromUser("Enter the Registration Date");
    unit.setRegistrationDate(regDate);
    
    std::cout << "Enter the Last Name: ";
    std::getline(std::cin, temp);
    unit.setLastName(temp);
    
    std::cout << "Enter the Initials: ";
    std::getline(std::cin, temp);
    unit.setInitials(temp);
    
    std::cout << "Enter the Nationality: ";
    std::getline(std::cin, temp);
    unit.setNationality(temp);
    
    std::cout << "Enter the Birth Year: ";
    std::cin >> temp_year;
    this->clearInputBuffer();
    unit.setBirthYear(temp_year);
    
    std::cout << "Enter the Passport Number: ";
    std::getline(std::cin, temp);
    unit.setPassport(temp);
    
    std::cout << "Enter the Purpose: ";
    std::getline(std::cin, temp);
    unit.setPurpose(temp);
    
    Date deregDate = getDateFromUser("Enter the Deregistration Date (1 1 2000 for active)");
    unit.setDeregistrationDate(deregDate);
}

int Interface::removeMigrant(void) {
    int number;
    while (true) {
        std::cout << "Enter Migrant number to delete (1-" << this->unit.size() << "): ";
        
        if (!(std::cin >> number)) {
            std::cin.clear();
            this->clearInputBuffer();
            std::cerr << "Error: Please enter a number\n\n";
            continue;
        }

        if (number > 0 && number <= this->unit.size()) {
            return number - 1;
        }
        
        std::cerr << "Error: Number must be between 1 and " << this->unit.size() << "\n\n";
    }
}

void Interface::displayMenu(void) {
    std::cout << "\n\n=== Migrant Database Menu ===" << std::endl;
    std::cout << "1. Display all records" << std::endl;
    std::cout << "2. Add new Migrant" << std::endl;
    std::cout << "3. Remove Migrant" << std::endl;
    std::cout << "4. Display Active Migrants" << std::endl;
    std::cout << "5. Display Regions Statistics by Nationality" << std::endl;
    std::cout << "6. Count Departed Migrants by Region and Period" << std::endl;
    std::cout << "7. Exit program" << std::endl;
    std::cout << "Enter your choice (1-7): ";
}

void Interface::pool(void) {
    short choice = 0;
    std::string temp;
    List<Migrant> collected;
    Migrant new_Migrant;
    Date startDate, endDate;
    
    while (true) {
        this->displayMenu();

        while (!(std::cin >> choice) || choice < 1 || choice > 7) {
            std::cout << "Invalid input. Please enter 1-7: ";
            this->clearInputBuffer();
        }

        this->clearInputBuffer();

        switch (choice) {
            case 1:
                std::cout << "\n[Displaying all records]\n";
                std::cout << this->unit << std::endl;
                break;
            case 2:
                std::cout << "\n[Adding new Migrant]\n";
                this->getMigrant(new_Migrant);
                this->unit.append(new_Migrant);
                break;
            case 3:
                std::cout << "\n[Removing Migrant]\n";
                this->unit.remove(this->removeMigrant());
                break;
            case 4: 
                std::cout << "\n[Displaying Active Migrants]\n";
                this->unit.getActiveMigrants(collected);
                for (int i = 0; i < collected.length(); ++i) 
                    std::cout << collected[i] << std::endl;
                collected.clear();
                break;
            case 5:
                std::cout << "\n[Displaying Regions Statistics by Nationality]\n";
                {
                    std::vector<std::pair<std::string, std::map<std::string, int>>> regionsStats;
                    this->unit.getRegionsByNationality(regionsStats);
                    for (const auto& region : regionsStats) {
                        std::cout << "\nRegion: " << region.first << std::endl;
                        for (const auto& nat : region.second) {
                            std::cout << "  " << nat.first << ": " << nat.second << std::endl;
                        }
                    }
                }
                break;
            case 6:
                std::cout << "\n[Count Departed Migrants by Region and Period]\n";
                std::cout << "Enter Region: ";
                std::getline(std::cin, temp);
                
                startDate = getDateFromUser("Enter Start Date");
                endDate = getDateFromUser("Enter End Date");
                
                std::cout << "Departed migrants count: " 
                         << this->unit.countDepartedMigrants(temp, startDate, endDate) 
                         << std::endl;
                break;
            case 7:
                std::cout << "\nExiting program...\n";
                return;
        }

        std::cout << "\nOperation completed. Press Enter to continue...";
        this->clearInputBuffer();
    }
}