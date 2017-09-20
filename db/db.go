// package db provides a shared object containing all of PMS' data.
package db

import (
	pms_mpd "github.com/ambientsound/pms/mpd"
	"github.com/ambientsound/pms/options"
	"github.com/ambientsound/pms/song"
	"github.com/ambientsound/pms/songlist"
)

// Instance holds state related to mutable data within PMS, such as the current
// state of MPD, any songlists, clipboards, options.
type Instance struct {
	// mpd state
	mpdStatus   pms_mpd.PlayerStatus
	currentSong *song.Song

	// song lists
	queue      *songlist.Queue
	library    *songlist.Library
	songlists  []songlist.Songlist
	clipboards map[string]songlist.Songlist
	options    *options.Options

	// panels
	left  *songlist.Collection
	right *songlist.Collection
}

// New returns Instance.
func New() *Instance {
	return &Instance{
		clipboards: make(map[string]songlist.Songlist, 0),
		left:       songlist.NewCollection(),
		right:      songlist.NewCollection(),
	}
}

// Clipboard returns a named clipboard.
func (db *Instance) Clipboard(key string) songlist.Songlist {
	_, ok := db.clipboards[key]
	if !ok {
		db.clipboards[key] = songlist.New()
	}
	return db.clipboards[key]
}

// Queue returns the MPD queue.
func (db *Instance) Queue() *songlist.Queue {
	return db.queue
}

// SetQueue sets the MPD queue.
func (db *Instance) SetQueue(queue *songlist.Queue) {
	db.queue = queue
}

// Library returns the MPD library.
func (db *Instance) Library() *songlist.Library {
	return db.library
}

// SetLibrary sets the MPD library.
func (db *Instance) SetLibrary(library *songlist.Library) {
	db.library = library
}

// Panel returns the active panel. At the moment, there is only one panel.
func (db *Instance) Panel() *songlist.Collection {
	return db.Left()
}

// Left returns the left panel.
func (db *Instance) Left() *songlist.Collection {
	return db.left
}

// Right returns the right panel.
func (db *Instance) Right() *songlist.Collection {
	return db.right
}
