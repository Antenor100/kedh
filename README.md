# KEDH - Keyboard Event Device Handler
The traditional way to bind keys to shell commands in Linux is to use the `xbindkeys` program. However, `xbindkeys` has some limitations, such as requiring X11 and not being able to handle certain key combinations.

This is a simple keyboard event handler that allows you to bind key combinations to shell commands. It is designed to work with Linux systems and can be used to create custom shortcuts for various tasks.

It is particularly useful for taking screenshots, launching applications, or executing scripts with specific key combinations.

&nbsp;
## Folders Configuration
KEDH uses configuration files located in the `~/.kedh/` directory.

The folder needs to be created manually on your HOME, and the configuration file must be created as well.

1. Create the .kedh directory:
   ```bash
   mkdir -p ~/.kedh
   ```

2. Create the keybinds configuration file:
   ```bash
   touch ~/.kedh/.keybinds
   ```

3. Set appropriate permissions:
   ```bash
   chmod 600 ~/.kedh/.keybinds
   ```

&nbsp;
## Usage
1. Clone the repository, the program is located in the `/build` folder:

2. Edit the keybinds file at `~/.kedh/.keybinds` (see below)

3. Install `libevdev-dev` if not already installed:
   ```bash
   sudo apt-get install libevdev-dev
   ```

4. On the first run, you will be prompted to select the keyboard device. You can also specify the device directly using the `-c` option. After choosing the device, the program will start monitoring key events.
   ```
   ./kedh -c
   ```
   If you prefer and your devices index always changes, you can use the `-n` option to choose the device by name:
   ```
   ./kedh -n "Your Keyboard Name"
   ```

5. After first run, you can start the program without any options:
   ```
   ./kedh
   ```

6. If you want to run the program in the background, use the `-s` option:
   ```
   ./kedh -s
   ```

7. For run kedh and find de devices event, follow the steps below:
   ```
   sudo nano /etc/udev/rules.d/99-input-permissions.rules
      - content: KERNEL=="event*", SUBSYSTEM=="input", MODE="0777"
   sudo udevadm control --reload-rules
   sudo udevadm trigger
   ls -l /dev/input/event*
   ```

&nbsp;
## .keybinds File Format

The keybinds configuration file allows you to define custom key combinations and their associated shell commands.

#### Syntax

```
key1+key2+key3 = command_to_execute
```

#### Supported Keys
- Alphabet keys: A-Z
- Number keys: 0-9
- Special keys: SPACE, ENTER, ESC, PRINT, BACKSPACE, TAB, SUPER, RIGHT_SUPER
- Special characters: / * - + ` \\ [ ] ; , . =
- Function keys: F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
- Modifier keys: SHIFT, RIGHT_SHIFT, CTRL, RIGHT_CTRL, ALT, RIGHT_ALT


&nbsp;
### Example Configuration

#### Format: key1+key2+key3 = command
```
# Take screenshot using gnome-screenshot
PRINT = gnome-screenshot

# Take screenshot of active window
ALT+PRINT = gnome-screenshot -w

# Take screenshot with 3-second delay
CTRL+PRINT = gnome-screenshot -d 3

# Open screenshot tool
SHIFT+PRINT = gnome-screenshot -i

# Alternative screenshot tools
CTRL+ALT+PRINT = flameshot gui
CTRL+SHIFT+PRINT = spectacle

# Function key examples
F1 = xdg-open ~
F2 = gedit
F3 = firefox
```

&nbsp;
### Creating Macros with xvkbd

While KEDH binds key combinations to *shell commands*, you might want to bind keys to insert specific text snippets (macros). A useful tool for this is `xvkbd`. You can bind a KEDH shortcut to an `xvkbd` command.

`xvkbd` allows you to simulate keyboard input, including special characters. You need to escape characters that have special meaning in the shell or `xvkbd` itself using a backslash (`\`).

**Example:**

To make a KEDH shortcut that types "Olá, quem é você?", you would add this line to your `~/.kedh/.keybinds` file:

```
# Example: Bind CTRL+ALT+T to type a specific phrase
CTRL+ALT+T = xvkbd -text 'Ol\{aacute}, quem \{eacute} voc\{ecircumflex}?'
```

This command tells `xvkbd` to type the specified text. Note the backslashes before `{`, `á`, `é`, and `ê` to ensure they are interpreted correctly.

You may need to install `xvkbd` first:
```bash
sudo apt-get install xvkbd
```

&nbsp;
## Command Line Options

```
./kedh [-c] [-h] [-t] [-v]

Options:
  No params     Start key monitor and run indefinitely
  -c            Choose an event device and start key monitor
  -t            Start in test mode, with logs (exit on ESC)
  -v            Show version information
  -h            Show help message
  -n "name"     Choose an event device by name
  -s            Start kedh in the background (standalone mode)
  -k            Kill the running kedh processes
```


&nbsp;
## Finding the Correct Keyboard Device

To find the correct keyboard device for KEDH, you can use `evtest`:

1. Install evtest if not already installed:
   ```bash
   sudo apt-get install evtest
   ```

2. List all input devices:
   ```bash
   sudo evtest
   ```

3. Identify your keyboard by:
   - Looking for devices with names like "keyboard", "input", or your keyboard's brand
   - Pressing keys and observing which device shows input events

4. Select the correct device path (e.g., `/dev/input/eventX`)

5. When running `./kedh -c`, choose the device path you identified

&nbsp;
## How to make a command shortcut for kedh (call it from anywhere, symbolic link)
1. Create a symbolic link to the KEDH executable in a directory that is in your PATH (e.g., `/usr/local/bin`):
   ```bash
   sudo ln -s /path/to/kedh/build/kedh /usr/local/bin/kedh
   ```

2. Make sure the symbolic link is executable:
   ```bash
   sudo chmod +x /usr/local/bin/kedh
   ```

3. Now you can run KEDH from anywhere in the terminal by simply typing `kedh`.

&nbsp;
## Setting KEDH to init on Linux Mint Startup
1. Open the "Startup Applications" tool in Linux Mint.
2. Click "Add" to create a new startup entry.
3. In the "Name" field, enter "KEDH".
4. In the "Command" field, enter the full path to the KEDH executable (e.g., `/path/to/kedh/build/kedh`).
5. In the "Comment" field, you can enter a description (optional).
6. Put 5s in the "Delay" field to ensure the program starts after the system is ready.
7. Click "Add" to save the entry.
8. Restart your computer to test if KEDH starts automatically.

&nbsp;
## Notes
- Key combinations are order-independent
- Maximum of 5 keys in a combination
- Commands are executed using `/bin/sh -c`
- The program can be terminated by pressing Ctrl+C
- With `-t`, the program exits when ESC is pressed
- After change in the keybinds file, restart the program to apply changes
- If shortcut conflicts with Linux generals happen, please disable what was configured in the system, this probably goes on writing what is in Kedh

&nbsp;
## Building

```bash
make
```

&nbsp;
## Running

```bash
./build/kedh