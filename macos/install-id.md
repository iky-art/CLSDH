# 🍎 Instalasi CLSDH di macOS (Bahasa Indonesia)

> Panduan menginstal CLSDH di macOS menggunakan Homebrew atau compile manual.

---

## 📋 Persyaratan

- macOS 10.15 atau lebih baru
- Xcode Command Line Tools atau Homebrew
- Koneksi internet

---

## 🚀 Metode 1: Homebrew (Rekomendasi)

### 1. Instal Homebrew (jika belum ada)
```bash
/bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
```

### 2. Instal Compiler
```bash
brew install gcc
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

## 🚀 Metode 2: Manual dengan Xcode

### 1. Instal Xcode Command Line Tools
```bash
xcode-select --install
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

> 🇮🇩 Bahasa Indonesia. Versi Inggris tersedia di `macos/install-en.md`.
