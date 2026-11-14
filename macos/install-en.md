# 🍎 Installing CLSDH on macOS (English)

> Guide to install CLSDH on macOS using Homebrew or manual compile.

---

## 📋 Requirements

- macOS 10.15 or newer
- Xcode Command Line Tools or Homebrew
- Internet connection

---

## 🚀 Method 1: Homebrew (Recommended)

### 1. Install Homebrew (if not installed)
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

### 2. Install Compiler
```bash
brew install gcc
```

### 3. Clone and Compile
```bash
git clone https://github.com/iky-art/CLSDH.git
cd CLSDH
g++ -std=c++11 -O2 -pthread clsdh.cpp -o clsdh
chmod +x clsdh
```

### 4. Verify
```bash
./clsdh -v
```

---

## 🚀 Method 2: Manual with Xcode

### 1. Install Xcode Command Line Tools
```bash
xcode-select --install
```

### 2. Clone and Compile
```bash
git clone https://github.com/iky-art/CLSDH.git
cd CLSDH
g++ -std=c++11 -O2 -pthread clsdh.cpp -o clsdh
chmod +x clsdh
```

---

## ▶️ Usage Examples

```bash
./clsdh link-check https://example.com
./clsdh tcp-port google.com 443
./clsdh cpu-monitor
```

---

> 🇬🇧 English documentation. Indonesian version available at `macos/install-id.md`.
