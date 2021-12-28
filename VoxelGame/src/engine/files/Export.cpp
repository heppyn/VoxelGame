#include "Export.h"

#include <iostream>

#include "helpers/Print.h"

void Engine::Files::Export::ExportScene(const Scene& scene, const std::string& fileName) {
    std::ofstream fs(fileName);

    if (!fs.is_open()) {
        std::cout << "Can't open output file " << fileName << '\n';
        return;
    }

    fs << "{\"chunks\":[";

    for (const auto& [_, chunk] : scene.GetChunks()) {
        ExportChunk(fs, chunk);
        fs << ',';
    }

    // delete ','
    fs.seekp(-1, std::ios_base::end);
    fs << "]}";
    fs.close();
}

void Engine::Files::Export::ExportChunk(std::ofstream& stream, const Chunk& chunk) {
    stream << "{\"pos\":[" << chunk.Position.x << ',' << chunk.Position.y << "],";
    stream << "\"meta\":[";

    for (const auto& vec : chunk.GetBlockInfos()) {
        for (const auto& bi : vec) {
            stream << Helpers::ToJson(bi) << ',';
        }
    }

    // delete ','
    stream.seekp(-1, std::ios_base::end);
    stream << "],\"objects\":[";

    for (const auto data = chunk.GetInstancesData();
         const auto& model : *data) {
        stream << Helpers::PackedMatToString(model) << ',';
    }
    for (const auto data = chunk.GetInstancesDataTrans();
         const auto& model : *data) {
        stream << Helpers::PackedMatToString(model) << ',';
    }

    // delete ','
    stream.seekp(-1, std::ios_base::end);
    stream << "]}";
}
