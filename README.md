# ⚔️ CP Killer

> **A comprehensive competitive programming environment with stress testing, judging, and VS Code integration.**

CP Killer is a complete toolkit for competitive programming that includes:
- 🎯 One-key judging with CPH-style interface
- 🔄 Stress testing with random test generation
- 🌐 Test case syncing from Competitive Companion
- 📦 VS Code extension for seamless workflow
- ⚡ Fast local testing and debugging

---

## 📋 Table of Contents

- [Features](#-features)
- [Quick Setup](#-quick-setup)
- [File Structure](#-file-structure)
- [Usage](#-usage)
  - [Initial Setup](#1-initial-setup)
  - [Receiving Test Cases](#2-receiving-test-cases)
  - [Running Tests](#3-running-tests)
  - [Stress Testing](#4-stress-testing)
  - [Adding Manual Tests](#5-adding-manual-tests)
- [VS Code Extension](#-vs-code-extension)
- [Requirements](#-requirements)

---

## ✨ Features

### 🏆 Core Functionality

- **Smart Judge System** - Automated compilation and testing with colored output (AC/WA/TLE)
- **Stress Testing** - Compare your solution against a brute force with random inputs
- **Test Management** - Sync test cases from Competitive Companion or add manually
- **Cross-Platform** - Works on Linux/macOS (bash) and Windows (batch scripts)

### 📁 Key Files

| File | Purpose |
|------|---------|
| `sol.cpp` | Your main solution |
| `gen.cpp` | Random test case generator |
| `brute.cpp` | Brute force solution for validation |
| `judge.cpp` | Test runner with colored output |
| `server.cpp` | HTTP server for Competitive Companion |
| `tests.db` | Test case database |
| `stress` / `stress.bat` | Stress testing scripts |
| `cpsetup` | Setup script for new problem |
| `addtest` | Manually add test cases |

---

## 🚀 Quick Setup

### Prerequisites

- **C++ Compiler** (g++ with C++23 support)
- **Optional**: [Competitive Companion](https://github.com/jmerle/competitive-companion) browser extension

### Installation

```bash
# Clone the repository
git clone https://github.com/zapwiz22/cp-killer.git
cd cp-killer

# Make scripts executable (Linux/macOS)
chmod +x cpsetup stress addtest

# Copy template to your scripts directory (optional)
mkdir -p ~/scripts
cp -r . ~/scripts/cp-killer
```

---

## 📁 File Structure

```
cp-killer/
├── sol.cpp              # Your solution goes here
├── brute.cpp            # Brute force solution for stress testing
├── gen.cpp              # Random test generator
├── judge.cpp            # Local judge system
├── server.cpp           # Competitive Companion server
├── httplib.h            # HTTP library for server
├── tests.db             # Test case storage
├── cpsetup              # Setup script (bash)
├── addtest              # Add test manually (bash)
├── stress               # Stress test (bash)
├── stress.bat           # Stress test (Windows)
└── zapwiz22-cp-killer/  # VS Code extension
```

---

## 📖 Usage

### 1. Initial Setup

For a new problem, run the setup script:

```bash
./cpsetup
```

This will:
- Copy all CP Killer files to your current directory
- Compile the server and judge
- Make scripts executable

### 2. Receiving Test Cases

#### Option A: Using Competitive Companion (Recommended)

1. Start the server:
```bash
./server
```

2. Open the problem in your browser
3. Click the Competitive Companion extension
4. Test cases will be automatically saved to `tests.db`

#### Option B: Manual Entry

```bash
./addtest
# Enter input (Ctrl+D when done)
# Enter expected output (Ctrl+D when done)
```

### 3. Running Tests

Write your solution in `sol.cpp`, then run:

```bash
./judge
```

**Output Format:**
- 🟢 **Accepted** - Your output matches expected output
- 🔴 **Wrong Answer** - Output mismatch (shows expected vs actual)
- 🟡 **Time Limit Exceeded** - Execution took more than 5 seconds

**Example Output:**
```
Test 1: Accepted
Test 2: Wrong Answer
Expected: 
42
Got: 
43
Test 3: Time Limit Exceeded!
```

### 4. Stress Testing

Stress testing compares your solution against a brute force solution with randomly generated inputs.

#### Setup

1. **Implement `gen.cpp`** - Random test case generator
   ```cpp
   #include <bits/stdc++.h>
   using namespace std;
   
   #define int long long 
   #define uid(a, b) uniform_int_distribution<int>(a, b)(rng)
   mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
   
   int32_t main() {
       int tests = 1;
       cout << tests << endl;
       
       // Generate your test case
       int n = uid(1, 100);  // Random n between 1 and 100
       cout << n << endl;
       
       return 0;
   }
   ```

2. **Implement `brute.cpp`** - Simple, correct solution (can be slow)

3. **Write your optimized solution in `sol.cpp`**

#### Running Stress Tests

**Linux/macOS:**
```bash
./stress
```
Runs 1000 test cases by default.

**Windows:**
```bat
stress.bat [numTests] [doCompile]
```
- `numTests`: Number of iterations (default: 100)
- `doCompile`: 1 to compile, 0 to skip (default: 1)

**Example:**
```bat
stress.bat 1000 1     # Run 1000 tests with compilation
stress.bat 500 0      # Run 500 tests, skip compilation
```

**What It Does:**
- Compiles all three programs (gen, sol, brute)
- Generates random test cases using `gen`
- Runs both `sol` and `brute` on each test
- Compares outputs using `diff`
- Stops immediately when a difference is found
- Shows the failing test case

### 5. Adding Manual Tests

```bash
./addtest
```

Then provide:
1. Input (press Ctrl+D when finished)
2. Expected output (press Ctrl+D when finished)

The test is appended to `tests.db`.

---

## 🔌 VS Code Extension

The `zapwiz22-cp-killer` directory contains a VS Code extension for enhanced workflow.

### Features
- One-key testing integration
- Automatic test case management
- Integrated with Competitive Companion

### Installation
1. Open the `zapwiz22-cp-killer` folder in VS Code
2. Press F5 to run the extension in development mode
3. Or package and install: `vsce package` then install the `.vsix` file

---

## 🛠 Requirements

- **C++ Compiler**: g++ with C++23 support
- **OS**: Linux, macOS, or Windows
- **Optional**: 
  - [nlohmann/json](https://github.com/nlohmann/json) - For server (included in httplib.h build)
  - Competitive Companion browser extension
  - VS Code (for extension)

---

## 📝 Test Database Format

Tests are stored in `tests.db` with the following format:

```
###
<input>
@@@
<output>
###
<input>
@@@
<output>
...
```

Each test case is delimited by `###`, with input and output separated by `@@@`.

---

## 🎯 Workflow Example

```bash
# 1. Setup for new problem
./cpsetup

# 2. Start server and get test cases
./server  # In terminal 1
# Click Competitive Companion in browser

# 3. Write solution in sol.cpp

# 4. Test your solution
./judge

# 5. If WA, debug with stress testing
# - Implement gen.cpp (random inputs)
# - Implement brute.cpp (correct but slow)
./stress  # Finds failing case automatically

# 6. Fix solution and repeat
./judge
```

---

## 🤝 Contributing

Feel free to open issues or submit pull requests for improvements!

---

## 📜 License

This project is open source and available for competitive programming use.

---

**Happy Coding! 🚀**
