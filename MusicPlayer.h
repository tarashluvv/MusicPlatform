#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include "Song.h"
#include "Playlist.h"
#include <memory>
#include <queue>

enum class PlayerState {
    STOPPED,
    PLAYING,
    PAUSED
};

enum class RepeatMode {
    NONE,
    ONE,
    ALL
};

class MusicPlayer {
private:
    std::shared_ptr<Song> currentSong;
    std::shared_ptr<Playlist> currentPlaylist;
    PlayerState state;
    RepeatMode repeatMode;
    bool shuffleMode;
    int currentIndex;
    std::queue<std::shared_ptr<Song>> playQueue;
    
    // Private helper methods
    void playNextInQueue();
    
public:
    // Constructor and Destructor
    MusicPlayer();
    ~MusicPlayer();
    
    // Playback control
    void play(std::shared_ptr<Song> song);
    void playPlaylist(std::shared_ptr<Playlist> playlist, int startIndex = 0);
    void pause();
    void resume();
    void stop();
    void next();
    void previous();
    
    // Queue management
    void addToQueue(std::shared_ptr<Song> song);
    void clearQueue();
    int getQueueSize() const;
    
    // Playback modes
    void setShuffleMode(bool enabled);
    void setRepeatMode(RepeatMode mode);
    bool isShuffleEnabled() const;
    RepeatMode getRepeatMode() const;
    
    // Status methods
    PlayerState getState() const;
    std::shared_ptr<Song> getCurrentSong() const;
    std::shared_ptr<Playlist> getCurrentPlaylist() const;
    int getCurrentIndex() const;
    
    // Display methods
    void displayCurrentSong() const;
    void displayPlayerStatus() const;
};

#endif // MUSICPLAYER_H