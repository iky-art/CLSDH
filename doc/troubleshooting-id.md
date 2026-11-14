# 🔧 Troubleshooting CLSDH (Bahasa Indonesia)

> Panduan menangani masalah umum saat menggunakan CLSDH.

---

## ❓ Masalah Umum

### 1. "command not found: clsdh"
**Penyebab:** Binary belum dikompilasi atau tidak ada di PATH.

**Solusi:**
```bash
# Kompilasi terlebih dahulu
g++ -std=c++11 -O2 -pthread clsdh.cpp -o clsdh

# Jalankan dengan path lengkap
./clsdh -v
```

---

### 2. Link https:// muncul DOWN/timeout
**Penyebab:** CLSDH menggunakan raw TCP socket tanpa OpenSSL/TLS.

**Solusi:** Gunakan untuk `http://` atau cek port TCP/UDP saja. Untuk HTTPS akurat, perlu dukungan libcurl.

```bash
# Ini akan DOWN (tanpa TLS)
./clsdh link-check https://google.com

# Ini akan UP (plain HTTP)
./clsdh link-check http://example.com
```

---

### 3. DNS: Name or service not known
**Penyebab:** Domain tidak dapat diresolusi atau tidak ada koneksi internet.

**Solusi:**
```bash
# Periksa koneksi internet
./clsdh ping google.com

# Periksa DNS
./clsdh dns-lookup google.com
```

---

### 4. Permission denied saat port scan
**Penyebab:** Port di bawah 1024 memerlukan akses root.

**Solusi:**
```bash
sudo ./clsdh port-scan localhost 1 100
```

---

### 5. Output terlalu cepat / tidak terbaca
**Penyebab:** Real-time output muncul sangat cepat.

**Solusi:** Simpan ke file untuk dibaca kemudian:
```bash
./clsdh link-check https://site.com -o hasil.txt
cat hasil.txt
```

---

## 🛠️ Perintah Diagnosa

Jika mengalami masalah, jalankan perintah berikut untuk diagnostik:

```bash
./clsdh -v
./clsdh hostname
./clsdh ip-addr
./clsdh ping google.com
./clsdh dns-lookup google.com
```

---

## 📞 Dukungan

Masih mengalami masalah? Hubungi melalui **Instagram DM**: https://instagram.com/iky-art

---

> 🇮🇩 Bahasa Indonesia. Versi Inggris tersedia di `troubleshooting-en.md`.
