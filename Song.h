#ifndef SONG_H
#define SONG_H

#include <string>
#include <iostream>
#include <memory>

class Song {
private:
    std::string title;
    std::string artist;
    std::string album;
    std::string filePath;
    int duration; // in seconds
    std::string genre;
    int playCount;
    
public:
    // Constructors
    Song();
    Song(const std::string& title, const std::string& artist, 
         const std::string& album, const std::string& filePath, 
         int duration, const std::string& genre = "Unknown");
    
    // Copy constructor
    Song(const Song& other);
    
    // Move constructor
    Song(Song&& other) noexcept;
    
    // Copy assignment operator
    Song& operator=(const Song& other);
    
    // Move assignment operator
    Song& operator=(Song&& other) noexcept;
    
    // Destructor
    ~Song();
    
    // Getters
    std::string getTitle() const;
    std::string getArtist() const;
    std::string getAlbum() const;
    std::string getFilePath() const;
    int getDuration() const;
    std::string getGenre() const;
    int getPlayCount() const;
    
    // Setters
    void setTitle(const std::string& title);
    void setArtist(const std::string& artist);
    void setAlbum(const std::string& album);
    void setFilePath(const std::string& filePath);
    void setDuration(int duration);
    void setGenre(const std::string& genre);
    
    // Methods
    void play();
    void incrementPlayCount();
    std::string getDurationFormatted() const;
    void displayInfo() const;
    
    // Operator overloading
    bool operator==(const Song& other) const;
    bool operator!=(const Song& other) const;
    friend std::ostream& operator<<(std::ostream& os, const Song& song);
    
    // Comparison operators for sorting
    bool operator<(const Song& other) const;
    bool operator>(const Song& other) const;
};

#endif // SONG_H