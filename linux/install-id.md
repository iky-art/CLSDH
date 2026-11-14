# 🐧 Instalasi CLSDH di Linux (Bahasa Indonesia)

> Panduan menginstal CLSDH di distribusi Linux (Ubuntu, Debian, CentOS, Arch, dll).

---

## 📋 Persyaratan

- Distribusi Linux apa pun
- Akses root / sudo
- Koneksi internet

---

## 🚀 Ubuntu / Debian

### 1. Update Paket
```bash
sudo apt update && sudo apt upgrade -y
```

### 2. Instal Compiler dan Git
```bash
sudo apt install g++ git make -y
```

### 3. Clone dan Kompilasi
```bash
git clone https://github.com/iky-art/CLSDH.git
cd CLSDH
g++ -std=c++11 -O2 -pthread clsdh.cpp -o clsdh
chmod +x clsdh
```

### 4. Verifikasi
```bash
./clsdh -v
```

---

## 🚀 CentOS / RHEL / Fedora

### 1. Instal Compiler dan Git
```bash
sudo dnf install gcc-c++ git make -y
```
ATAU
```bash
sudo yum install gcc-c++ git make -y
```

### 2. Clone dan Kompilasi
```bash
git clone https://github.com/iky-art/CLSDH.git
cd CLSDH
g++ -std=c++11 -O2 -pthread clsdh.cpp -o clsdh
chmod +x clsdh
```

---

## 🚀 Arch Linux

### 1. Instal Compiler dan Git
```bash
sudo pacman -S gcc git make --noconfirm
```

### 2. Clone dan Kompilasi
```bash
git clone https://github.com/iky-art/CLSDH.git
cd CLSDH
g++ -std=c++11 -O2 -pthread clsdh.cpp -o clsdh
chmod +x clsdh
```

---

## ▶️ Contoh Penggunaan

```bash
./clsdh link-check https://example.com
./clsdh tcp-port google.com 443
./clsdh cpu-monitor
```

---

> 🇮🇩 Bahasa Indonesia. Versi Inggris tersedia di `linux/install-en.md`.
