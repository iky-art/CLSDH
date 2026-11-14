# 📱 Installing CLSDH on Termux (English)

> Complete guide to install and run CLSDH in Termux for Android.

---

## 📋 Requirements

- **Termux** app installed (from F-Droid or GitHub, not the outdated Play Store version)
- Internet connection to download packages and compile
- Storage access (optional, for saving output files)

---

## 🚀 Installation Steps

### 1. Update Termux Packages
```bash
pkg update && pkg upgrade -y
```

### 2. Install Compiler and Git
```bash
pkg install git clang make -y
```

### 3. Clone Repository
```bash
git clone https://github.com/iky-art/CLSDH.git
cd CLSDH
```

### 4. Compile CLSDH
```bash
g++ -std=c++11 -O2 -pthread clsdh.cpp -o clsdh
```

### 5. Give Execute Permission
```bash
chmod +x clsdh
```

### 6. Verify
```bash
./clsdh -v
```

---

## 📦 Required Packages

| Package | Function | Command |
|---------|----------|---------|
| `git` | Clone repository | `pkg install git` |
| `clang` | C/C++ compiler | `pkg install clang` |
| `make` | Build tools | `pkg install make` |

---

## ▶️ Usage Examples in Termux

```bash
./clsdh link-check https://example.com
./clsdh tcp-port google.com 443
./clsdh cpu-monitor
./clsdh mem-monitor
```

---

## 💾 Saving Output in Termux

```bash
./clsdh link-check https://example.com -o ~/hasil-clsdh.txt
cat ~/hasil-clsdh.txt
```

---

## ⚠️ Important Notes

- **HTTPS**: Since CLSDH doesn't use OpenSSL, `https://` links may show timeout. Use `http://` or check TCP ports.
- **Ports below 1024**: In Termux, usually doesn't require root for low ports, but depends on system configuration.
- **Battery**: Real-time monitors (cpu, mem, disk, net) may increase battery consumption.

---

## 🔄 Update in Termux

```bash
cd CLSDH
git pull
g++ -std=c++11 -O2 -pthread clsdh.cpp -o clsdh
```

---

> 🇬🇧 English documentation. Indonesian version available at `termux/install-id.md`.
