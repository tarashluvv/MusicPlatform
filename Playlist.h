#ifndef PLAYLIST_H
#define PLAYLIST_H

#include "Song.h"
#include <vector>
#include <string>
#include <memory>
#include <algorithm>

class Playlist {
private:
    std::string name;
    std::vector<std::shared_ptr<Song>> songs;
    std::string description;
    
public:
    // Constructors
    Playlist();
    explicit Playlist(const std::string& name);
    Playlist(const std::string& name, const std::string& description);
    
    // Rule of Five
    Playlist(const Playlist& other);
    Playlist(Playlist&& other) noexcept;
    Playlist& operator=(const Playlist& other);
    Playlist& operator=(Playlist&& other) noexcept;
    ~Playlist();
    
    // Getters
    std::string getName() const;
    std::string getDescription() const;
    int getSongCount() const;
    int getTotalDuration() const;
    std::vector<std::shared_ptr<Song>> getSongs() const;
    
    // Setters
    void setName(const std::string& name);
    void setDescription(const std::string& description);
    
    // Song management
    void addSong(std::shared_ptr<Song> song);
    bool removeSong(int index);
    bool removeSongByTitle(const std::string& title);
    void clearPlaylist();
    std::shared_ptr<Song> getSong(int index) const;
    
    // Playlist operations
    void shuffle();
    void sortByTitle();
    void sortByArtist();
    void sortByDuration();
    void displayPlaylist() const;
    bool isEmpty() const;
    
    // Search operations
    std::vector<std::shared_ptr<Song>> searchByTitle(const std::string& keyword) const;
    std::vector<std::shared_ptr<Song>> searchByArtist(const std::string& keyword) const;
    
    // Operator overloading
    std::shared_ptr<Song> operator[](int index) const;
};

#endif // PLAYLIST_H