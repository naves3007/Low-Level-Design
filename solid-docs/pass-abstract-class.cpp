#include <bits/stdc++.h>
using namespace std;

// class FileManager{
// public:
//     string fileName;
//     vector<string> data;

//     FileManager(const string &fileName) : fileName(fileName) {}

//     void read(){
//         cout << "Reading data from file: " << fileName << "\n"; 
//     }
//     void write(const vector<string> &data){
//         cout << "Writing data to file: " << fileName << "\n"; 
//     }
//     void processCSV(){
//         cout << "Processing CSV data from file: " << fileName << "\n"; 
//     }
//     void processJSON(){
//         cout << "Processing JSON data from file: " << fileName << "\n"; 
//     }
// }

// void handleFiles(FileManager &fileManager){
//     fileManager.read();
//     fileManager.write({"Sample data"});
//     fileManager.processCSV();
//     fileManager.processJSON();
// }

// int main(){
//     FileManager fileManager("data.csv");
//     handleFiles(&fileManager);

//     return 0;
// }

class AbstractReader{
    public:
    virtual void read(const string &fileName) = 0;
}
class AbstractWriter{
    public:
    virtual void write(const string &fileName, const vector<string> &data) = 0;
}
class AbstractCSVProcessor{
    public:
    virtual void processCSV(const string &fileName) = 0;
}
class JSONProcessor{
    public:
    virtual void processJSON(const string &fileName) = 0;
}

class Reader : public AbstractReader{
    public:
    Reader (const string &fileName)  : fileName(fileName) {}
    void read(const string &fileName) override {
        cout << "Reading data from file: " << fileName << "\n"; 
    }
}
class Writer : public AbstractWriter{
    public:
    Writer (const string &fileName)  : fileName(fileName) {}
    void write(const string &fileName, const vector<string> &data) override {
        cout << "Writing data to file: " << fileName << "\n"; 
    }
}
class CSVProcessor : public AbstractCSVProcessor{
    public:
    CSVProcessor (const string &fileName)  : fileName(fileName) {}
    void processCSV(const string &fileName) override {
        cout << "Processing CSV data from file: " << fileName << "\n"; 
    }
}
class JSONProcessor : public AbstractJSONProcessor{
    public:
    JSONProcessor (const string &fileName)  : fileName(fileName) {}
    void processJSON(const string &fileName) override {
        cout << "Processing JSON data from file: " << fileName << "\n"; 
    }
}

void handleFiles(AbstractReader &reader, AbstractWriter &writer, AbstractCSVProcessor &csvProcessor, AbstractJSONProcessor &jsonProcessor){
    reader.read("data.csv");
    writer.write("data.csv", {"Sample data"});
    csvProcessor.processCSV("data.csv");
    jsonProcessor.processJSON("data.json");
}

int main(){
    Reader reader("data.csv");
    Writer writer("data.csv");
    CSVProcessor csvProcessor("data.csv");
    JSONProcessor jsonProcessor("data.json");

    handleFiles(reader, writer, csvProcessor, jsonProcessor);

    return 0;
}
