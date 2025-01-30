#include "./../../minishell.h"

void exec_clear(void)
{
    // First move cursor to top-left corner
    write(STDOUT_FILENO, "\033[H", 3);
    
    // Clear entire screen and scrollback buffer
    write(STDOUT_FILENO, "\033[3J", 4);
    
    // Clear screen from cursor to end
    write(STDOUT_FILENO, "\033[J", 3);
    
    // Move cursor to top again (some terminals might need this)
    write(STDOUT_FILENO, "\033[H", 3);
}