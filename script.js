// Data Storage (simulating C++ backend data)
let library = {
    songs: [],
    playlists: [],
    currentSong: null,
    isPlaying: false,
    shuffleMode: false,
    repeatMode: 'none', // 'none', 'one', 'all'
    queue: []
};

// Sample Data
const sampleSongs = [
    { id: 1, title: "Blinding Lights", artist: "The Weeknd", album: "After Hours", duration: 200, genre: "Pop", playCount: 15 },
    { id: 2, title: "Levitating", artist: "Dua Lipa", album: "Future Nostalgia", duration: 203, genre: "Pop", playCount: 12 },
    { id: 3, title: "Circles", artist: "Post Malone", album: "Hollywood's Bleeding", duration: 215, genre: "Pop", playCount: 8 },
    { id: 4, title: "Watermelon Sugar", artist: "Harry Styles", album: "Fine Line", duration: 174, genre: "Pop", playCount: 10 },
    { id: 5, title: "Save Your Tears", artist: "The Weeknd", album: "After Hours", duration: 215, genre: "Pop", playCount: 7 },
    { id: 6, title: "Peaches", artist: "Justin Bieber", album: "Justice", duration: 198, genre: "Pop", playCount: 5 },
    { id: 7, title: "Good 4 U", artist: "Olivia Rodrigo", album: "Sour", duration: 178, genre: "Pop Rock", playCount: 13 },
    { id: 8, title: "Stay", artist: "The Kid LAROI", album: "F*ck Love 3", duration: 141, genre: "Pop", playCount: 9 }
];

const samplePlaylists = [
    { id: 1, name: "My Favorites", description: "Best songs ever!", songIds: [1, 2, 4] },
    { id: 2, name: "Workout Mix", description: "Get pumped!", songIds: [2, 3, 5] },
    { id: 3, name: "Chill Vibes", description: "Relax and unwind", songIds: [3, 4, 6, 8] }
];

// Initialize App
document.addEventListener('DOMContentLoaded', () => {
    loadSampleData();
    initializeNavigation();
    renderLibrary();
    renderPlaylists();
    renderSidebarPlaylists();
    renderGenres();
    updateStatistics();
});

// Load Sample Data
function loadSampleData() {
    library.songs = [...sampleSongs];
    library.playlists = [...samplePlaylists];
}

// Navigation
function initializeNavigation() {
    const navBtns = document.querySelectorAll('.nav-btn');
    navBtns.forEach(btn => {
        btn.addEventListener('click', () => {
            const section = btn.dataset.section;
            showSection(section);
            
            // Update active nav button
            navBtns.forEach(b => b.classList.remove('active'));
            btn.classList.add('active');
        });
    });
}

function showSection(sectionId) {
    const sections = document.querySelectorAll('.section');
    sections.forEach(section => {
        section.classList.remove('active');
    });
    document.getElementById(sectionId).classList.add('active');
}

// Render Library
function renderLibrary() {
    const container = document.getElementById('libraryContent');
    container.innerHTML = '';
    
    library.songs.forEach((song, index) => {
        const songElement = createSongElement(song, index + 1);
        container.appendChild(songElement);
    });
}

function createSongElement(song, index) {
    const div = document.createElement('div');
    div.className = 'song-item';
    div.innerHTML = `
        <div class="song-number">${index}</div>
        <div class="song-title">${song.title}</div>
        <div class="song-artist">${song.artist}</div>
        <div class="song-album">${song.album}</div>
        <div class="song-duration">${formatDuration(song.duration)}</div>
        <div class="song-actions">
            <button class="icon-btn" onclick="playSong(${song.id})" title="Play">▶️</button>
            <button class="icon-btn" onclick="addToQueue(${song.id})" title="Add to Queue">➕</button>
        </div>
    `;
    return div;
}

// Render Playlists
function renderPlaylists() {
    const container = document.getElementById('playlistsContent');
    container.innerHTML = '';
    
    library.playlists.forEach(playlist => {
        const playlistElement = createPlaylistCard(playlist);
        container.appendChild(playlistElement);
    });
}

function createPlaylistCard(playlist) {
    const div = document.createElement('div');
    div.className = 'playlist-card';
    div.onclick = () => viewPlaylist(playlist.id);
    div.innerHTML = `
        <div class="playlist-cover">🎵</div>
        <h3>${playlist.name}</h3>
        <p>${playlist.description}</p>
        <p>${playlist.songIds.length} songs</p>
    `;
    return div;
}

// Sidebar Playlists
function renderSidebarPlaylists() {
    const container = document.getElementById('playlistList');
    container.innerHTML = '';
    
    library.playlists.forEach(playlist => {
        const div = document.createElement('div');
        div.className = 'playlist-item';
        div.textContent = `📝 ${playlist.name}`;
        div.onclick = () => viewPlaylist(playlist.id);
        container.appendChild(div);
    });
}

// Genres
function renderGenres() {
    const container = document.getElementById('genreList');
    const genres = [...new Set(library.songs.map(s => s.genre))];
    container.innerHTML = '';
    
    genres.forEach(genre => {
        const div = document.createElement('div');
        div.className = 'genre-item';
        div.textContent = `🎸 ${genre}`;
        div.onclick = () => filterByGenre(genre);
        container.appendChild(div);
    });
}

// Player Functions
function playSong(songId) {
    const song = library.songs.find(s => s.id === songId);
    if (!song) return;
    
    library.currentSong = song;
    library.isPlaying = true;
    song.playCount++;
    
    updatePlayerUI();
    updateStatistics();
    
    // Show notification
    showNotification(`Now Playing: ${song.title} by ${song.artist}`);
}

function updatePlayerUI() {
    const song = library.currentSong;
    if (!song) return;
    
    document.getElementById('currentSongTitle').textContent = song.title;
    document.getElementById('currentSongArtist').textContent = song.artist;
    document.getElementById('currentSongAlbum').textContent = song.album;
    
    const playBtn = document.querySelector('.play-btn');
    playBtn.textContent = library.isPlaying ? '⏸️' : '▶️';
}

function togglePlay() {
    if (!library.currentSong) {
        showNotification('No song selected');
        return;
    }
    
    library.isPlaying = !library.isPlaying;
    updatePlayerUI();
    
    showNotification(library.isPlaying ? 'Playing' : 'Paused');
}

function nextSong() {
    if (!library.currentSong) return;
    
    const currentIndex = library.songs.findIndex(s => s.id === library.currentSong.id);
    const nextIndex = (currentIndex + 1) % library.songs.length;
    playSong(library.songs[nextIndex].id);
}

function previousSong() {
    if (!library.currentSong) return;
    
    const currentIndex = library.songs.findIndex(s => s.id === library.currentSong.id);
    const prevIndex = currentIndex === 0 ? library.songs.length - 1 : currentIndex - 1;
    playSong(library.songs[prevIndex].id);
}

function addToQueue(songId) {
    const song = library.songs.find(s => s.id === songId);
    if (!song) return;
    
    library.queue.push(song);
    updateQueueUI();
    showNotification(`Added "${song.title}" to queue`);
}

function updateQueueUI() {
    const container = document.getElementById('queueList');
    container.innerHTML = '';
    
    if (library.queue.length === 0) {
        container.innerHTML = '<p style="color: var(--text-secondary);">Queue is empty</p>';
        return;
    }
    
    library.queue.forEach((song, index) => {
        const div = document.createElement('div');
        div.className = 'song-item';
        div.innerHTML = `
            <div class="song-number">${index + 1}</div>
            <div class="song-title">${song.title}</div>
            <div class="song-artist">${song.artist}</div>
            <div class="song-actions">
                <button class="icon-btn" onclick="removeFromQueue(${index})">❌</button>
            </div>
        `;
        container.appendChild(div);
    });
}

function removeFromQueue(index) {
    library.queue.splice(index, 1);
    updateQueueUI();
}

function toggleShuffle() {
    library.shuffleMode = !library.shuffleMode;
    const btn = document.getElementById('shuffleBtn');
    btn.classList.toggle('active');
    showNotification(`Shuffle ${library.shuffleMode ? 'ON' : 'OFF'}`);
}

function toggleRepeat() {
    const modes = ['none', 'one', 'all'];
    const currentIndex = modes.indexOf(library.repeatMode);
    library.repeatMode = modes[(currentIndex + 1) % modes.length];
    
    const btn = document.getElementById('repeatBtn');
    if (library.repeatMode === 'none') {
        btn.classList.remove('active');
        btn.textContent = '🔁';
    } else if (library.repeatMode === 'one') {
        btn.classList.add('active');
        btn.textContent = '🔂';
    } else {
        btn.classList.add('active');
        btn.textContent = '🔁';
    }
    
    showNotification(`Repeat: ${library.repeatMode.toUpperCase()}`);
}

// Search
function searchSongs() {
    const query = document.getElementById('searchInput').value.toLowerCase();
    const results = library.songs.filter(song => 
        song.title.toLowerCase().includes(query) ||
        song.artist.toLowerCase().includes(query) ||
        song.album.toLowerCase().includes(query)
    );
    
    const container = document.getElementById('libraryContent');
    container.innerHTML = '';
    
    if (results.length === 0) {
        container.innerHTML = '<p style="color: var(--text-secondary);">No songs found</p>';
        return;
    }
    
    results.forEach((song, index) => {
        const songElement = createSongElement(song, index + 1);
        container.appendChild(songElement);
    });
}

// Filter by Genre
function filterByGenre(genre) {
    const filtered = library.songs.filter(s => s.genre === genre);
    const container = document.getElementById('libraryContent');
    container.innerHTML = '';
    
    filtered.forEach((song, index) => {
        const songElement = createSongElement(song, index + 1);
        container.appendChild(songElement);
    });
    
    showNotification(`Filtered by: ${genre}`);
}

// Statistics
function updateStatistics() {
    document.getElementById('totalSongs').textContent = library.songs.length;
    document.getElementById('totalArtists').textContent = 
        new Set(library.songs.map(s => s.artist)).size;
    document.getElementById('totalAlbums').textContent = 
        new Set(library.songs.map(s => s.album)).size;
    document.getElementById('totalPlaylists').textContent = library.playlists.length;
    
    renderMostPlayed();
}

function renderMostPlayed() {
    const container = document.getElementById('mostPlayedList');
    const sorted = [...library.songs].sort((a, b) => b.playCount - a.playCount).slice(0, 5);
    
    container.innerHTML = '';
    sorted.forEach((song, index) => {
        const div = document.createElement('div');
        div.className = 'song-item';
        div.innerHTML = `
            <div class="song-number">${index + 1}</div>
            <div class="song-title">${song.title}</div>
            <div class="song-artist">${song.artist}</div>
            <div class="song-duration">${song.playCount} plays</div>
            <div class="song-actions">
                <button class="icon-btn" onclick="playSong(${song.id})">▶️</button>
            </div>
        `;
        container.appendChild(div);
    });
}

// View Playlist
function viewPlaylist(playlistId) {
    const playlist = library.playlists.find(p => p.id === playlistId);
    if (!playlist) return;
    
    showSection('library');
    const container = document.getElementById('libraryContent');
    container.innerHTML = `<h3 style="margin-bottom: 20px;">Playlist: ${playlist.name}</h3>`;
    
    playlist.songIds.forEach((songId, index) => {
        const song = library.songs.find(s => s.id === songId);
        if (song) {
            const songElement = createSongElement(song, index + 1);
            container.appendChild(songElement);
        }
    });
}

// Modal Functions
function showAddSongModal() {
    document.getElementById('addSongModal').classList.add('active');
}

function showCreatePlaylistModal() {
    document.getElementById('createPlaylistModal').classList.add('active');
}

function closeModal(modalId) {
    document.getElementById(modalId).classList.remove('active');
}

// Form Submissions
document.getElementById('addSongForm').addEventListener('submit', (e) => {
    e.preventDefault();
    
    const newSong = {
        id: library.songs.length + 1,
        title: document.getElementById('songTitle').value,
        artist: document.getElementById('songArtist').value,
        album: document.getElementById('songAlbum').value,
        duration: parseInt(document.getElementById('songDuration').value),
        genre: document.getElementById('songGenre').value,
        playCount: 0
    };
    
    library.songs.push(newSong);
    renderLibrary();
    renderGenres();
    updateStatistics();
    closeModal('addSongModal');
    e.target.reset();
    showNotification('Song added successfully!');
});

document.getElementById('createPlaylistForm').addEventListener('submit', (e) => {
    e.preventDefault();
    
    const newPlaylist = {
        id: library.playlists.length + 1,
        name: document.getElementById('playlistName').value,
        description: document.getElementById('playlistDescription').value,
        songIds: []
    };
    
    library.playlists.push(newPlaylist);
    renderPlaylists();
    renderSidebarPlaylists();
    updateStatistics();
    closeModal('createPlaylistModal');
    e.target.reset();
    showNotification('Playlist created successfully!');
});

// Utility Functions
function formatDuration(seconds) {
    const mins = Math.floor(seconds / 60);
    const secs = seconds % 60;
    return `${mins}:${secs.toString().padStart(2, '0')}`;
}

function showNotification(message) {
    // Simple notification (you can enhance this)
    console.log('Notification:', message);
    
    // Create a temporary notification element
    const notif = document.createElement('div');
    notif.style.cssText = `
        position: fixed;
        top: 80px;
        right: 20px;
        background: linear-gradient(135deg, var(--primary), var(--secondary));
        color: white;
        padding: 15px 25px;
        border-radius: 10px;
        z-index: 1000;
        animation: slideIn 0.3s ease;
    `;
    notif.textContent = message;
    document.body.appendChild(notif);
    
    setTimeout(() => {
        notif.style.animation = 'slideOut 0.3s ease';
        setTimeout(() => notif.remove(), 300);
    }, 2000);
}

// Filter buttons
document.querySelectorAll('.filter-btn').forEach(btn => {
    btn.addEventListener('click', () => {
        document.querySelectorAll('.filter-btn').forEach(b => b.classList.remove('active'));
        btn.classList.add('active');
        
        const filter = btn.dataset.filter;
        if (filter === 'all') {
            renderLibrary();
        }
        // Add other filters as needed
    });
});

// Close modal on outside click
document.querySelectorAll('.modal').forEach(modal => {
    modal.addEventListener('click', (e) => {
        if (e.target === modal) {
            modal.classList.remove('active');
        }
    });
});

// Add CSS animation styles
const style = document.createElement('style');
style.textContent = `
    @keyframes slideIn {
        from {
            transform: translateX(400px);
            opacity: 0;
        }
        to {
            transform: translateX(0);
            opacity: 1;
        }
    }
    
    @keyframes slideOut {
        from {
            transform: translateX(0);
            opacity: 1;
        }
        to {
            transform: translateX(400px);
            opacity: 0;
        }
    }
`;
document.head.appendChild(style);