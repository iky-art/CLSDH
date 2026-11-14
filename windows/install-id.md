# 🪟 Instalasi CLSDH di Windows (Bahasa Indonesia)

> Panduan menginstal CLSDH di Windows menggunakan WSL, MinGW, atau Git Bash.

---

## 📋 Persyaratan

- Windows 10 atau 11
- WSL2 (Windows Subsystem for Linux) disarankan
- ATAU MinGW-w64 / Git Bash
- Koneksi internet

---

## 🚀 Metode 1: WSL2 (Rekomendasi)

### 1. Instal WSL2
```powershell
wsl --install
```
Restart komputer setelah instalasi.

### 2. Buka Ubuntu dari WSL
```bash
sudo apt update && sudo apt upgrade -y
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

## 🚀 Metode 2: MinGW-w64

### 1. Instal MinGW-w64
Unduh dari https://winlibs.com/ dan tambahkan ke PATH.

### 2. Kompilasi di Git Bash / CMD
```bash
g++ -std=c++11 -O2 -pthread clsdh.cpp -o clsdh.exe
clsdh.exe -v
```

---

## ▶️ Contoh Penggunaan

```bash
./clsdh link-check https://example.com
./clsdh tcp-port google.com 443
./clsdh cpu-monitor
```

---

> 🇮🇩 Bahasa Indonesia. Versi Inggris tersedia di `windows/install-en.md`.
