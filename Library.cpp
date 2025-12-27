#include "Library.h"
#include <iostream>
#include <algorithm>

// Constructor
Library::Library() {
    std::cout << "Music Library initialized" << std::endl;
}

// Destructor
Library::~Library() {
    allSongs.clear();
    playlists.clear();
    artistMap.clear();
    albumMap.clear();
    genreMap.clear();
}

// Helper methods
void Library::updateMaps(std::shared_ptr<Song> song) {
    artistMap[song->getArtist()].push_back(song);
    albumMap[song->getAlbum()].push_back(song);
    genreMap[song->getGenre()].push_back(song);
}

void Library::rebuildMaps() {
    artistMap.clear();
    albumMap.clear();
    genreMap.clear();
    
    for (const auto& song : allSongs) {
        updateMaps(song);
    }
}

// Song management
void Library::addSong(std::shared_ptr<Song> song) {
    if (song) {
        allSongs.push_back(song);
        updateMaps(song);
        std::cout << "Added to library: " << song->getTitle() << std::endl;
    }
}

bool Library::removeSong(const std::string& title) {
    auto it = std::remove_if(allSongs.begin(), allSongs.end(),
        [&title](const std::shared_ptr<Song>& song) {
            return song->getTitle() == title;
        });
    
    if (it != allSongs.end()) {
        allSongs.erase(it, allSongs.end());
        rebuildMaps();
        std::cout << "Removed from library: " << title << std::endl;
        return true;
    }
    return false;
}

std::shared_ptr<Song> Library::findSongByTitle(const std::string& title) const {
    for (const auto& song : allSongs) {
        if (song->getTitle() == title) {
            return song;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Song>> Library::getAllSongs() const {
    return allSongs;
}

int Library::getTotalSongs() const {
    return allSongs.size();
}

// Playlist management
std::shared_ptr<Playlist> Library::createPlaylist(const std::string& name) {
    auto playlist = std::make_shared<Playlist>(name);
    playlists.push_back(playlist);
    std::cout << "Created playlist: " << name << std::endl;
    return playlist;
}

std::shared_ptr<Playlist> Library::createPlaylist(const std::string& name, const std::string& description) {
    auto playlist = std::make_shared<Playlist>(name, description);
    playlists.push_back(playlist);
    std::cout << "Created playlist: " << name << std::endl;
    return playlist;
}

bool Library::deletePlaylist(const std::string& name) {
    auto it = std::remove_if(playlists.begin(), playlists.end(),
        [&name](const std::shared_ptr<Playlist>& pl) {
            return pl->getName() == name;
        });
    
    if (it != playlists.end()) {
        playlists.erase(it, playlists.end());
        std::cout << "Deleted playlist: " << name << std::endl;
        return true;
    }
    return false;
}

std::shared_ptr<Playlist> Library::getPlaylist(const std::string& name) const {
    for (const auto& playlist : playlists) {
        if (playlist->getName() == name) {
            return playlist;
        }
    }
    return nullptr;
}

std::vector<std::shared_ptr<Playlist>> Library::getAllPlaylists() const {
    return playlists;
}

void Library::displayAllPlaylists() const {
    std::cout << "\n=== All Playlists ===" << std::endl;
    if (playlists.empty()) {
        std::cout << "No playlists found." << std::endl;
        return;
    }
    
    for (size_t i = 0; i < playlists.size(); ++i) {
        std::cout << i + 1 << ". " << playlists[i]->getName() 
                  << " (" << playlists[i]->getSongCount() << " songs)" << std::endl;
    }
}

// Search and filter operations
std::vector<std::shared_ptr<Song>> Library::searchSongs(const std::string& keyword) const {
    std::vector<std::shared_ptr<Song>> results;
    
    for (const auto& song : allSongs) {
        if (song->getTitle().find(keyword) != std::string::npos ||
            song->getArtist().find(keyword) != std::string::npos ||
            song->getAlbum().find(keyword) != std::string::npos) {
            results.push_back(song);
        }
    }
    
    return results;
}

std::vector<std::shared_ptr<Song>> Library::getSongsByArtist(const std::string& artist) const {
    auto it = artistMap.find(artist);
    if (it != artistMap.end()) {
        return it->second;
    }
    return std::vector<std::shared_ptr<Song>>();
}

std::vector<std::shared_ptr<Song>> Library::getSongsByAlbum(const std::string& album) const {
    auto it = albumMap.find(album);
    if (it != albumMap.end()) {
        return it->second;
    }
    return std::vector<std::shared_ptr<Song>>();
}

std::vector<std::shared_ptr<Song>> Library::getSongsByGenre(const std::string& genre) const {
    auto it = genreMap.find(genre);
    if (it != genreMap.end()) {
        return it->second;
    }
    return std::vector<std::shared_ptr<Song>>();
}

// Statistics
std::vector<std::shared_ptr<Song>> Library::getMostPlayedSongs(int count) const {
    std::vector<std::shared_ptr<Song>> sortedSongs = allSongs;
    
    std::sort(sortedSongs.begin(), sortedSongs.end(),
        [](const std::shared_ptr<Song>& a, const std::shared_ptr<Song>& b) {
            return a->getPlayCount() > b->getPlayCount();
        });
    
    if (sortedSongs.size() > count) {
        sortedSongs.resize(count);
    }
    
    return sortedSongs;
}

std::set<std::string> Library::getAllArtists() const {
    std::set<std::string> artists;
    for (const auto& pair : artistMap) {
        artists.insert(pair.first);
    }
    return artists;
}

std::set<std::string> Library::getAllAlbums() const {
    std::set<std::string> albums;
    for (const auto& pair : albumMap) {
        albums.insert(pair.first);
    }
    return albums;
}

std::set<std::string> Library::getAllGenres() const {
    std::set<std::string> genres;
    for (const auto& pair : genreMap) {
        genres.insert(pair.first);
    }
    return genres;
}

// Display methods
void Library::displayLibrary() const {
    std::cout << "\n=== Music Library ===" << std::endl;
    std::cout << "Total Songs: " << allSongs.size() << std::endl;
    std::cout << "Total Artists: " << artistMap.size() << std::endl;
    std::cout << "Total Albums: " << albumMap.size() << std::endl;
    std::cout << "Total Playlists: " << playlists.size() << std::endl;
    std::cout << "\nSongs:" << std::endl;
    
    for (size_t i = 0; i < allSongs.size(); ++i) {
        std::cout << i + 1 << ". " << *allSongs[i] << std::endl;
    }
}

void Library::displayStatistics() const {
    std::cout << "\n=== Library Statistics ===" << std::endl;
    std::cout << "Total Songs: " << allSongs.size() << std::endl;
    std::cout << "Total Artists: " << artistMap.size() << std::endl;
    std::cout << "Total Albums: " << albumMap.size() << std::endl;
    std::cout << "Total Genres: " << genreMap.size() << std::endl;
    std::cout << "Total Playlists: " << playlists.size() << std::endl;
    
    auto mostPlayed = getMostPlayedSongs(5);
    if (!mostPlayed.empty()) {
        std::cout << "\nTop 5 Most Played:" << std::endl;
        for (size_t i = 0; i < mostPlayed.size(); ++i) {
            std::cout << i + 1 << ". " << *mostPlayed[i] 
                      << " (" << mostPlayed[i]->getPlayCount() << " plays)" << std::endl;
        }
    }
}

void Library::displayArtists() const {
    std::cout << "\n=== Artists ===" << std::endl;
    for (const auto& pair : artistMap) {
        std::cout << pair.first << " (" << pair.second.size() << " songs)" << std::endl;
    }
}

void Library::displayAlbums() const {
    std::cout << "\n=== Albums ===" << std::endl;
    for (const auto& pair : albumMap) {
        std::cout << pair.first << " (" << pair.second.size() << " songs)" << std::endl;
    }
}