#include "DataProcessor.h"
#include <algorithm>
#include <cmath>
#include <numeric>

namespace LunarImpactAnalyzer {

std::vector<double> DataProcessor::normalizeData(const std::vector<double>& data) {
    if (data.empty()) return {};
    
    double mean = std::accumulate(data.begin(), data.end(), 0.0) / data.size();
    double variance = std::accumulate(data.begin(), data.end(), 0.0,
        [mean](double acc, double x) { return acc + (x - mean) * (x - mean); }) / data.size();
    double stddev = std::sqrt(variance);
    
    if (stddev == 0) return std::vector<double>(data.size(), 0.0);
    
    std::vector<double> normalized(data.size());
    std::transform(data.begin(), data.end(), normalized.begin(),
        [mean, stddev](double x) { return (x - mean) / stddev; });
    
    return normalized;
}

std::vector<double> DataProcessor::detectAnomalies(const std::vector<double>& data, double threshold) {
    auto normalized = normalizeData(data);
    std::vector<double> anomalies;
    
    for (size_t i = 0; i < normalized.size(); ++i) {
        if (std::abs(normalized[i]) > threshold) {
            anomalies.push_back(data[i]);
        }
    }
    
    return anomalies;
}

std::vector<std::pair<size_t, double>> DataProcessor::findPeaks(const std::vector<double>& data, 
                                                                size_t windowSize) {
    std::vector<std::pair<size_t, double>> peaks;
    
    if (data.empty() || windowSize == 0) return peaks;
    
    size_t halfWindow = windowSize / 2;
    
    for (size_t i = halfWindow; i < data.size() - halfWindow; ++i) {
        bool isPeak = true;
        double currentValue = data[i];
        
        for (size_t j = i - halfWindow; j <= i + halfWindow; ++j) {
            if (j != i && data[j] >= currentValue) {
                isPeak = false;
                break;
            }
        }
        
        if (isPeak) {
            peaks.emplace_back(i, currentValue);
        }
    }
    
    return peaks;
}

} // namespace LunarImpactAnalyzer