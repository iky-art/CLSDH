# CLSDH - Link Checker CLI (C++)

```
 CCCCC   L      SSSSS   DDDDD   HH   HH 
C         L      S      D   D   HH   HH 
C         L      SSS    D   D   HHHHHHH 
C         L           S  D   D   HH   HH 
 CCCCC   LLLLL   SSSSS   DDDDD   HH   HH 
```

**CLSDH v2.0.0**  
**Cek Link Sebelum Data Hilang** / **Check Links Before Data Loss**

CLI cek link **real-time** yang ditulis dalam **C++**. Tidak perlu library eksternal — hanya butuh `g++`. Setiap hasil pengecekan dicetak begitu selesai, tidak perlu menunggu semua link selesai dicek.

---

## 📌 Fitur

| Fitur | Keterangan |
|-------|------------|
| **Real-time output** | Hasil muncul segera setiap link selesai dicek (dengan timestamp) |
| **Concurrent** | Mengecek banyak link sekaligus (`-c` / concurrency) |
| **CLI lengkap** | Opsi pendek dan panjang (`-f`, `-c`, `-t`, `-o`, dll.) |
| **ASCII art banner** | Tampil saat program dijalankan |
| **Status UP/DOWN** | Warna hijau untuk UP, merah untuk DOWN |
| **Kode HTTP** | Menampilkan status kode (200, 404, 500, dst.) dan waktu respons (ms) |
| **Simpan ke file** | `-o` / `--output` menyimpan hasil ke file (tanpa warna ANSI) |
| **Auto-update** | `./checklink upd` untuk update otomatis ke versi terbaru |
| **Input dari stdin** | Bisa menerima pipe dari `cat` atau redirection |
| **Tanpa dependensi** | Hanya butuh compiler `g++`, tidak perlu libcurl/OpenSSL |

---

## 🛠️ Compile (Build)

```bash
cd /root/tools-check-pishink
g++ -std=c++11 -O2 -pthread checklink.cpp -o checklink
```

Jika ingin tanpa warna ANSI secara default, edit variabel `g_useColor` di kode atau gunakan opsi `--no-color`.

---

## 🚀 Cara Pemanggilan (Usage)

### 1. Cek langsung beberapa link
```bash
./checklink https://example.com http://example.org
```

### 2. Cek dari file (satu link per baris)
```bash
./checklink -f links.txt
```

### 3. Cek dari file dengan pengaturan
```bash
./checklink -f links.txt -c 20 -t 10
```
- `-c 20` = 20 link dicek bersamaan (concurrency)
- `-t 10` = timeout 10 detik per link

### 4. Simpan hasil ke file output
```bash
./checklink -f links.txt -o hasil.txt
```

### 5. Tanpa warna ANSI (cocok untuk log / cron)
```bash
./checklink -f links.txt --no-color -o hasil.log
```

### 6. Baca dari stdin / pipe
```bash
cat links.txt | ./checklink
# atau
./checklink < links.txt
```

### 7. Update otomatis ke versi terbaru
```bash
./checklink upd
```
> **Peringatan:** Sebelum menggunakan `upd`, ubah baris `UPDATE_URL` di `checklink.cpp` ke alamat file binary `checklink` terbaru kamu (contoh GitHub Releases), lalu recompile.

### 8. Bantuan dan versi
```bash
./checklink -h      # Tampilkan bantuan
./checklink -v      # Tampilkan versi
```

---

## 📋 Opsi CLI

| Opsi Pendek | Opsi Panjang | Keterangan |
|-------------|--------------|------------|
| `-f <file>` | `--file <file>` | Baca daftar link dari file (satu link per baris) |
| `-c <N>` | `--concurrency <N>` | Jumlah pengecekan bersamaan (default 30) |
| `-t <sec>` | `--timeout <sec>` | Timeout per link dalam detik (default 10) |
| `-o <file>` | `--output <file>` | Simpan hasil ke file (tanpa warna ANSI) |
| | `--no-color` | Matikan warna ANSI output |
| `upd` | `--update` | Update otomatis ke versi terbaru |
| `-h` | `--help` | Tampilkan bantuan |
| `-v` | `--version` | Tampilkan versi |

---

## 🖥️ Contoh Output

```
 CCCCC   L      SSSSS   DDDDD   HH   HH 
C         L      S      D   D   HH   HH 
C         L      SSS    D   D   HHHHHHH 
C         L           S  D   D   HH   HH 
 CCCCC   LLLLL   SSSSS   DDDDD   HH   HH 
   CLSDH - Cek Link Sebelum Data Hilang
   CLSDH - Check Links Before Data Loss
   CLI • C++ • Tanpa dependensi eksternal • Real-time output

URLs: 4  Concurrency: 4  Timeout: 8s
----------------------------------------------------------------------
[10:51:08] [UP]   http://example.org                                              HTTP 200 OK  (180 ms)
[10:51:08] [DOWN] https://example.com                                             HTTP 400 Bad Request  (190 ms)
[10:51:08] [DOWN] http://127.0.0.1:9                                              ERR connection failed
[10:51:08] [DOWN] https://tidakada-domain-xyz.com                                ERR DNS: Name or service not known
----------------------------------------------------------------------
Selesai. Total: 4 | UP: 1 | DOWN: 3
```

Setiap baris muncul **secara real-time** begitu pengecekan satu link selesai.

---

## 📁 Format File Output (`-o`)

File output disimpan **tanpa kode warna ANSI**, siap diproses lebih lanjut atau dilaporkan:

```
CLSDH v2.0.0 - Cek Link Sebelum Data Hilang / Check Links Before Data Loss
Waktu: 10:51:08
Total URL: 4
----------------------------------------------------------------------
[10:51:08] [UP]   http://example.org                                              HTTP 200 OK  (180 ms)
[10:51:08] [DOWN] https://example.com                                             HTTP 400 Bad Request  (190 ms)
----------------------------------------------------------------------
Selesai. Total: 4 | UP: 1 | DOWN: 3
```

---

## ⚠️ Catatan Penting

### HTTP vs HTTPS
Versi ini menggunakan **raw TCP socket (BSD socket)** tanpa OpenSSL, jadi:
- Link **`http://`**: dapat dicek dengan akurat (menerima respons HTTP mentah).
- Link **`https://`**: koneksi plain TCP ke port 443 biasanya tidak mendapat respons HTTP yang valid karena butuh TLS/SSL, jadi akan tampil sebagai `DOWN`/timeout.

Jika ingin cek `https://` secara akurat, perlu ditulis ulang menggunakan **libcurl** (`-lcurl`) dengan dukungan TLS.

### Auto-update (`./checklink upd`)
1. Upload binary `checklink` hasil compile ke server/GitHub Releases kamu.
2. Ubah baris ini di `checklink.cpp`:
   ```cpp
   static const char* UPDATE_URL = "https://contoh.com/checklink";
   ```
   Ganti dengan URL file binary terbaru kamu, misalnya:
   ```cpp
   static const char* UPDATE_URL = "https://github.com/user/repo/releases/download/v2.0.0/checklink";
   ```
3. Recompile:
   ```bash
   g++ -std=c++11 -O2 -pthread checklink.cpp -o checklink
   ```
4. Jalankan `./checklink upd`.

> Binary yang diunduh harus sudah dikompilasi untuk arsitektur yang sama (aarch64/ARM64 di VPS kamu).

---

## 📂 Struktur File

| File | Keterangan |
|------|------------|
| `checklink.cpp` | Sumber kode C++ (CLI lengkap + ASCII art + auto-update) |
| `checklink` | Hasil kompilasi (binary siap jalankan) |
| `links.txt` | Contoh daftar link |
| `hasil.txt` | Contoh hasil output file |
| `README.md` | Panduan ini |

---

## 📄 Lisensi

Dibuat untuk keperluan internal. Bebas dimodifikasi dan digunakan.

---

**CLSDH v2.0.0** — Cek Link Sebelum Data Hilang / Check Links Before Data Loss
