#include "MusicPlayer.h"
#include <iostream>
#include <algorithm>
#include <random>
#include <chrono>

// Constructor
MusicPlayer::MusicPlayer() 
    : currentSong(nullptr), currentPlaylist(nullptr), 
      state(PlayerState::STOPPED), repeatMode(RepeatMode::NONE),
      shuffleMode(false), currentIndex(-1) {
    std::cout << "Music Player initialized" << std::endl;
}

// Destructor
MusicPlayer::~MusicPlayer() {
    stop();
}

// Private helper methods
void MusicPlayer::playNextInQueue() {
    if (!playQueue.empty()) {
        auto nextSong = playQueue.front();
        playQueue.pop();
        play(nextSong);
    } else if (currentPlaylist && !currentPlaylist->isEmpty()) {
        next();
    } else {
        stop();
    }
}

// Playback control
void MusicPlayer::play(std::shared_ptr<Song> song) {
    if (song) {
        currentSong = song;
        state = PlayerState::PLAYING;
        song->play();
        std::cout << "▶ Playing: " << song->getTitle() << std::endl;
    }
}

void MusicPlayer::playPlaylist(std::shared_ptr<Playlist> playlist, int startIndex) {
    if (playlist && !playlist->isEmpty()) {
        currentPlaylist = playlist;
        currentIndex = (startIndex >= 0 && startIndex < playlist->getSongCount()) 
                       ? startIndex : 0;
        
        if (shuffleMode) {
            // Create a shuffled copy for playback
            auto songs = playlist->getSongs();
            unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
            std::shuffle(songs.begin(), songs.end(), std::default_random_engine(seed));
            play(songs[0]);
        } else {
            play(playlist->getSong(currentIndex));
        }
        
        std::cout << "Playing playlist: " << playlist->getName() << std::endl;
    }
}

void MusicPlayer::pause() {
    if (state == PlayerState::PLAYING) {
        state = PlayerState::PAUSED;
        std::cout << "⏸ Paused" << std::endl;
    }
}

void MusicPlayer::resume() {
    if (state == PlayerState::PAUSED && currentSong) {
        state = PlayerState::PLAYING;
        std::cout << "▶ Resumed: " << currentSong->getTitle() << std::endl;
    }
}

void MusicPlayer::stop() {
    currentSong = nullptr;
    state = PlayerState::STOPPED;
    currentIndex = -1;
    std::cout << "⏹ Stopped" << std::endl;
}

void MusicPlayer::next() {
    if (!currentPlaylist || currentPlaylist->isEmpty()) {
        playNextInQueue();
        return;
    }
    
    if (repeatMode == RepeatMode::ONE && currentSong) {
        play(currentSong);
        return;
    }
    
    currentIndex++;
    
    if (currentIndex >= currentPlaylist->getSongCount()) {
        if (repeatMode == RepeatMode::ALL) {
            currentIndex = 0;
        } else {
            playNextInQueue();
            return;
        }
    }
    
    play(currentPlaylist->getSong(currentIndex));
}

void MusicPlayer::previous() {
    if (!currentPlaylist || currentPlaylist->isEmpty()) {
        return;
    }
    
    currentIndex--;
    
    if (currentIndex < 0) {
        if (repeatMode == RepeatMode::ALL) {
            currentIndex = currentPlaylist->getSongCount() - 1;
        } else {
            currentIndex = 0;
        }
    }
    
    play(currentPlaylist->getSong(currentIndex));
}

// Queue management
void MusicPlayer::addToQueue(std::shared_ptr<Song> song) {
    if (song) {
        playQueue.push(song);
        std::cout << "Added to queue: " << song->getTitle() << std::endl;
    }
}

void MusicPlayer::clearQueue() {
    while (!playQueue.empty()) {
        playQueue.pop();
    }
    std::cout << "Queue cleared" << std::endl;
}

int MusicPlayer::getQueueSize() const {
    return playQueue.size();
}

// Playback modes
void MusicPlayer::setShuffleMode(bool enabled) {
    shuffleMode = enabled;
    std::cout << "Shuffle: " << (enabled ? "ON" : "OFF") << std::endl;
}

void MusicPlayer::setRepeatMode(RepeatMode mode) {
    repeatMode = mode;
    std::string modeStr;
    switch (mode) {
        case RepeatMode::NONE: modeStr = "OFF"; break;
        case RepeatMode::ONE: modeStr = "Repeat One"; break;
        case RepeatMode::ALL: modeStr = "Repeat All"; break;
    }
    std::cout << "Repeat mode: " << modeStr << std::endl;
}

bool MusicPlayer::isShuffleEnabled() const {
    return shuffleMode;
}

RepeatMode MusicPlayer::getRepeatMode() const {
    return repeatMode;
}

// Status methods
PlayerState MusicPlayer::getState() const {
    return state;
}

std::shared_ptr<Song> MusicPlayer::getCurrentSong() const {
    return currentSong;
}

std::shared_ptr<Playlist> MusicPlayer::getCurrentPlaylist() const {
    return currentPlaylist;
}

int MusicPlayer::getCurrentIndex() const {
    return currentIndex;
}

// Display methods
void MusicPlayer::displayCurrentSong() const {
    if (currentSong) {
        std::cout << "\n▶ Now Playing:" << std::endl;
        currentSong->displayInfo();
    } else {
        std::cout << "No song is currently playing." << std::endl;
    }
}

void MusicPlayer::displayPlayerStatus() const {
    std::cout << "\n=== Player Status ===" << std::endl;
    
    std::string stateStr;
    switch (state) {
        case PlayerState::STOPPED: stateStr = "Stopped"; break;
        case PlayerState::PLAYING: stateStr = "Playing"; break;
        case PlayerState::PAUSED: stateStr = "Paused"; break;
    }
    std::cout << "State: " << stateStr << std::endl;
    
    if (currentSong) {
        std::cout << "Current Song: " << *currentSong << std::endl;
    }
    
    if (currentPlaylist) {
        std::cout << "Current Playlist: " << currentPlaylist->getName() << std::endl;
        std::cout << "Track: " << (currentIndex + 1) << " / " 
                  << currentPlaylist->getSongCount() << std::endl;
    }
    
    std::cout << "Shuffle: " << (shuffleMode ? "ON" : "OFF") << std::endl;
    
    std::string repeatStr;
    switch (repeatMode) {
        case RepeatMode::NONE: repeatStr = "OFF"; break;
        case RepeatMode::ONE: repeatStr = "Repeat One"; break;
        case RepeatMode::ALL: repeatStr = "Repeat All"; break;
    }
    std::cout << "Repeat: " << repeatStr << std::endl;
    std::cout << "Queue Size: " << playQueue.size() << std::endl;
}