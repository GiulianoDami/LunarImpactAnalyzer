#ifndef REPORTER_H
#define REPORTER_H

#include <string>
#include <iostream>

class Reporter {
public:
    void generateReport(const std::string& filename);
    void printSummary();
};

#endif // REPORTER_H