/*
 * ============================================================
 *  TOPIC: File Handling in C++
 * ============================================================
 *
 * A STREAM is a flow of data.
 *
 * Classes:
 *   istream  — input stream  (cin is an istream object)
 *   ostream  — output stream (cout is an ostream object)
 *   fstream  — file I/O (inherits ifstream + ofstream)
 *   ifstream — input file stream  (read from file)
 *   ofstream — output file stream (write to file)
 *
 * ╔══════════════════════════════════════════════════════════╗
 *  INTERVIEW MUST-KNOW:
 *  Open modes (can be combined with |):
 *    ios::in    — open for reading
 *    ios::out   — open for writing (creates/truncates)
 *    ios::app   — append to end of file
 *    ios::trunc — truncate file on open (default with out)
 *    ios::binary— binary mode (no newline translation)
 *    ios::ate   — seek to end after opening
 *
 *  Always close files after use: fileObj.close()
 *  Check if file opened: if(!file) or file.is_open()
 *
 *  Text vs Binary:
 *    Text   — stores as ASCII; human-readable; more space
 *    Binary — stores raw bytes; machine-readable; compact, faster
 * ╚══════════════════════════════════════════════════════════╝
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip> // for manipulators
using namespace std;

/* ══════════════════════════════════════════════════════════
   1. WRITING TO A TEXT FILE
   ══════════════════════════════════════════════════════════ */

void writeTextFile()
{
    cout << "--- Writing to text file ---\n";

    /* ofstream opens file for writing; creates if doesn't exist */
    ofstream outFile("students.txt");

    if (!outFile)
    {
        cerr << "Error: Could not open file for writing!\n";
        return;
    }

    /* Write using << just like cout */
    outFile << "Name,RollNo,CGPA\n";
    outFile << "Alice,101,9.5\n";
    outFile << "Bob,102,8.7\n";
    outFile << "Charlie,103,9.1\n";

    outFile.close(); // ALWAYS close the file
    cout << "Data written to students.txt\n";
}

/* ══════════════════════════════════════════════════════════
   2. READING FROM A TEXT FILE
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    - getline(file, str) — reads a whole line including spaces.
    - file >> var        — reads word by word (skips whitespace).
    - file.eof()         — true when end of file is reached.
    - Always check is_open() before reading.
   ╚══════════════════════════════════════════════════════════╝
*/

void readTextFile()
{
    cout << "\n--- Reading from text file ---\n";

    ifstream inFile("students.txt");

    if (!inFile.is_open())
    {
        cerr << "Error: File not found!\n";
        return;
    }

    string line;
    while (getline(inFile, line))
    { // read line by line
        cout << line << "\n";
    }

    if (inFile.eof())
    {
        cout << "[End of file reached]\n";
    }

    inFile.close();
}

/* ══════════════════════════════════════════════════════════
   3. APPENDING TO A FILE
   ══════════════════════════════════════════════════════════ */

void appendToFile()
{
    cout << "\n--- Appending to file ---\n";

    /* ios::app — existing content is PRESERVED, new data added at end */
    ofstream outFile("students.txt", ios::app);

    if (!outFile)
    {
        cerr << "Error opening file for append!\n";
        return;
    }

    outFile << "Diana,104,9.8\n";
    outFile << "Eve,105,8.5\n";
    outFile.close();
    cout << "Appended 2 more students.\n";
}

/* ══════════════════════════════════════════════════════════
   4. BINARY FILE — Write & Read
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW MUST-KNOW:
    Binary files store raw bytes — no ASCII conversion.
    - write(reinterpret_cast<char*>(&obj), sizeof(obj))
    - read (reinterpret_cast<char*>(&obj), sizeof(obj))
    Faster than text, less space, but not human-readable.
   ╚══════════════════════════════════════════════════════════╝
*/

struct StudentRecord
{
    char name[50];
    int rollNo;
    double cgpa;
};

void writeBinaryFile()
{
    cout << "\n--- Writing binary file ---\n";

    ofstream outFile("students.bin", ios::binary);
    if (!outFile)
    {
        cerr << "Cannot open binary file!\n";
        return;
    }

    StudentRecord students[] = {
        {"Alice", 101, 9.5},
        {"Bob", 102, 8.7},
        {"Charlie", 103, 9.1}};

    for (const auto &s : students)
    {
        outFile.write(reinterpret_cast<const char *>(&s), sizeof(StudentRecord));
    }

    outFile.close();
    cout << "Binary data written to students.bin\n";
}

void readBinaryFile()
{
    cout << "\n--- Reading binary file ---\n";

    ifstream inFile("students.bin", ios::binary);
    if (!inFile)
    {
        cerr << "Cannot open binary file!\n";
        return;
    }

    StudentRecord s;
    while (inFile.read(reinterpret_cast<char *>(&s), sizeof(StudentRecord)))
    {
        cout << "Name=" << s.name
             << " Roll=" << s.rollNo
             << " CGPA=" << s.cgpa << "\n";
    }

    inFile.close();
}

/* ══════════════════════════════════════════════════════════
   5. SERIALIZATION — Store and retrieve object state
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    Serialization = converting object state → byte stream (to file/network).
    Deserialization = reconstructing object from byte stream.
    In C++: overload << and >> for fstream.
   ╚══════════════════════════════════════════════════════════╝
*/

class Product
{
public:
    string name;
    int id;
    double price;

    Product() : id(0), price(0.0) {} // default ctor needed for deserialization
    Product(string n, int i, double p) : name(n), id(i), price(p) {}

    /* Serialize to text file */
    friend ofstream &operator<<(ofstream &ofs, const Product &p)
    {
        ofs << p.name << "\n"
            << p.id << "\n"
            << p.price << "\n";
        return ofs;
    }

    /* Deserialize from text file */
    friend ifstream &operator>>(ifstream &ifs, Product &p)
    {
        ifs >> p.name >> p.id >> p.price;
        return ifs;
    }

    void display() const
    {
        cout << "Product(id=" << id << ", name=" << name
             << ", price=$" << price << ")\n";
    }
};

void serializeDemo()
{
    cout << "\n--- Serialization (Object → File → Object) ---\n";

    /* Write objects to file */
    ofstream out("products.txt");
    Product p1("Laptop", 1001, 999.99);
    Product p2("Phone", 1002, 499.50);
    Product p3("Headphones", 1003, 149.99);
    out << p1 << p2 << p3;
    out.close();
    cout << "Products serialized.\n";

    /* Read objects back */
    ifstream in("products.txt");
    Product loaded;
    cout << "Deserialized:\n";
    while (in >> loaded)
    {
        loaded.display();
    }
    in.close();
}

/* ══════════════════════════════════════════════════════════
   6. I/O MANIPULATORS
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    Manipulators format the output stream WITHOUT changing values.
    Common ones (from <iomanip> and <iostream>):
      setw(n)         — set field width (right-aligned by default)
      setfill(c)      — fill character for padding
      left / right    — alignment
      setprecision(n) — decimal places
      fixed / scientific — floating point notation
      hex / oct / dec — integer base
      boolalpha       — print true/false instead of 1/0
      endl            — newline + flush
   ╚══════════════════════════════════════════════════════════╝
*/

void demonstrateManipulators()
{
    cout << "\n--- I/O Manipulators ---\n";

    /* Integer bases */
    int n = 255;
    cout << "Decimal: " << dec << n << "\n";
    cout << "Hex:     " << hex << n << "\n";
    cout << "Octal:   " << oct << n << "\n";
    cout << dec; // reset to decimal

    /* Floating point */
    double pi = 3.14159265358979;
    cout << "\nfixed:      " << fixed << setprecision(4) << pi << "\n";
    cout << "scientific: " << scientific << setprecision(4) << pi << "\n";
    cout << fixed << setprecision(2); // restore

    /* Field width & alignment */
    cout << "\nFormatted table:\n";
    cout << left;
    cout << setw(15) << "Product"
         << setw(8) << "ID"
         << setw(10) << "Price" << "\n";
    cout << string(33, '-') << "\n";
    cout << setw(15) << "Laptop"
         << setw(8) << 1001
         << "$" << setw(9) << 999.99 << "\n";
    cout << setw(15) << "Phone"
         << setw(8) << 1002
         << "$" << setw(9) << 499.50 << "\n";

    /* Fill character */
    cout << "\nWith fill:\n";
    cout << setfill('*') << setw(20) << right << "Hello" << "\n";
    cout << setfill(' '); // reset fill

    /* Bool alpha */
    cout << "\nboolalpha: " << boolalpha << true << " " << false << "\n";
    cout << noboolalpha;
}

/* ══════════════════════════════════════════════════════════
   7. STRING STREAM (in-memory file)
   ══════════════════════════════════════════════════════════

   ╔══════════════════════════════════════════════════════════╗
    INTERVIEW TIP:
    stringstream is like a file but in memory.
    Great for:
    - Converting int/double to string (int → string)
    - Parsing strings
    - Building strings without string concatenation overhead
   ╚══════════════════════════════════════════════════════════╝
*/

void stringstreamDemo()
{
    cout << "\n--- stringstream (in-memory I/O) ---\n";

    /* int → string */
    ostringstream oss;
    oss << "ID: " << 42 << " Price: " << fixed << setprecision(2) << 9.99;
    string result = oss.str();
    cout << "Built string: " << result << "\n";

    /* string → int/double parsing */
    string data = "100 3.14 hello";
    istringstream iss(data);
    int intVal;
    double dblVal;
    string strVal;
    iss >> intVal >> dblVal >> strVal;
    cout << "Parsed: int=" << intVal
         << " double=" << dblVal
         << " string=" << strVal << "\n";
}

/* ══════════════════════════════════════════════════════════
   MAIN
   ══════════════════════════════════════════════════════════ */
int main()
{
    cout << "===== File Handling in C++ =====\n\n";

    writeTextFile();
    readTextFile();
    appendToFile();
    readTextFile(); // read again to see appended content

    writeBinaryFile();
    readBinaryFile();

    serializeDemo();
    demonstrateManipulators();
    stringstreamDemo();

    return 0;
}
