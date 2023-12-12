#include <iostream>
#include <fstream>

using namespace std;

struct PlayerData {
    string name;
    int score;
    PlayerData(string nm = "", int scr = 0) {
        name = nm;
        score = scr;
    }
};
class HighScore {
    PlayerData* data;
    int size;
    fstream file;
public:
    HighScore() {
        file.open("Highscore.txt", ios::in);
        string teststring;
        size = 0;
        while (file.peek() != EOF) {
            getline(file, teststring);
            size++;
        }
        file.close();
        if (size != 0) {
            data = new PlayerData[size];
            file.open("Highscore.txt", ios::in);
            int i = 0;
            while (file.peek() != EOF) {
                file >> data[i].name >> data[i].score;
                i++;
            }
            file.close();
        }
        else
            cout << "No file was there so new created\n";

    }
    void addPlayer(string name, int score) {
        if (size == 0) {
            data = new PlayerData(name, score);
            size = 1;
        }
        else {
            bool found = false;
            for (int i = 0; i < score; i++) {
                if (data[i].name == name) {
                    if (data[i].score < score)
                        data[i].score = score;
                    found = true;
                    break;
                }
            }
            if (!found) {
                PlayerData* temp = new PlayerData[size + 1];
                for (int i = 0; i < size; i++)
                    temp[i] = data[i];
                temp[size].name = name;
                temp[size].score = score;
                size++;
                data = temp;
            }
        }
        //sorting with score
        for (int i = 0; i < size; i++) {
            bool swapped = false;
            for (int j = 0; j < size - 1 - i; j++) {
                if (data[j].score < data[j + 1].score) {
                    swap(data[j], data[j + 1]);
                    swapped = true;
                }
            }
            if (!swapped)
                break;
        }
        file.open("Highscore.txt", ios::out);
        for (int i = 0; i < size; i++) {
            file << data[i].name << '\t' << data[i].score;
            if (i != size - 1)
                file << '\n';
        }
        file.close();
    }
};


// int main(){
//     HighScore h;
//     h.addPlayer("Hassan", 120);
// }