#  Introduction to Emacs

**彭贻豪 2019013255**

---

### Features

- Strong extendibility
- Multi-platform
- Open-source

### Installation

```bash
sudo apt-get install emacs # Installs emacs
emacs --version            # Checks emacs version
```

### Abbreviations

- ``C-<chr>``

  It means hold the ``CONTROL`` key while typing the character ``<chr>``. 

  Thus, ``C-f`` would be: hold the ``CONTROL`` key and type ``f``.

- ``M-<chr>``

  It means hold the  ``META`` or ``EDIT`` or ``ALT`` key down while typing ``<chr>``.

  If there is no ``META``, ``EDIT``, ``ALT`` key, instead press and release the ``ESC`` key and then type ``<chr>``.

### Key bindings

1. To quit, save and open file

   - ``C-x C-c``

     End the emacs session.

   - ``C-g``

     Quit a partially entered command.

   - ``C-x C-s``

     Save the text you are editing.

   - ``C-x C-f <file-name>``

     Open the file you want to edit.

2. To view screenfuls

   - ``C-v``

     Move forward one screenful.

   - ``M-v``

     Move backward one screenful.

   - ``C-l (available in terminal)``

     Clear screen and redisplay all the text, moving the text around the cursor to the center of the screen. Type twice to move the text to the top, and type three times to move to the bottom.

3. Cursor-moving

   | Command                         | Function                           |
   | ------------------------------- | ---------------------------------- |
   | ``C-f (available in terminal)`` | Move forward a character           |
   | ``C-b (available in terminal)`` | Move backward a character          |
   | ``M-f (available in terminal)`` | Move forward a word                |
   | ``M-b (available in terminal)`` | Move backward a word               |
   | ``C-n (available in terminal)`` | Move to next line                  |
   | ``C-p (available in terminal)`` | Move to previous line              |
   | ``C-a (available in terminal)`` | Move to beginning of line          |
   | ``C-e (available in terminal)`` | Move to end of line                |
   | ``M-a``                         | Move back to beginning of sentence |
   | ``M-e``                         | Move foward to end of sentence     |

4. Basic editing

   - ``C-d (available in terminal)``

     Delete the next character after the cursor.

   - ``M-<DEL> (available in terminal)``

     Kill the word immediately before the cursor. 

     ``<DEL>`` is the key on the keyboard usually labeled ``backspace`` — the same one you normally use, outside Emacs, to delete the last character typed. It's different from the key ``delete``.

   - ``M-d (available in terminal)``

     Kill the next word after the cursor.

   - ``C-k (available in terminal)``

     Kill from the cursor position to end of line.

   - ``M-k``

     Kill to the end of the current sentence.

5. Manage the windows

   - ``C-x 2``

     Split the screen into two horizontal windows.

   - ``C-x 3``

     Split the screen into two vertical windows.

   - ``C-x 1``

     Keep just one window that I am already in.

   - ``C-x 4 C-f <file-name>``

     See the specified file appear in the bottom window.

   - ``C-x o``

     Switch between the windows.

   - ``C-M-v``

     Scroll the text in the other window without leaving the selected window.

### Extendibility

- Emacs lisp.
  - A language.
  - ``~/.emacs.d/init.el``
  - ``~/.emacs``
  - ``M-x <command``
  - *https://www.gnu.org/software/emacs/manual/html__node/elisp/*

- Plugins

  有哪些是必备的 emacs 扩展？- 知乎

