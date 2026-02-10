#include "Analyzer.h"
#include <algorithm>
#include <cmath>
#include <numeric>

LunarImpactAnalyzer::LunarImpactAnalyzer(const std::vector<Sample>& samples) : samples_(samples) {}

std::vector<ImpactEvent> LunarImpactAnalyzer::detectImpactEvents() {
    std::vector<ImpactEvent> events;
    
    for (size_t i = 0; i < samples_.size(); ++i) {
        const Sample& sample = samples_[i];
        
        // Check for volatile depletion
        bool hasVolatileDepletion = checkVolatileDepletion(sample);
        
        // Check for anomalous isotope ratios
        bool hasAnomalousRatios = checkAnomalousIsotopeRatios(sample);
        
        // Check for elevated temperature signatures
        bool hasHighTempSignature = checkHighTemperatureSignature(sample);
        
        if (hasVolatileDepletion || hasAnomalousRatios || hasHighTempSignature) {
            ImpactEvent event;
            event.sample_id = i;
            event.timestamp = sample.timestamp;
            event.location = sample.location;
            
            if (hasVolatileDepletion) event.signatures.push_back("volatile_depletion");
            if (hasAnomalousRatios) event.signatures.push_back("anomalous_isotopes");
            if (hasHighTempSignature) event.signatures.push_back("high_temperature");
            
            events.push_back(event);
        }
    }
    
    return events;
}

bool LunarImpactAnalyzer::checkVolatileDepletion(const Sample& sample) {
    // Look for depletion in volatile elements like H, He, Li, Na, K
    static const std::vector<std::string> volatile_elements = {"H", "He", "Li", "Na", "K"};
    
    for (const auto& element : volatile_elements) {
        auto it = sample.composition.find(element);
        if (it != sample.composition.end()) {
            // If concentration is below threshold, consider depleted
            if (it->second < VOLATILE_DEPLETION_THRESHOLD) {
                return true;
            }
        }
    }
    
    return false;
}

bool LunarImpactAnalyzer::checkAnomalousIsotopeRatios(const Sample& sample) {
    // Check for abnormal ratios of isotopes that indicate high-energy events
    // Example: abnormal 18O/16O or 17O/16O ratios
    auto o16_it = sample.composition.find("16O");
    auto o17_it = sample.composition.find("17O");
    auto o18_it = sample.composition.find("18O");
    
    if (o16_it != sample.composition.end() && 
        o17_it != sample.composition.end() && 
        o18_it != sample.composition.end()) {
        
        double ratio_18_16 = o18_it->second / o16_it->second;
        double ratio_17_16 = o17_it->second / o16_it->second;
        
        // Check if ratios are outside normal range
        if (ratio_18_16 > ANOMALOUS_RATIO_THRESHOLD || 
            ratio_17_16 > ANOMALOUS_RATIO_THRESHOLD) {
            return true;
        }
    }
    
    return false;
}

bool LunarImpactAnalyzer::checkHighTemperatureSignature(const Sample& sample) {
    // Look for evidence of extreme heating (e.g., high Fe/Mg ratios)
    auto fe_it = sample.composition.find("Fe");
    auto mg_it = sample.composition.find("Mg");
    
    if (fe_it != sample.composition.end() && mg_it != sample.composition.end()) {
        double fe_mg_ratio = fe_it->second / mg_it->second;
        
        // High Fe/Mg ratio can indicate melting/degassing from impact
        if (fe_mg_ratio > HIGH_TEMP_THRESHOLD) {
            return true;
        }
    }
    
    return false;
}

std::vector<double> LunarImpactAnalyzer::calculateImpactParameters(const Sample& sample) {
    std::vector<double> parameters;
    
    // Calculate energy required to produce observed depletion
    double energy_estimate = calculateEnergyEstimate(sample);
    parameters.push_back(energy_estimate);
    
    // Calculate impactor size estimate
    double size_estimate = calculateImpactorSize(sample);
    parameters.push_back(size_estimate);
    
    // Calculate depth of impact effect
    double depth_estimate = calculateImpactDepth(sample);
    parameters.push_back(depth_estimate);
    
    return parameters;
}

double LunarImpactAnalyzer::calculateEnergyEstimate(const Sample& sample) {
    // Simplified model: energy proportional to volatile depletion and temperature anomaly
    double depletion_factor = 0.0;
    double temp_factor = 0.0;
    
    // Volatile depletion factor
    static const std::vector<std::string> volatile_elements = {"H", "He", "Li", "Na", "K"};
    for (const auto& element : volatile_elements) {
        auto it = sample.composition.find(element);
        if (it != sample.composition.end()) {
            depletion_factor += std::max(0.0, VOLATILE_DEPLETION_THRESHOLD - it->second);
        }
    }
    
    // Temperature factor
    auto fe_it = sample.composition.find("Fe");
    auto mg_it = sample.composition.find("Mg");
    if (fe_it != sample.composition.end() && mg_it != sample.composition.end()) {
        temp_factor = std::max(0.0, (fe_it->second / mg_it->second) - HIGH_TEMP_THRESHOLD);
    }
    
    // Simple linear combination
    return ENERGY_CONSTANT * (depletion_factor + temp_factor);
}

double LunarImpactAnalyzer::calculateImpactorSize(const Sample& sample) {
    // Estimate based on energy requirement
    double energy = calculateEnergyEstimate(sample);
    // Using simplified relationship E = k * D^3 where D is diameter
    return std::pow(energy / IMPACTOR_SIZE_CONSTANT, 1.0/3.0);
}

double LunarImpactAnalyzer::calculateImpactDepth(const Sample& sample) {
    // Estimate based on volatile depletion and temperature
    double depletion_factor = 0.0;
    double temp_factor = 0.0;
    
    static const std::vector<std::string> volatile_elements = {"H", "He", "Li", "Na", "K"};
    for (const auto& element : volatile_elements) {
        auto it = sample.composition.find(element);
        if (it != sample.composition.end()) {
            depletion_factor += std::max(0.0, VOLATILE_DEPLETION_THRESHOLD - it->second);
        }
    }
    
    auto fe_it = sample.composition.find("Fe");
    auto mg_it = sample.composition.find("Mg");
    if (fe_it != sample.composition.end() && mg_it != sample.composition.end()) {
        temp_factor = std::max(0.0, (fe_it->second / mg_it->second) - HIGH_TEMP_THRESHOLD);
    }
    
    return DEPTH_CONSTANT * (depletion_factor + temp_factor);
}