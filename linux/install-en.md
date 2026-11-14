# 🐧 Installing CLSDH on Linux (English)

> Guide to install CLSDH on Linux distributions (Ubuntu, Debian, CentOS, Arch, etc.).

---

## 📋 Requirements

- Any Linux distribution
- Root / sudo access
- Internet connection

---

## 🚀 Ubuntu / Debian

### 1. Update Packages
```bash
sudo apt update && sudo apt upgrade -y
```

### 2. Install Compiler and Git
```bash
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

## 🚀 CentOS / RHEL / Fedora

### 1. Install Compiler and Git
```bash
sudo dnf install gcc-c++ git make -y
```
OR
```bash
sudo yum install gcc-c++ git make -y
```

### 2. Clone and Compile
```bash
git clone https://github.com/iky-art/CLSDH.git
cd CLSDH
g++ -std=c++11 -O2 -pthread clsdh.cpp -o clsdh
chmod +x clsdh
```

---

## 🚀 Arch Linux

### 1. Install Compiler and Git
```bash
sudo pacman -S gcc git make --noconfirm
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

> 🇬🇧 English documentation. Indonesian version available at `linux/install-id.md`.
