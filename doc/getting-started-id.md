# 🎯 Memulai dengan CLSDH (Bahasa Indonesia)

> Panduan cepat untuk pemula yang ingin menggunakan CLSDH secara efektif.

---

## 📖 Apa itu CLSDH?

**CLSDH** singkat dari **"Cek Link Sebelum Data Hilang"** (Indonesia) / **"Check Links Before Data Loss"** (Inggris). Alat CLI multi-tool yang memungkinkan Anda memeriksa link, memantau sistem, dan menjalankan diagnosa jaringan secara real-time — semua dalam satu binary C++.

---

## 🚀 Instalasi Pertama Kali

### 1. Clone Repository
```bash
git clone https://github.com/iky-art/CLSDH.git
cd CLSDH
```

### 2. Kompilasi
```bash
g++ -std=c++11 -O2 -pthread clsdh.cpp -o clsdh
```

### 3. Verifikasi
```bash
./clsdh -v
```
**Output yang diharapkan:**
```
CLSDH v2.0.0 - Cek Link Sebelum Data Hilang / Check Links Before Data Loss
```

---

## ▶️ Cara Dasar Menggunakan

CLSDH menggunakan pola perintah berikut:

```bash
./clsdh <nama_tool> [argumen...]
```

### Contoh Pengecekan Link
```bash
./clsdh link-check https://example.com http://example.org
```

### Contoh Pengecekan Port
```bash
./clsdh tcp-port google.com 443
```

### Lihat Semua Tersedia
```bash
./clsdh list
```

---

## 📋 Tools Paling Populer

| No | Tool | Fungsi | Contoh |
|----|------|--------|--------|
| 1 | `link-check` | Pengecekan link HTTP real-time | `./clsdh link-check https://site.com` |
| 2 | `tcp-port` | Pengecekan port TCP | `./clsdh tcp-port host.com 80` |
| 3 | `cpu-monitor` | Pantau CPU real-time | `./clsdh cpu-monitor` |
| 4 | `mem-monitor` | Pantau memori real-time | `./clsdh mem-monitor` |
| 5 | `http-headers` | Lihat header HTTP | `./clsdh http-headers https://site.com` |

---

## 💡 Tips Penggunaan

1. **Gunakan `--no-color`** untuk output tanpa warna (cocok untuk log):
   ```bash
   ./clsdh link-check https://site.com --no-color
   ```

2. **Simpan hasil ke file**:
   ```bash
   ./clsdh link-check https://site.com -o hasil.txt
   ```

3. **Hentikan monitor** (CPU, Mem, Disk, Net) dengan tekan **Ctrl+C**.

---

## ❓ Pertanyaan Umum

**Q: Kenapa link https:// kadang menunjukkan DOWN?**  
A: CLSDH menggunakan raw TCP socket tanpa OpenSSL. Untuk HTTPS, koneksi plain TCP ke port 443 biasanya tidak menerima respons HTTP valid.

**Q: Bagaimana cara update?**  
A: Unduh binary terbaru dari [Release GitHub](https://github.com/iky-art/CLSDH/releases) atau gunakan `./clsdh upd` (jika `UPDATE_URL` sudah dikonfigurasi).

---

## 📞 Dukungan

Butuh bantuan? Hubungi melalui **Instagram DM**: https://instagram.com/iky-art

---

> 🇮🇩 Dokumentasi dalam Bahasa Indonesia. Versi Inggris tersedia di `getting-started-en.md`.
