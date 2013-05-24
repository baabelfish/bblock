# BbLock

*BbLock* is ncurses-based lock for terminal inspired by **i3lock**.

## Installation
    git clone https://github.com/baabelfish/bblock.git
    cd bblock
    make

## Usage
### Tmux
Add following to ~/tmux.conf

    set-option -g lock-command /path/to/bblock

### Screen
Set `$LOCKPRG` variable to `/path/to/bblock`
