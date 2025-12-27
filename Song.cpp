#include "Song.h"
#include <iomanip>
#include <sstream>

// Default constructor
Song::Song() 
    : title("Unknown"), artist("Unknown"), album("Unknown"), 
      filePath(""), duration(0), genre("Unknown"), playCount(0) {}

// Parameterized constructor
Song::Song(const std::string& title, const std::string& artist, 
           const std::string& album, const std::string& filePath, 
           int duration, const std::string& genre)
    : title(title), artist(artist), album(album), filePath(filePath),
      duration(duration), genre(genre), playCount(0) {}

// Copy constructor
Song::Song(const Song& other)
    : title(other.title), artist(other.artist), album(other.album),
      filePath(other.filePath), duration(other.duration), 
      genre(other.genre), playCount(other.playCount) {
    std::cout << "Song copied: " << title << std::endl;
}

// Move constructor
Song::Song(Song&& other) noexcept
    : title(std::move(other.title)), artist(std::move(other.artist)),
      album(std::move(other.album)), filePath(std::move(other.filePath)),
      duration(other.duration), genre(std::move(other.genre)),
      playCount(other.playCount) {
    other.duration = 0;
    other.playCount = 0;
}

// Copy assignment operator
Song& Song::operator=(const Song& other) {
    if (this != &other) {
        title = other.title;
        artist = other.artist;
        album = other.album;
        filePath = other.filePath;
        duration = other.duration;
        genre = other.genre;
        playCount = other.playCount;
    }
    return *this;
}

// Move assignment operator
Song& Song::operator=(Song&& other) noexcept {
    if (this != &other) {
        title = std::move(other.title);
        artist = std::move(other.artist);
        album = std::move(other.album);
        filePath = std::move(other.filePath);
        duration = other.duration;
        genre = std::move(other.genre);
        playCount = other.playCount;
        
        other.duration = 0;
        other.playCount = 0;
    }
    return *this;
}

// Destructor
Song::~Song() {
    // No dynamic memory to clean up, but good practice to have it
}

// Getters
std::string Song::getTitle() const { return title; }
std::string Song::getArtist() const { return artist; }
std::string Song::getAlbum() const { return album; }
std::string Song::getFilePath() const { return filePath; }
int Song::getDuration() const { return duration; }
std::string Song::getGenre() const { return genre; }
int Song::getPlayCount() const { return playCount; }

// Setters
void Song::setTitle(const std::string& title) { this->title = title; }
void Song::setArtist(const std::string& artist) { this->artist = artist; }
void Song::setAlbum(const std::string& album) { this->album = album; }
void Song::setFilePath(const std::string& filePath) { this->filePath = filePath; }
void Song::setDuration(int duration) { this->duration = duration; }
void Song::setGenre(const std::string& genre) { this->genre = genre; }

// Methods
void Song::play() {
    incrementPlayCount();
    std::cout << "Now playing: " << title << " by " << artist << std::endl;
}

void Song::incrementPlayCount() {
    playCount++;
}

std::string Song::getDurationFormatted() const {
    int minutes = duration / 60;
    int seconds = duration % 60;
    std::ostringstream oss;
    oss << minutes << ":" << std::setw(2) << std::setfill('0') << seconds;
    return oss.str();
}

void Song::displayInfo() const {
    std::cout << "Title: " << title << std::endl;
    std::cout << "Artist: " << artist << std::endl;
    std::cout << "Album: " << album << std::endl;
    std::cout << "Genre: " << genre << std::endl;
    std::cout << "Duration: " << getDurationFormatted() << std::endl;
    std::cout << "Play Count: " << playCount << std::endl;
}

// Operator overloading
bool Song::operator==(const Song& other) const {
    return title == other.title && artist == other.artist && album == other.album;
}

bool Song::operator!=(const Song& other) const {
    return !(*this == other);
}

std::ostream& operator<<(std::ostream& os, const Song& song) {
    os << song.title << " - " << song.artist << " [" << song.getDurationFormatted() << "]";
    return os;
}

bool Song::operator<(const Song& other) const {
    return title < other.title;
}

bool Song::operator>(const Song& other) const {
    return title > other.title;
}