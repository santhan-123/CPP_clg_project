#include <iostream>
#include <string>
#include <chrono>

const int MAX_PARKING_SLOTS = 10;
const double HOURLY_RATE = 5.0; // Adjust the hourly rate as needed

class ParkingSystem {
private:
    struct ParkingRecord {
        std::string regNumber;
        std::chrono::time_point<std::chrono::system_clock> entryTime;
    };

    ParkingRecord parkingSlots[MAX_PARKING_SLOTS];
    int availableSlots;

public:
    ParkingSystem() : availableSlots(MAX_PARKING_SLOTS) {
        for (int i = 0; i < MAX_PARKING_SLOTS; ++i) {
            parkingSlots[i].regNumber = "";  // Initialize all slots as empty
        }
    }

    void parkCar() {
        if (availableSlots > 0) {
            std::cout << "Enter car registration number: ";
            std::string regNumber;
            std::cin >> regNumber;

            for (int i = 0; i < MAX_PARKING_SLOTS; ++i) {
                if (parkingSlots[i].regNumber == "") {
                    parkingSlots[i].regNumber = regNumber;
                    parkingSlots[i].entryTime = std::chrono::system_clock::now();
                    availableSlots--;
                    std::cout << "Car parked at slot " << i + 1 << std::endl;
                    return;
                }
            }
        } else {
            std::cout << "Parking is full. No available slots." << std::endl;
        }
    }

    void retrieveCar() {
        std::cout << "Enter slot number to retrieve the car: ";
        int slotNumber;
        std::cin >> slotNumber;

        if (slotNumber >= 1 && slotNumber <= MAX_PARKING_SLOTS) {
            if (parkingSlots[slotNumber - 1].regNumber != "") {
                std::chrono::time_point<std::chrono::system_clock> exitTime = std::chrono::system_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::minutes>(exitTime - parkingSlots[slotNumber - 1].entryTime);
                double parkingFee = HOURLY_RATE * (duration.count() / 60.0);

                std::cout << "Car with registration number " << parkingSlots[slotNumber - 1].regNumber
                          << " retrieved from slot " << slotNumber << std::endl;
                std::cout << "Parking fee: $" << parkingFee << std::endl;

                parkingSlots[slotNumber - 1].regNumber = "";
                availableSlots++;
            } else {
                std::cout << "No car found at slot " << slotNumber << std::endl;
            }
        } else {
            std::cout << "Invalid slot number. Please enter a valid slot number." << std::endl;
        }
    }

    void displayParkingStatus() {
        std::cout << "Parking Status:" << std::endl;
        for (int i = 0; i < MAX_PARKING_SLOTS; ++i) {
            std::cout << "Slot " << i + 1 << ": ";
            if (parkingSlots[i].regNumber != "") {
                std::cout << parkingSlots[i].regNumber;
            } else {
                std::cout << "Empty";
            }
            std::cout << std::endl;
        }
    }
};

int main() {
    ParkingSystem parkingLot;

    int choice;
    do {
        std::cout << "\nMenu:\n1. Park Car\n2. Retrieve Car\n3. Display Parking Status\n4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                parkingLot.parkCar();
                break;
            case 2:
                parkingLot.retrieveCar();
                break;
            case 3:
                parkingLot.displayParkingStatus();
                break;
            case 4:
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please enter a valid option.\n";
        }
    } while (choice != 4);

    return 0;
}

