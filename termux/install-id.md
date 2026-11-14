# 📱 Instalasi CLSDH di Termux (Bahasa Indonesia)

> Panduan lengkap menginstal dan menjalankan CLSDH di aplikasi Termux untuk Android.

---

## 📋 Persyaratan

- Aplikasi **Termux** terinstal (dari F-Droid atau GitHub, bukan Play Store yang sudah lama)
- Koneksi internet untuk mengunduh paket dan mengkompilasi
- Akses penyimpanan (opsional, untuk menyimpan hasil output)

---

## 🚀 Langkah Instalasi

### 1. Update Paket Termux
```bash
pkg update && pkg upgrade -y
```

### 2. Instal Compiler dan Git
```bash
pkg install git clang make -y
```

### 3. Clone Repository
```bash
git clone https://github.com/iky-art/CLSDH.git
cd CLSDH
```

### 4. Kompilasi CLSDH
```bash
g++ -std=c++11 -O2 -pthread clsdh.cpp -o clsdh
```

### 5. Beri Izin Eksekusi
```bash
chmod +x clsdh
```

### 6. Verifikasi
```bash
./clsdh -v
```

---

## 📦 Paket yang Diperlukan

| Paket | Fungsi | Perintah |
|-------|--------|----------|
| `git` | Clone repository | `pkg install git` |
| `clang` | Compiler C/C++ | `pkg install clang` |
| `make` | Build tools | `pkg install make` |

---

## ▶️ Contoh Penggunaan di Termux

```bash
./clsdh link-check https://example.com
./clsdh tcp-port google.com 443
./clsdh cpu-monitor
./clsdh mem-monitor
```

---

## 💾 Menyimpan Hasil di Termux

```bash
./clsdh link-check https://example.com -o ~/hasil-clsdh.txt
cat ~/hasil-clsdh.txt
```

---

## ⚠️ Catatan Penting

- **HTTPS**: Karena CLSDH tidak menggunakan OpenSSL, link `https://` mungkin menunjukkan timeout. Gunakan `http://` atau cek port TCP.
- **Port di bawah 1024**: Di Termux, biasanya tidak memerlukan root untuk port rendah, tetapi tergantung konfigurasi sistem.
- **Baterai**: Monitor real-time (cpu, mem, disk, net) dapat meningkatkan konsumsi baterai.

---

## 🔄 Update di Termux

```bash
cd CLSDH
git pull
g++ -std=c++11 -O2 -pthread clsdh.cpp -o clsdh
```

---

> 🇮🇩 Bahasa Indonesia. Versi Inggris tersedia di `termux/install-en.md`.
