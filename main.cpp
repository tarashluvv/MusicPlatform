#include <iostream>
#include <memory>
#include "Song.h"
#include "Playlist.h"
#include "Library.h"
#include "MusicPlayer.h"
#include "FileManager.h"

void displayMenu() {
    std::cout << "\n╔════════════════════════════════════╗" << std::endl;
    std::cout << "║    🎵 Music Platform Menu 🎵      ║" << std::endl;
    std::cout << "╚════════════════════════════════════╝" << std::endl;
    std::cout << "1.  Add Song to Library" << std::endl;
    std::cout << "2.  Display Library" << std::endl;
    std::cout << "3.  Create Playlist" << std::endl;
    std::cout << "4.  Add Song to Playlist" << std::endl;
    std::cout << "5.  Display Playlists" << std::endl;
    std::cout << "6.  Display Playlist Songs" << std::endl;
    std::cout << "7.  Play Song" << std::endl;
    std::cout << "8.  Play Playlist" << std::endl;
    std::cout << "9.  Player Controls (Next/Prev/Pause)" << std::endl;
    std::cout << "10. Search Songs" << std::endl;
    std::cout << "11. Display Statistics" << std::endl;
    std::cout << "12. Display Artists" << std::endl;
    std::cout << "13. Shuffle Playlist" << std::endl;
    std::cout << "14. Sort Playlist" << std::endl;
    std::cout << "15. Save Library" << std::endl;
    std::cout << "16. Load Library" << std::endl;
    std::cout << "17. Save Playlist" << std::endl;
    std::cout << "18. Export to CSV" << std::endl;
    std::cout << "0.  Exit" << std::endl;
    std::cout << "Enter choice: ";
}

void demoWithSampleData(Library& library, MusicPlayer& player) {
    std::cout << "\n=== Loading Sample Data ===" << std::endl;
    
    // Create sample songs
    auto song1 = std::make_shared<Song>("Blinding Lights", "The Weeknd", "After Hours", 
                                        "/music/blinding_lights.mp3", 200, "Pop");
    auto song2 = std::make_shared<Song>("Levitating", "Dua Lipa", "Future Nostalgia", 
                                        "/music/levitating.mp3", 203, "Pop");
    auto song3 = std::make_shared<Song>("Circles", "Post Malone", "Hollywood's Bleeding", 
                                        "/music/circles.mp3", 215, "Pop");
    auto song4 = std::make_shared<Song>("Watermelon Sugar", "Harry Styles", "Fine Line", 
                                        "/music/watermelon.mp3", 174, "Pop");
    auto song5 = std::make_shared<Song>("Save Your Tears", "The Weeknd", "After Hours", 
                                        "/music/save_tears.mp3", 215, "Pop");
    
    // Add songs to library
    library.addSong(song1);
    library.addSong(song2);
    library.addSong(song3);
    library.addSong(song4);
    library.addSong(song5);
    
    // Create playlists
    auto favorites = library.createPlaylist("My Favorites", "Best songs ever!");
    favorites->addSong(song1);
    favorites->addSong(song2);
    favorites->addSong(song4);
    
    auto workout = library.createPlaylist("Workout Mix", "Get pumped!");
    workout->addSong(song2);
    workout->addSong(song3);
    workout->addSong(song5);
    
    std::cout << "Sample data loaded successfully!" << std::endl;
}

int main() {
    Library library;
    MusicPlayer player;
    FileManager fileManager;
    int choice;
    bool running = true;
    
    std::cout << "╔══════════════════════════════════════════╗" << std::endl;
    std::cout << "║  Welcome to C++ Music Listening Platform ║" << std::endl;
    std::cout << "╚══════════════════════════════════════════╝" << std::endl;
    
    // Try to load existing library
    std::cout << "\nAttempting to load existing library..." << std::endl;
    if (!fileManager.loadLibrary(library)) {
        // If no library exists, offer to load demo data
        char loadDemo;
        std::cout << "\nNo existing library found. Load demo data? (y/n): ";
        std::cin >> loadDemo;
        std::cin.ignore();
        
        if (loadDemo == 'y' || loadDemo == 'Y') {
            demoWithSampleData(library, player);
        }
    }
    
    while (running) {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore();
        
        switch (choice) {
            case 1: { // Add Song
                std::string title, artist, album, genre;
                int duration;
                
                std::cout << "\nEnter song details:" << std::endl;
                std::cout << "Title: ";
                std::getline(std::cin, title);
                std::cout << "Artist: ";
                std::getline(std::cin, artist);
                std::cout << "Album: ";
                std::getline(std::cin, album);
                std::cout << "Duration (seconds): ";
                std::cin >> duration;
                std::cin.ignore();
                std::cout << "Genre: ";
                std::getline(std::cin, genre);
                
                auto song = std::make_shared<Song>(title, artist, album, 
                                                   "/music/" + title + ".mp3", 
                                                   duration, genre);
                library.addSong(song);
                break;
            }
            
            case 2: // Display Library
                library.displayLibrary();
                break;
            
            case 3: { // Create Playlist
                std::string name, desc;
                std::cout << "Playlist name: ";
                std::getline(std::cin, name);
                std::cout << "Description: ";
                std::getline(std::cin, desc);
                library.createPlaylist(name, desc);
                break;
            }
            
            case 4: { // Add Song to Playlist
                std::string playlistName, songTitle;
                std::cout << "Playlist name: ";
                std::getline(std::cin, playlistName);
                std::cout << "Song title: ";
                std::getline(std::cin, songTitle);
                
                auto playlist = library.getPlaylist(playlistName);
                auto song = library.findSongByTitle(songTitle);
                
                if (playlist && song) {
                    playlist->addSong(song);
                } else {
                    std::cout << "Playlist or song not found!" << std::endl;
                }
                break;
            }
            
            case 5: // Display Playlists
                library.displayAllPlaylists();
                break;
            
            case 6: { // Display Playlist Songs
                std::string name;
                std::cout << "Playlist name: ";
                std::getline(std::cin, name);
                auto playlist = library.getPlaylist(name);
                if (playlist) {
                    playlist->displayPlaylist();
                } else {
                    std::cout << "Playlist not found!" << std::endl;
                }
                break;
            }
            
            case 7: { // Play Song
                std::string title;
                std::cout << "Song title: ";
                std::getline(std::cin, title);
                auto song = library.findSongByTitle(title);
                if (song) {
                    player.play(song);
                } else {
                    std::cout << "Song not found!" << std::endl;
                }
                break;
            }
            
            case 8: { // Play Playlist
                std::string name;
                std::cout << "Playlist name: ";
                std::getline(std::cin, name);
                auto playlist = library.getPlaylist(name);
                if (playlist) {
                    player.playPlaylist(playlist);
                } else {
                    std::cout << "Playlist not found!" << std::endl;
                }
                break;
            }
            
            case 9: { // Player Controls
                std::cout << "\n1. Next  2. Previous  3. Pause  4. Resume  5. Stop  6. Status" << std::endl;
                std::cout << "Choice: ";
                int ctrl;
                std::cin >> ctrl;
                std::cin.ignore();
                
                switch (ctrl) {
                    case 1: player.next(); break;
                    case 2: player.previous(); break;
                    case 3: player.pause(); break;
                    case 4: player.resume(); break;
                    case 5: player.stop(); break;
                    case 6: player.displayPlayerStatus(); break;
                }
                break;
            }
            
            case 10: { // Search
                std::string keyword;
                std::cout << "Search keyword: ";
                std::getline(std::cin, keyword);
                auto results = library.searchSongs(keyword);
                std::cout << "\nSearch Results (" << results.size() << "):" << std::endl;
                for (size_t i = 0; i < results.size(); ++i) {
                    std::cout << i + 1 << ". " << *results[i] << std::endl;
                }
                break;
            }
            
            case 11: // Statistics
                library.displayStatistics();
                break;
            
            case 12: // Artists
                library.displayArtists();
                break;
            
            case 13: { // Shuffle Playlist
                std::string name;
                std::cout << "Playlist name: ";
                std::getline(std::cin, name);
                auto playlist = library.getPlaylist(name);
                if (playlist) {
                    playlist->shuffle();
                    std::cout << "Playlist shuffled!" << std::endl;
                } else {
                    std::cout << "Playlist not found!" << std::endl;
                }
                break;
            }
            
            case 14: { // Sort Playlist
                std::string name;
                std::cout << "Playlist name: ";
                std::getline(std::cin, name);
                auto playlist = library.getPlaylist(name);
                if (playlist) {
                    std::cout << "1. By Title  2. By Artist  3. By Duration" << std::endl;
                    int sortChoice;
                    std::cin >> sortChoice;
                    std::cin.ignore();
                    
                    switch (sortChoice) {
                        case 1: playlist->sortByTitle(); break;
                        case 2: playlist->sortByArtist(); break;
                        case 3: playlist->sortByDuration(); break;
                    }
                } else {
                    std::cout << "Playlist not found!" << std::endl;
                }
                break;
            }
            
            case 15: { // Save Library
                if (fileManager.saveLibrary(library)) {
                    std::cout << "✓ Library saved successfully!" << std::endl;
                } else {
                    std::cout << "✗ Failed to save library!" << std::endl;
                }
                break;
            }
            
            case 16: { // Load Library
                Library newLibrary;
                if (fileManager.loadLibrary(newLibrary)) {
                    library = std::move(newLibrary);
                    std::cout << "✓ Library loaded successfully!" << std::endl;
                } else {
                    std::cout << "✗ Failed to load library!" << std::endl;
                }
                break;
            }
            
            case 17: { // Save Playlist
                std::string name, filename;
                std::cout << "Playlist name: ";
                std::getline(std::cin, name);
                auto playlist = library.getPlaylist(name);
                if (playlist) {
                    std::cout << "Save as filename (without .txt): ";
                    std::getline(std::cin, filename);
                    if (fileManager.savePlaylist(*playlist, filename)) {
                        std::cout << "✓ Playlist saved!" << std::endl;
                    } else {
                        std::cout << "✗ Failed to save playlist!" << std::endl;
                    }
                } else {
                    std::cout << "Playlist not found!" << std::endl;
                }
                break;
            }
            
            case 18: { // Export to CSV
                std::string filename;
                std::cout << "Export filename (e.g., library.csv): ";
                std::getline(std::cin, filename);
                if (fileManager.exportToCSV(library, filename)) {
                    std::cout << "✓ Library exported to CSV!" << std::endl;
                } else {
                    std::cout << "✗ Failed to export!" << std::endl;
                }
                break;
            }
            
            case 0: // Exit
                std::cout << "\nSave library before exiting? (y/n): ";
                char save;
                std::cin >> save;
                if (save == 'y' || save == 'Y') {
                    fileManager.saveLibrary(library);
                }
                std::cout << "\nThank you for using Music Platform! 🎵" << std::endl;
                running = false;
                break;
            
            default:
                std::cout << "Invalid choice!" << std::endl;
        }
    }
    
    return 0;
}