#include <string>
#include <chrono>
#include <iostream>

#include <google/profiler.h>

#include "Common/Files.h"
#include "FBXFileLoader.h"

using namespace std;

int main(const int argc, const char **argv) {
    if (argc < 2) {
        cout << "must provide a file path to load" << endl;
        return 1;
    }

    string file_path = argv[1];

    ModelFileLoaderPtr loader = ModelFileLoader::CreateLoader(file_path);
    if (!loader) {
        cout << "cannot load file: " << file_path << endl;
        return 1;
    }

    ProfilerStart("model_loader.prof");
    loader->Load(file_path);
    ProfilerStop();
    return 0;
}
