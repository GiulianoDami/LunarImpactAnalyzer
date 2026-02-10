#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <vector>
#include <string>
#include <map>

class DataProcessor {
public:
    // Process raw lunar sample data
    std::map<std::string, double> processSampleData(const std::vector<double>& rawData);
    
    // Detect impact signatures in compositional data
    bool detectImpactSignature(const std::map<std::string, double>& composition);
    
    // Calculate volatile depletion ratio
    double calculateVolatileDepletion(const std::map<std::string, double>& composition);
    
    // Identify anomalous element ratios
    std::vector<std::string> identifyAnomalies(const std::map<std::string, double>& composition);

private:
    // Helper method to validate data ranges
    bool isValidComposition(const std::map<std::string, double>& composition);
};

#endif // DATAPROCESSOR_H