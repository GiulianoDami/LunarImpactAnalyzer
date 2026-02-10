#ifndef LUNAR_IMPACT_ANALYZER_H
#define LUNAR_IMPACT_ANALYZER_H

#include <vector>
#include <string>
#include <map>

class LunarImpactAnalyzer {
private:
    std::vector<std::map<std::string, double>> sample_data;
    
public:
    LunarImpactAnalyzer();
    ~LunarImpactAnalyzer();
    
    void load_sample_data(const std::vector<std::map<std::string, double>>& samples);
    std::vector<std::string> detect_impact_signatures(double threshold = 0.5);
    std::map<std::string, double> analyze_compositional_anomalies();
    bool validate_sample_composition(const std::map<std::string, double>& sample);
};

#endif // LUNAR_IMPACT_ANALYZER_H