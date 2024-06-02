#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Train 
{
public:
    int number;
    string departureTime;
    string destination;

    Train(int num, string time, string dest): number(num), departureTime(time), destination(dest) {}

    friend ostream& operator<<(ostream& os, const Train& train);
    friend istream& operator>>(istream& is, Train& train);
};
ostream& operator<<(ostream& os, const Train& train)
{
    os << train.number << " " << train.departureTime << " " << train.destination;
    return os;
}
istream& operator>>(istream& is, Train& train)
{
    is >> train.number >> train.departureTime >> train.destination;
    return is;
}
class TrainStation 
{
private:
    vector<Train> trains;
public:
    void addTrain(const Train& train)
    {
        trains.push_back(train);
    }

    void displayAllTrains() const 
    {
        for (const auto& train : trains) 
        {
            cout << train << endl;
        }
    }

    void displayTrainByNumber(int number) const
    {
        for (const auto& train : trains)
        {
            if (train.number == number)
            {
                cout << train << endl;
                return;
            }
        }
        cout << "Train with number " << number << " not found." << endl;
    }
    void editTrainTime(int number, const string& newTime) 
    {
        for (auto& train : trains)
        {
            if (train.number == number) 
            {
                train.departureTime = newTime;
                return;
            }
        }
        cout << "Train with number " << number << " not found." << endl;
    }
    void sortTrainsByDepartureTime() 
    {
        for (size_t i = 0; i < trains.size(); ++i) 
        {
            for (size_t j = 0; j < trains.size() - 1; ++j) 
            {
                if (trains[j].departureTime > trains[j + 1].departureTime)
                {
                    swap(trains[j], trains[j + 1]);
                }
            }
        }
    }
    void displayTrainsByDestination(const string& destination) const 
    {
        for (const auto& train : trains) 
        {
            if (train.destination == destination)
            {
                cout << train << endl;
            }
        }
    }
    void saveToFile(const string& filename) const 
    {
        ofstream outFile(filename);
        if (outFile.is_open())
        {
            for (const auto& train : trains)
            {
                outFile << train << endl;
            }
            outFile.close();
        }
        else
        {
            cout << "Unable to open file for writing." << endl;
        }
    }
    void loadFromFile(const string& filename) 
    {
        ifstream inFile(filename);
        if (inFile.is_open())
        {
            trains.clear();
            Train train(0, "", "");
            while (inFile >> train)
            {
                trains.push_back(train);
            }
            inFile.close();
        }
        else
        {
            cout << "Unable to open file for reading." << endl;
        }
    }
};
int main() 
{
    TrainStation station;
    int choice;
    while (true) 
    {
        cout << "1. Add train\n"
            << "2. Display all trains\n"
            << "3. Display train by number\n"
            << "4. Edit train departure time\n"
            << "5. Sort trains by departure time\n"
            << "6. Display trains by destination\n"
            << "7. Save to file\n"
            << "8. Load from file\n"
            << "9. Exit\n"
            << "Enter your choice: ";
        cin >> choice;
        if (choice == 9)
            break;
        int number;
        string time, destination, filename;
        switch (choice) {
        case 1:
            cout << "Enter train number, departure time and destination: ";
            cin >> number >> time >> destination;
            station.addTrain(Train(number, time, destination));
            break;
        case 2:
            station.displayAllTrains();
            break;
        case 3:
            cout << "Enter train number: ";
            cin >> number;
            station.displayTrainByNumber(number);
            break;
        case 4:
            cout << "Enter train number and new departure time: ";
            cin >> number >> time;
            station.editTrainTime(number, time);
            break;
        case 5:
            station.sortTrainsByDepartureTime();
            break;
        case 6:
            cout << "Enter destination: ";
            cin >> destination;
            station.displayTrainsByDestination(destination);
            break;
        case 7:
            cout << "Enter filename: ";
            cin >> filename;
            station.saveToFile(filename);
            break;
        case 8:
            cout << "Enter filename: ";
            cin >> filename;
            station.loadFromFile(filename);
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }
}