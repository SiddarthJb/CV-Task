#include <iostream>
#include <map>
#include <fstream>

class File{

    std::string _file;

    public:
        void loadFile(std::string filePath){
            _file = filePath;            
        }

        std::map<std::string,int> countWords(){
            
            std::ifstream in(_file);

            if(!in)
                exit(EXIT_FAILURE);

            std::map<std::string, int> words;
            std::string word;

            while (in>>word){
                ++words[word];
            }

            return words;
        }
};

int main() {
    File file;

    file.loadFile("../sample_text.txt");

    std::map<std::string, int> words;

    words = file.countWords();
    for (std::map<std::string, int>::iterator p = words.begin();p != words.end(); ++p) {
        std::cout << p->first <<" "<< p->second << "\n";
    }
}
