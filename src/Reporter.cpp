#include "Reporter.h"
#include <iostream>
#include <fstream>
#include <iomanip>

void Reporter::generateReport(const std::vector<ImpactEvent>& events, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
        return;
    }

    file << "Lunar Impact Event Analysis Report\n";
    file << "==================================\n\n";

    for (const auto& event : events) {
        file << "Event ID: " << event.id << "\n";
        file << "Date: " << event.date << "\n";
        file << "Location: (" << std::fixed << std::setprecision(2) 
             << event.location.x << ", " << event.location.y << ")\n";
        file << "Impact Energy: " << std::scientific << std::setprecision(2) 
             << event.energy << " Joules\n";
        file << "Volatile Depletion: " << std::fixed << std::setprecision(2) 
             << event.volatileDepletion * 100 << "%\n";
        file << "Chemical Signature: " << event.signature << "\n";
        file << "Confidence Level: " << std::fixed << std::setprecision(1) 
             << event.confidence * 100 << "%\n";
        file << "----------------------------------------\n";
    }

    file.close();
    std::cout << "Report generated successfully: " << filename << std::endl;
}