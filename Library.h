#ifndef LIBRARY_H
#define LIBRARY_H

#include "Song.h"
#include "Playlist.h"
#include <vector>
#include <map>
#include <set>
#include <memory>
#include <string>

class Library {
private:
    std::vector<std::shared_ptr<Song>> allSongs;
    std::vector<std::shared_ptr<Playlist>> playlists;
    std::map<std::string, std::vector<std::shared_ptr<Song>>> artistMap;
    std::map<std::string, std::vector<std::shared_ptr<Song>>> albumMap;
    std::map<std::string, std::vector<std::shared_ptr<Song>>> genreMap;
    
    // Helper methods
    void updateMaps(std::shared_ptr<Song> song);
    void rebuildMaps();
    
public:
    // Constructor and Destructor
    Library();
    ~Library();
    
    // Song management
    void addSong(std::shared_ptr<Song> song);
    bool removeSong(const std::string& title);
    std::shared_ptr<Song> findSongByTitle(const std::string& title) const;
    std::vector<std::shared_ptr<Song>> getAllSongs() const;
    int getTotalSongs() const;
    
    // Playlist management
    std::shared_ptr<Playlist> createPlaylist(const std::string& name);
    std::shared_ptr<Playlist> createPlaylist(const std::string& name, const std::string& description);
    bool deletePlaylist(const std::string& name);
    std::shared_ptr<Playlist> getPlaylist(const std::string& name) const;
    std::vector<std::shared_ptr<Playlist>> getAllPlaylists() const;
    void displayAllPlaylists() const;
    
    // Search and filter operations
    std::vector<std::shared_ptr<Song>> searchSongs(const std::string& keyword) const;
    std::vector<std::shared_ptr<Song>> getSongsByArtist(const std::string& artist) const;
    std::vector<std::shared_ptr<Song>> getSongsByAlbum(const std::string& album) const;
    std::vector<std::shared_ptr<Song>> getSongsByGenre(const std::string& genre) const;
    
    // Statistics
    std::vector<std::shared_ptr<Song>> getMostPlayedSongs(int count = 10) const;
    std::set<std::string> getAllArtists() const;
    std::set<std::string> getAllAlbums() const;
    std::set<std::string> getAllGenres() const;
    
    // Display methods
    void displayLibrary() const;
    void displayStatistics() const;
    void displayArtists() const;
    void displayAlbums() const;
};

#endif // LIBRARY_H