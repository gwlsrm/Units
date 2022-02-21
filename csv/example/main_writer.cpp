#include <string>
#include <vector>

#include "../csv_writer.h"

using namespace std;


int main() {
    CsvWriter csv("test.csv");
    csv << 1 << 2.3 << 'a';
    csv << "char*";
    csv << "string"s;
    csv << "string_view"sv;
    csv.endLine();

    csv.writeLine<double>({1.0, 2.4, 3.5}, true);

    return 0;
}