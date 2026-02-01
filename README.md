# CP Killer

A lightweight, CPH-style competitive programming judge for VS Code that seamlessly integrates with Competitive Companion to sync test cases and run them against your solution with a single keystroke.

## What is CP Killer?

CP Killer is a streamlined competitive programming testing environment that combines:
- **VS Code Extension**: One-key command to compile and test your solutions
- **Local Judge**: Automated test runner with colored output (Accepted/Wrong Answer/TLE)
- **Test Case Management**: Easy addition of manual test cases or sync from Competitive Companion
- **Stress Testing**: Compare your solution against a brute-force implementation

## Features

- 🚀 **Single-File Workflow**: All solutions go in `sol.cpp`
- ⚡ **One-Key Testing**: Run all tests with a single VS Code command
- 🔗 **Competitive Companion Integration**: Automatically sync test cases from online judges
- ✅ **Colored Output**: Green for AC, Red for WA, Yellow for TLE
- 🧪 **Manual Test Addition**: Easily add custom test cases via `addtest` script
- 🔄 **Stress Testing**: Compare against brute-force with automated random testing
- ⏱️ **Time Limit Detection**: 5-second TLE detection for hung programs (hardcoded in judge)

## Prerequisites

- **Linux/Unix Environment** (or WSL on Windows)
- **g++** compiler with C++23 support
- **VS Code** (for the extension)
- **Node.js and npm** (for building the VS Code extension)

## Installation

### Step 1: Clone and Setup Template Files

```bash
# Clone the repository
git clone https://github.com/zapwiz22/cp-killer.git
cd cp-killer

# Install template files to your home directory
mkdir -p $HOME/scripts
cp -r . $HOME/scripts/cp-killer
```

### Step 2: Build the VS Code Extension

```bash
# From the cp-killer directory
cd zapwiz22-cp-killer
npm install
npm run package
```

### Step 3: Install the Extension in VS Code

1. Open VS Code
2. Press `Ctrl+Shift+P` (or `Cmd+Shift+P` on Mac)
3. Type "Install from VSIX"
4. Navigate to `zapwiz22-cp-killer` directory and select the generated `.vsix` file

### Step 4: Setup a Problem Directory

For each problem you want to solve:

```bash
# Navigate to your problem directory
cd /path/to/your/problem/folder

# Run the setup script (use full path or add to PATH)
$HOME/scripts/cp-killer/cpsetup
```

**Optional**: Add to your shell's PATH for easier access:
```bash
# Add to ~/.bashrc or ~/.zshrc
export PATH="$PATH:$HOME/scripts/cp-killer"
```

After adding to PATH, you can simply run:
```bash
cpsetup
```

This will copy all necessary files and compile the server and judge.

## Usage

### Basic Workflow

1. **Write your solution** in `sol.cpp`
2. **Add test cases** using one of these methods:
   - Use Competitive Companion browser extension (automatically sends to local server)
   - Manually add tests with `./addtest` script
3. **Run tests** using the VS Code command palette (`Ctrl+Shift+P`) → "CP Killer: Run"

### Adding Test Cases Manually

```bash
./addtest
```

Then:
1. Enter the input (press Ctrl+D when done)
2. Enter the expected output (press Ctrl+D when done)

### Stress Testing

Compare your solution against a brute-force implementation:

**Linux:**
```bash
./stress
```

**Windows:**
```batch
stress.bat [numTests] [doCompile]
```

You need to provide three files:
- `sol.cpp` - Your optimized solution
- `brute.cpp` - A correct but slow brute-force solution
- `gen.cpp` - Random test case generator

The stress script will run up to 1000 tests (Linux) or a specified number (Windows) and stop if it finds a discrepancy.

## File Structure

```
cp-killer/
├── cpsetup              # Setup script to initialize a problem directory
├── addtest              # Script to manually add test cases
├── stress               # Linux stress testing script
├── stress.bat           # Windows stress testing script
├── server.cpp           # HTTP server to receive tests from Competitive Companion
├── judge.cpp            # Main judge that compiles and runs tests
├── sol.cpp              # Your solution file (empty template)
├── httplib.h            # HTTP library for server
├── tests.db             # Database file storing test cases
└── zapwiz22-cp-killer/  # VS Code extension source
    ├── src/
    │   └── extension.ts # Extension entry point
    └── package.json     # Extension manifest
```

## How It Works

1. **Competitive Companion** sends test cases via HTTP POST to `localhost:27122`
2. **Server** (`server.cpp`) receives and stores tests in `tests.db`
3. **VS Code Extension** triggers the judge with a single command
4. **Judge** (`judge.cpp`) compiles `sol.cpp` and runs all tests from `tests.db`
5. Results are displayed with colored output in the VS Code terminal

## Test Case Format

Test cases are stored in `tests.db` with this format:

```
###
[input]
@@@
[expected output]
###
[next input]
@@@
[next expected output]
```

## Keybindings (Optional)

You can add a keyboard shortcut for the "CP Killer: Run" command:

1. Open VS Code settings (`Ctrl+K Ctrl+S`)
2. Search for "CP Killer: Run"
3. Assign your preferred keybinding (e.g., `Ctrl+Alt+R`)

## Troubleshooting

### Server fails to start
- Ensure port 27122 is not in use: `lsof -i :27122`
- Kill any existing server: `pkill server`

### Tests not syncing from Competitive Companion
- Verify the server is running: `ps aux | grep server`
- Check Competitive Companion settings point to `http://localhost:27122`

### Compilation errors
- Ensure g++ supports C++23: `g++ --version`
- Update g++ if necessary

## License

This project is open source. Feel free to use and modify as needed.

## Contributing

Contributions are welcome! Feel free to open issues or submit pull requests.
