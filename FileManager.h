#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Song.h"
#include "Playlist.h"
#include "Library.h"
#include <string>
#include <vector>
#include <memory>
#include <fstream>

class FileManager {
private:
    std::string dataDirectory;
    std::string libraryFile;
    std::string playlistDirectory;
    
    // Helper methods for parsing
    std::string trim(const std::string& str);
    std::vector<std::string> split(const std::string& str, char delimiter);
    
public:
    // Constructor
    FileManager(const std::string& dataDir = "data/");
    
    // Library operations
    bool saveLibrary(const Library& library);
    bool loadLibrary(Library& library);
    
    // Playlist operations
    bool savePlaylist(const Playlist& playlist, const std::string& filename);
    bool loadPlaylist(Playlist& playlist, const std::string& filename);
    bool deletePlaylistFile(const std::string& filename);
    std::vector<std::string> listPlaylistFiles();
    
    // Export/Import
    bool exportToCSV(const Library& library, const std::string& filename);
    bool importFromCSV(Library& library, const std::string& filename);
    
    // Utility
    bool fileExists(const std::string& filename);
    bool createDirectory(const std::string& path);
};

#endif // FILEMANAGER_H