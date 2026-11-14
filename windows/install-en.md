# 🪟 Installing CLSDH on Windows (English)

> Guide to install CLSDH on Windows using WSL, MinGW, or Git Bash.

---

## 📋 Requirements

- Windows 10 or 11
- WSL2 (Windows Subsystem for Linux) recommended
- OR MinGW-w64 / Git Bash
- Internet connection

---

## 🚀 Method 1: WSL2 (Recommended)

### 1. Install WSL2
```powershell
wsl --install
```
Restart computer after installation.

### 2. Open Ubuntu from WSL
```bash
sudo apt update && sudo apt upgrade -y
sudo apt install g++ git make -y
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

## 🚀 Method 2: MinGW-w64

### 1. Install MinGW-w64
Download from https://winlibs.com/ and add to PATH.

### 2. Compile in Git Bash / CMD
```bash
g++ -std=c++11 -O2 -pthread clsdh.cpp -o clsdh.exe
clsdh.exe -v
```

---

## ▶️ Usage Examples

```bash
./clsdh link-check https://example.com
./clsdh tcp-port google.com 443
./clsdh cpu-monitor
```

---

> 🇬🇧 English documentation. Indonesian version available at `windows/install-id.md`.
