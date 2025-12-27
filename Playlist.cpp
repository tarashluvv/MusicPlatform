#include "Playlist.h"
#include <iostream>
#include <random>
#include <chrono>

// Constructors
Playlist::Playlist() : name("Untitled Playlist"), description("") {}

Playlist::Playlist(const std::string& name) 
    : name(name), description("") {}

Playlist::Playlist(const std::string& name, const std::string& description)
    : name(name), description(description) {}

// Copy constructor
Playlist::Playlist(const Playlist& other)
    : name(other.name), description(other.description), songs(other.songs) {
    std::cout << "Playlist copied: " << name << std::endl;
}

// Move constructor
Playlist::Playlist(Playlist&& other) noexcept
    : name(std::move(other.name)), 
      description(std::move(other.description)),
      songs(std::move(other.songs)) {}

// Copy assignment
Playlist& Playlist::operator=(const Playlist& other) {
    if (this != &other) {
        name = other.name;
        description = other.description;
        songs = other.songs;
    }
    return *this;
}

// Move assignment
Playlist& Playlist::operator=(Playlist&& other) noexcept {
    if (this != &other) {
        name = std::move(other.name);
        description = std::move(other.description);
        songs = std::move(other.songs);
    }
    return *this;
}

// Destructor
Playlist::~Playlist() {
    songs.clear();
}

// Getters
std::string Playlist::getName() const { return name; }
std::string Playlist::getDescription() const { return description; }
int Playlist::getSongCount() const { return songs.size(); }

int Playlist::getTotalDuration() const {
    int total = 0;
    for (const auto& song : songs) {
        total += song->getDuration();
    }
    return total;
}

std::vector<std::shared_ptr<Song>> Playlist::getSongs() const {
    return songs;
}

// Setters
void Playlist::setName(const std::string& name) { this->name = name; }
void Playlist::setDescription(const std::string& description) { 
    this->description = description; 
}

// Song management
void Playlist::addSong(std::shared_ptr<Song> song) {
    if (song) {
        songs.push_back(song);
        std::cout << "Added: " << song->getTitle() << " to " << name << std::endl;
    }
}

bool Playlist::removeSong(int index) {
    if (index >= 0 && index < songs.size()) {
        std::cout << "Removed: " << songs[index]->getTitle() << std::endl;
        songs.erase(songs.begin() + index);
        return true;
    }
    return false;
}

bool Playlist::removeSongByTitle(const std::string& title) {
    auto it = std::remove_if(songs.begin(), songs.end(),
        [&title](const std::shared_ptr<Song>& song) {
            return song->getTitle() == title;
        });
    
    if (it != songs.end()) {
        songs.erase(it, songs.end());
        return true;
    }
    return false;
}

void Playlist::clearPlaylist() {
    songs.clear();
    std::cout << "Playlist cleared: " << name << std::endl;
}

std::shared_ptr<Song> Playlist::getSong(int index) const {
    if (index >= 0 && index < songs.size()) {
        return songs[index];
    }
    return nullptr;
}

// Playlist operations
void Playlist::shuffle() {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::shuffle(songs.begin(), songs.end(), std::default_random_engine(seed));
    std::cout << "Playlist shuffled: " << name << std::endl;
}

void Playlist::sortByTitle() {
    std::sort(songs.begin(), songs.end(),
        [](const std::shared_ptr<Song>& a, const std::shared_ptr<Song>& b) {
            return a->getTitle() < b->getTitle();
        });
    std::cout << "Sorted by title" << std::endl;
}

void Playlist::sortByArtist() {
    std::sort(songs.begin(), songs.end(),
        [](const std::shared_ptr<Song>& a, const std::shared_ptr<Song>& b) {
            return a->getArtist() < b->getArtist();
        });
    std::cout << "Sorted by artist" << std::endl;
}

void Playlist::sortByDuration() {
    std::sort(songs.begin(), songs.end(),
        [](const std::shared_ptr<Song>& a, const std::shared_ptr<Song>& b) {
            return a->getDuration() < b->getDuration();
        });
    std::cout << "Sorted by duration" << std::endl;
}

void Playlist::displayPlaylist() const {
    std::cout << "\n=== " << name << " ===" << std::endl;
    if (!description.empty()) {
        std::cout << "Description: " << description << std::endl;
    }
    std::cout << "Songs: " << getSongCount() << std::endl;
    std::cout << "Total Duration: " << getTotalDuration() / 60 << " minutes" << std::endl;
    std::cout << "\nTracks:" << std::endl;
    
    for (size_t i = 0; i < songs.size(); ++i) {
        std::cout << i + 1 << ". " << *songs[i] << std::endl;
    }
    std::cout << std::endl;
}

bool Playlist::isEmpty() const {
    return songs.empty();
}

// Search operations
std::vector<std::shared_ptr<Song>> Playlist::searchByTitle(const std::string& keyword) const {
    std::vector<std::shared_ptr<Song>> results;
    for (const auto& song : songs) {
        if (song->getTitle().find(keyword) != std::string::npos) {
            results.push_back(song);
        }
    }
    return results;
}

std::vector<std::shared_ptr<Song>> Playlist::searchByArtist(const std::string& keyword) const {
    std::vector<std::shared_ptr<Song>> results;
    for (const auto& song : songs) {
        if (song->getArtist().find(keyword) != std::string::npos) {
            results.push_back(song);
        }
    }
    return results;
}

// Operator overloading
std::shared_ptr<Song> Playlist::operator[](int index) const {
    return getSong(index);
}