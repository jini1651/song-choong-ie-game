#include <ncurses.h>
#include "setting.h"

using namespace std;

int kbhit(void)    /* comment */
{
    int ch, r;

    // turn off getch() blocking and echo
    nodelay(win_map, TRUE);
    noecho();

    // check for input
    ch = wgetch(win_map);
    if( ch == ERR)      // no input
            r = FALSE;
    else                // input
    {
            r = TRUE;
            ungetch(ch);
    }

    // restore block and echo
    echo();
    nodelay(win_map, FALSE);
    return(r);
}
