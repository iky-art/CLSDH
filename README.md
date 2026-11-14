# 🚀 CLSDH — Multi-Tool CLI Suite

[![Version](https://img.shields.io/badge/version-2.0.0-blue.svg)](https://github.com/iky-art/CLSDH/releases/tag/v2.0.0)
[![License: MIT](https://img.shields.io/badge/license-MIT-green.svg)](LICENSE)
[![Language: C++](https://img.shields.io/badge/language-C%2B%2B-brightgreen.svg)](clsdh.cpp)
[![Platform: Linux | macOS | Windows | Termux](https://img.shields.io/badge/platform-linux%20%7C%20macOS%20%7C%20windows%20%7C%20termux-orange.svg)](.)

```
 ________  ___       ________  ________  ___  ___     
|\   ____\|\  \     |\   ____\|\   ___ \|\  \|\  \   
\ \  \___|\\ \  \    \ \  \___|\\ \  \_|\\ \  \\\\  \ 
 \ \  \    \ \  \    \ \  \    \ \  \ \ \ \ \  \\\\  \
  \ \  \____\ \  \____\ \ \  \ \ \ \__\_\ \ \_______\
   \ \_______\\ \_______\ \ \__\ \ \__\ \__\ \|_______|
    \|_______|\|_______|\|__|\|__|\|__|    \|_______|
```

> **CLSDH** = **Cek Link Sebelum Data Hilang** / **Check Links Before Data Loss**

CLI multi-tool **real-time** yang ditulis dalam **C++**. Tidak perlu library eksternal — hanya butuh compiler `g++`. Terdiri dari **49 tools** dalam satu binary untuk pemantauan jaringan, sistem, file, dan utilitas enkoding.

---

## 📋 Daftar Isi

- [🎯 Fitur Utama](#-fitur-utama)
- [🛠️ Instalasi](#️-instalasi)
- [▶️ Cara Pakai](#️-cara-pakai)
- [📁 Struktur Dokumen](#-struktur-dokumen)
- [🌐 Dukungan Platform](#-dukungan-platform)
- [📄 Lisensi](#-lisensi)
- [🔒 Keamanan](#-keamanan)

---

## 🎯 Fitur Utama

| Fitur | Keterangan |
|-------|------------|
| **49 Tools** | Satu binary, semua fungsi real-time |
| **Real-time Output** | Hasil muncul segera dengan timestamp |
| **ASCII Art Banner** | Tampil saat startup dengan warna magenta `#ff00ff` |
| **Tanpa Dependensi** | Tidak perlu libcurl / OpenSSL |
| **Multi-Platform** | Linux, macOS, Windows, Termux |
| **CLI Lengkap** | Opsi pendek dan panjang |

---

## 🛠️ Instalasi

### Dari Source
```bash
git clone https://github.com/iky-art/CLSDH.git
cd CLSDH
g++ -std=c++11 -O2 -pthread clsdh.cpp -o clsdh
```

### Dari Release
```bash
wget https://github.com/iky-art/CLSDH/releases/download/v2.0.0/clsdh
chmod +x clsdh
```

---

## ▶️ Cara Pakai

```bash
./clsdh -v                          # Lihat versi
./clsdh list                        # Daftar semua tools
./clsdh link-check https://example.com
./clsdh tcp-port example.com 80
./clsdh cpu-monitor
```

---

## 📁 Struktur Dokumen

```
CLSDH/
├── doc/                    # Dokumentasi umum (ID & EN)
├── termux/                 # Panduan Termux (ID & EN)
├── macos/                  # Panduan macOS (ID & EN)
├── windows/                # Panduan Windows (ID & EN)
├── linux/                  # Panduan Linux (ID & EN)
├── LICENSE
├── SECURITY.md
├── DISCLAIMER.md
└── README.md
```

---

## 🌐 Dukungan Platform

| Platform | Status | Folder |
|----------|--------|--------|
| Linux | ✅ Supported | `linux/` |
| macOS | ✅ Supported | `macos/` |
| Windows | ✅ Supported | `windows/` |
| Termux | ✅ Supported | `termux/` |

---

## 📄 Lisensi

Diberlisikan di bawah [MIT License](LICENSE).

---

## 🔒 Keamanan

Lihat [SECURITY.md](SECURITY.md) untuk kebijakan dan kontak laporan kerentanan.

---

> Dibuat dengan ❤️ oleh [iky-art](https://instagram.com/iky-art)  
> **CLSDH v2.0.0** — Cek Link Sebelum Data Hilang / Check Links Before Data Loss
