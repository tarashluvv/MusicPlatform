# 🎵 Music Listening Platform - C++ Final Project

A feature-rich, object-oriented music management and playback system built with modern C++ concepts.

## 📋 Project Overview

This Music Listening Platform is a desktop application that allows users to manage their music library, create and organize playlists, and control music playback. The project demonstrates advanced C++ programming concepts including OOP, STL containers, smart pointers, design patterns, and more.

## ✨ Features

### Core Functionality
- **Music Library Management**: Add, remove, and organize songs
- **Smart Playlist System**: Create, edit, and manage custom playlists
- **Music Player**: Play songs with full playback controls (play, pause, next, previous)
- **Advanced Search**: Search songs by title, artist, album, or genre
- **Playback Modes**: Shuffle and repeat modes (none, one, all)
- **Queue System**: Add songs to play queue
- **Statistics Tracking**: Track play counts and most played songs

### Advanced Features
- Automatic organization by artist, album, and genre
- Playlist sorting (by title, artist, duration)
- Playlist shuffling with random algorithm
- Play count tracking
- Formatted duration display (MM:SS)

## 🛠️ Technologies Used

### Backend (C++)
- **Language**: C++11/14/17
- **Build System**: g++ compiler
- **Development Environment**: Visual Studio Code

### Key C++ Concepts Demonstrated
1. **Object-Oriented Programming**
   - Classes and objects (Song, Playlist, Library, MusicPlayer)
   - Encapsulation with private/public members
   - Constructors and destructors
   - The Rule of Five (copy/move constructors and assignment operators)

2. **STL (Standard Template Library)**
   - `std::vector` - Dynamic arrays for songs and playlists
   - `std::map` - Organizing songs by artist/album/genre
   - `std::set` - Unique collections of artists/albums
   - `std::queue` - Play queue management
   - `std::shared_ptr` - Smart pointers for memory management

3. **Advanced Features**
   - Lambda expressions for sorting and searching
   - Operator overloading (==, !=, <, >, <<, [])
   - Enum classes for type-safe states
   - Algorithm library functions (sort, shuffle, remove_if)
   - RAII (Resource Acquisition Is Initialization) principles

4. **Design Patterns**
   - Composition pattern (Library contains Songs and Playlists)
   - State pattern (PlayerState enum)
   - Strategy pattern (different sort methods)

## 📁 Project Structure

```
MusicPlatform/
├── src/
│   ├── Song.h              # Song class header
│   ├── Song.cpp            # Song class implementation
│   ├── Playlist.h          # Playlist class header
│   ├── Playlist.cpp        # Playlist implementation
│   ├── Library.h           # Library class header
│   ├── Library.cpp         # Library implementation
│   ├── MusicPlayer.h       # Music player header
│   ├── MusicPlayer.cpp     # Music player implementation
│   └── main.cpp            # Main application entry point
├── README.md               # This file
└── .gitignore             # Git ignore file
```

## 🚀 How to Compile and Run

### Prerequisites
- C++ compiler (g++ recommended)
- C++11 or later support
- Terminal/Command Prompt

### Compilation Instructions

#### Option 1: Compile All Files at Once
```bash
g++ -std=c++11 src/*.cpp -o music_platform
```

#### Option 2: Compile Step by Step
```bash
# Compile each source file
g++ -std=c++11 -c src/Song.cpp -o Song.o
g++ -std=c++11 -c src/Playlist.cpp -o Playlist.o
g++ -std=c++11 -c src/Library.cpp -o Library.o
g++ -std=c++11 -c src/MusicPlayer.cpp -o MusicPlayer.o
g++ -std=c++11 -c src/main.cpp -o main.o

# Link all object files
g++ Song.o Playlist.o Library.o MusicPlayer.o main.o -o music_platform
```

#### Option 3: Using Makefile (Recommended)
Create a `Makefile`:
```makefile
CXX = g++
CXXFLAGS = -std=c++11 -Wall
TARGET = music_platform
SOURCES = src/Song.cpp src/Playlist.cpp src/Library.cpp src/MusicPlayer.cpp src/main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

run: $(TARGET)
	./$(TARGET)
```

Then run:
```bash
make
make run
```

### Running the Application
```bash
./music_platform
```

On Windows:
```bash
music_platform.exe
```

## 📖 Usage Guide

### Menu Options

1. **Add Song to Library**: Add a new song with metadata (title, artist, album, duration, genre)
2. **Display Library**: View all songs in your library
3. **Create Playlist**: Create a new playlist with name and description
4. **Add Song to Playlist**: Add existing songs to a playlist
5. **Display Playlists**: View all available playlists
6. **Display Playlist Songs**: View songs in a specific playlist
7. **Play Song**: Play a specific song
8. **Play Playlist**: Start playing a playlist from the beginning
9. **Player Controls**: Control playback (next, previous, pause, resume, stop)
10. **Search Songs**: Search for songs by keyword
11. **Display Statistics**: View library statistics and most played songs
12. **Display Artists**: View all artists and their song counts
13. **Shuffle Playlist**: Randomize the order of songs in a playlist
14. **Sort Playlist**: Sort playlist by title, artist, or duration

### Sample Workflow

```
1. Load demo data (y)
2. Display Library (option 2)
3. Play Playlist "My Favorites" (option 8)
4. Use player controls (option 9)
   - Next track
   - Display status
5. Search for songs (option 10)
6. View statistics (option 11)
```

## 🎯 Advanced C++ Features Showcase

### 1. Smart Pointers
```cpp
std::shared_ptr<Song> song = std::make_shared<Song>(...);
```
- Automatic memory management
- No manual delete needed
- Safe sharing between objects

### 2. Lambda Expressions
```cpp
std::sort(songs.begin(), songs.end(),
    [](const std::shared_ptr<Song>& a, const std::shared_ptr<Song>& b) {
        return a->getTitle() < b->getTitle();
    });
```

### 3. Move Semantics
```cpp
Song::Song(Song&& other) noexcept
    : title(std::move(other.title)), ...
```

### 4. Operator Overloading
```cpp
std::ostream& operator<<(std::ostream& os, const Song& song)
bool operator==(const Song& other) const
```

### 5. STL Algorithms
```cpp
std::shuffle(songs.begin(), songs.end(), random_engine);
std::remove_if(songs.begin(), songs.end(), predicate);
```

## 👥 Team Information

- **Team Member**: [Your Name]
- **Student ID**: [Your ID]
- **Course**: C++ Programming
- **Date**: December 2024

## 🔮 Future Enhancements

Possible extensions for higher grades:
- Audio file parsing (read real MP3/WAV metadata)
- Web-based UI using HTML/CSS/JavaScript
- Database integration (SQLite)
- User authentication system
- Music recommendations algorithm
- Export/import playlists (JSON/XML format)
- Real audio playback integration
- Visualization of audio spectrum

## 📝 License

This project is created for educational purposes as part of a C++ final project.

## 🤝 Contributing

This is an individual/team academic project. For suggestions or questions, please contact the team members.

## 📧 Contact

- Email: [your.email@example.com]
- GitHub: [your-github-username]

## 🙏 Acknowledgments

- C++ Standard Library documentation
- Visual Studio Code
- Course instructors and materials

---

**Note**: This project demonstrates advanced C++ concepts for academic purposes. The audio playback is simulated through console output. For real audio playback, integration with libraries like SFML, SDL, or BASS would be required.