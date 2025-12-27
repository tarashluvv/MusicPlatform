#include "FileManager.h"
#include <sstream>
#include <algorithm>
#include <sys/stat.h>

// Constructor
FileManager::FileManager(const std::string& dataDir) 
    : dataDirectory(dataDir),
      libraryFile(dataDir + "library.txt"),
      playlistDirectory(dataDir + "playlists/") {
    createDirectory(dataDirectory);
    createDirectory(playlistDirectory);
}

// Helper methods
std::string FileManager::trim(const std::string& str) {
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

std::vector<std::string> FileManager::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(trim(token));
    }
    return tokens;
}

// Save Library
bool FileManager::saveLibrary(const Library& library) {
    std::ofstream file(libraryFile);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << libraryFile << std::endl;
        return false;
    }
    
    auto songs = library.getAllSongs();
    file << "# Music Library Data File" << std::endl;
    file << "# Format: Title|Artist|Album|FilePath|Duration|Genre|PlayCount" << std::endl;
    file << std::endl;
    
    for (const auto& song : songs) {
        file << song->getTitle() << "|"
             << song->getArtist() << "|"
             << song->getAlbum() << "|"
             << song->getFilePath() << "|"
             << song->getDuration() << "|"
             << song->getGenre() << "|"
             << song->getPlayCount() << std::endl;
    }
    
    file.close();
    std::cout << "Library saved successfully to " << libraryFile << std::endl;
    return true;
}

// Load Library
bool FileManager::loadLibrary(Library& library) {
    std::ifstream file(libraryFile);
    if (!file.is_open()) {
        std::cout << "No existing library file found. Starting with empty library." << std::endl;
        return false;
    }
    
    std::string line;
    int count = 0;
    
    while (std::getline(file, line)) {
        // Skip comments and empty lines
        if (line.empty() || line[0] == '#') continue;
        
        auto parts = split(line, '|');
        if (parts.size() != 7) {
            std::cerr << "Warning: Invalid line format, skipping: " << line << std::endl;
            continue;
        }
        
        try {
            auto song = std::make_shared<Song>(
                parts[0],                    // title
                parts[1],                    // artist
                parts[2],                    // album
                parts[3],                    // filePath
                std::stoi(parts[4]),        // duration
                parts[5]                     // genre
            );
            
            // Set play count
            for (int i = 0; i < std::stoi(parts[6]); ++i) {
                song->incrementPlayCount();
            }
            
            library.addSong(song);
            count++;
        } catch (const std::exception& e) {
            std::cerr << "Error parsing song: " << e.what() << std::endl;
        }
    }
    
    file.close();
    std::cout << "Loaded " << count << " songs from library" << std::endl;
    return true;
}

// Save Playlist
bool FileManager::savePlaylist(const Playlist& playlist, const std::string& filename) {
    std::string filepath = playlistDirectory + filename + ".txt";
    std::ofstream file(filepath);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file for writing: " << filepath << std::endl;
        return false;
    }
    
    file << "# Playlist: " << playlist.getName() << std::endl;
    file << "# Description: " << playlist.getDescription() << std::endl;
    file << "# Songs: " << playlist.getSongCount() << std::endl;
    file << std::endl;
    
    auto songs = playlist.getSongs();
    for (const auto& song : songs) {
        file << song->getTitle() << "|"
             << song->getArtist() << "|"
             << song->getAlbum() << "|"
             << song->getFilePath() << "|"
             << song->getDuration() << "|"
             << song->getGenre() << std::endl;
    }
    
    file.close();
    std::cout << "Playlist saved: " << filepath << std::endl;
    return true;
}

// Load Playlist
bool FileManager::loadPlaylist(Playlist& playlist, const std::string& filename) {
    std::string filepath = playlistDirectory + filename;
    std::ifstream file(filepath);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open playlist file: " << filepath << std::endl;
        return false;
    }
    
    std::string line;
    std::string name, description;
    
    // Read header information
    while (std::getline(file, line)) {
        if (line.empty()) break;
        
        if (line.find("# Playlist:") != std::string::npos) {
            name = line.substr(12);
            playlist.setName(trim(name));
        } else if (line.find("# Description:") != std::string::npos) {
            description = line.substr(15);
            playlist.setDescription(trim(description));
        }
    }
    
    // Read songs
    int count = 0;
    while (std::getline(file, line)) {
        if (line.empty() || line[0] == '#') continue;
        
        auto parts = split(line, '|');
        if (parts.size() != 6) continue;
        
        try {
            auto song = std::make_shared<Song>(
                parts[0],              // title
                parts[1],              // artist
                parts[2],              // album
                parts[3],              // filePath
                std::stoi(parts[4]),  // duration
                parts[5]               // genre
            );
            
            playlist.addSong(song);
            count++;
        } catch (const std::exception& e) {
            std::cerr << "Error parsing song in playlist: " << e.what() << std::endl;
        }
    }
    
    file.close();
    std::cout << "Loaded playlist with " << count << " songs" << std::endl;
    return true;
}

// Delete Playlist File
bool FileManager::deletePlaylistFile(const std::string& filename) {
    std::string filepath = playlistDirectory + filename + ".txt";
    if (std::remove(filepath.c_str()) == 0) {
        std::cout << "Playlist file deleted: " << filepath << std::endl;
        return true;
    }
    std::cerr << "Error: Could not delete file: " << filepath << std::endl;
    return false;
}

// List Playlist Files
std::vector<std::string> FileManager::listPlaylistFiles() {
    std::vector<std::string> files;
    // Note: This is a simplified version
    // In a real implementation, you'd use platform-specific directory listing
    std::cout << "Note: Directory listing not implemented in this version" << std::endl;
    return files;
}

// Export to CSV
bool FileManager::exportToCSV(const Library& library, const std::string& filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not create CSV file: " << filename << std::endl;
        return false;
    }
    
    // CSV Header
    file << "Title,Artist,Album,Duration,Genre,Play Count" << std::endl;
    
    auto songs = library.getAllSongs();
    for (const auto& song : songs) {
        file << "\"" << song->getTitle() << "\","
             << "\"" << song->getArtist() << "\","
             << "\"" << song->getAlbum() << "\","
             << song->getDuration() << ","
             << "\"" << song->getGenre() << "\","
             << song->getPlayCount() << std::endl;
    }
    
    file.close();
    std::cout << "Library exported to CSV: " << filename << std::endl;
    return true;
}

// Import from CSV
bool FileManager::importFromCSV(Library& library, const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open CSV file: " << filename << std::endl;
        return false;
    }
    
    std::string line;
    std::getline(file, line); // Skip header
    
    int count = 0;
    while (std::getline(file, line)) {
        // Simple CSV parsing (doesn't handle all edge cases)
        auto parts = split(line, ',');
        if (parts.size() < 6) continue;
        
        try {
            // Remove quotes from strings
            for (auto& part : parts) {
                if (!part.empty() && part.front() == '"' && part.back() == '"') {
                    part = part.substr(1, part.length() - 2);
                }
            }
            
            auto song = std::make_shared<Song>(
                parts[0],              // title
                parts[1],              // artist
                parts[2],              // album
                "/music/" + parts[0] + ".mp3",  // generate file path
                std::stoi(parts[3]),  // duration
                parts[4]               // genre
            );
            
            library.addSong(song);
            count++;
        } catch (const std::exception& e) {
            std::cerr << "Error importing song: " << e.what() << std::endl;
        }
    }
    
    file.close();
    std::cout << "Imported " << count << " songs from CSV" << std::endl;
    return true;
}

// Check if file exists
bool FileManager::fileExists(const std::string& filename) {
    std::ifstream file(filename);
    return file.good();
}

// Create directory
bool FileManager::createDirectory(const std::string& path) {
#ifdef _WIN32
    return mkdir(path.c_str()) == 0 || errno == EEXIST;
#else
    return mkdir(path.c_str(), 0755) == 0 || errno == EEXIST;
#endif
}