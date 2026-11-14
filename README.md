# CLSDH - Multi-Tool CLI Suite (C++)

```
 ________  ___       ________  ________  ___  ___     
|\   ____\|\  \     |\   ____\|\   ___ \|\  \|\  \   
\ \  \___|\\ \  \    \ \  \___|\\ \  \_|\\ \  \\\\  \ 
 \ \  \    \ \  \    \ \  \    \ \  \ \ \ \ \  \\\\  \
  \ \  \____\ \  \____\ \ \  \ \ \ \__\_\ \ \_______\
   \ \_______\\ \_______\ \ \__\ \ \__\ \__\ \|_______|
    \|_______|\|_______|\|__|\|__|\|__|    \|_______|
```

**CLSDH v2.0.0**  
**Cek Link Sebelum Data Hilang** / **Check Links Before Data Loss**

CLI multi-tool **real-time** yang ditulis dalam **C++**. Tidak perlu library eksternal — hanya butuh `g++`. Terdiri dari **49 tools** dalam satu binary.

---

## 📌 Fitur Utama

| Fitur | Keterangan |
|-------|------------|
| **49 tools dalam 1 binary** | Jaringan, sistem, file, enkoding, utilitas |
| **Real-time output** | Hasil muncul segera setiap proses selesai (dengan timestamp) |
| **ASCII art banner** | Tampil saat program dijalankan (warna magenta `#ff00ff`) |
| **CLI lengkap** | Opsi pendek dan panjang |
| **Warna terminal** | ANSI truecolor support |
| **Tanpa dependensi** | Hanya butuh compiler `g++`, tidak perlu libcurl/OpenSSL |

---

## 🛠️ Compile (Build)

```bash
cd /root/tools-check-pishink
g++ -std=c++11 -O2 -pthread clsdh.cpp -o clsdh
```

---

## 🚀 Cara Pemanggilan (Usage)

```bash
./clsdh <tool> [args...]
```

### Contoh:
```bash
./clsdh -v                          # Lihat versi
./clsdh list                        # Daftar semua tools
./clsdh link-check https://example.com
./clsdh tcp-port example.com 80
./clsdh cpu-monitor
./clsdh mem-monitor
./clsdh http-get https://example.com
./clsdh md5 "halo dunia"
./clsdh base64-enc "clsdh"
```

---

## 📋 Daftar Semua Tools (49)

| No | Tool | Keterangan |
|----|------|------------|
| 1 | `link-check` | Real-time HTTP link checker |
| 2 | `tcp-port` | TCP port check |
| 3 | `udp-port` | UDP port check |
| 4 | `ping` | Ping host |
| 5 | `dns-lookup` | DNS resolution |
| 6 | `reverse-dns` | Reverse DNS (PTR) |
| 7 | `http-headers` | HTTP headers (HEAD) |
| 8 | `port-scan` | Port scanner |
| 9 | `ntp-time` | NTP time sync |
| 10 | `smtp-test` | SMTP banner check |
| 11 | `http-post` | HTTP POST request |
| 12 | `cpu-monitor` | Real-time CPU monitor |
| 13 | `mem-monitor` | Real-time memory monitor |
| 14 | `disk-monitor` | Real-time disk monitor |
| 15 | `uptime` | System uptime |
| 16 | `load-avg` | Real-time load average |
| 17 | `proc-list` | Top processes |
| 18 | `proc-watch` | Watch process (real-time) |
| 19 | `net-stats` | Real-time network I/O |
| 20 | `hostname` | Hostname |
| 21 | `kernel` | Kernel info |
| 22 | `os-info` | OS info |
| 23 | `ip-addr` | IP addresses |
| 24 | `route` | Routing table |
| 25 | `file-checksum` | SHA256 checksum |
| 26 | `file-watch` | Watch file changes |
| 27 | `line-count` | Count lines in file |
| 28 | `date-time` | Current date/time |
| 29 | `calendar` | Calendar |
| 30 | `base64-enc` | Base64 encode |
| 31 | `base64-dec` | Base64 decode |
| 32 | `md5` | MD5 hash |
| 33 | `sha1` | SHA1 hash |
| 34 | `sha256` | SHA256 hash |
| 35 | `uuid` | Generate UUID |
| 36 | `password-gen` | Generate password |
| 37 | `http-get` | HTTP GET request |
| 38 | `whois` | WHOIS lookup |
| 39 | `ssl-cert` | SSL certificate info |
| 40 | `banner-grab` | Service banner grab |
| 41 | `proc-tree` | Process tree |
| 42 | `disk-usage` | Disk usage (df -h) |
| 43 | `users-list` | List system users |
| 44 | `unix-timestamp` | Unix timestamp |
| 45 | `url-encode` | URL encode |
| 46 | `url-decode` | URL decode |
| 47 | `crontab-list` | List cron jobs |
| 48 | `top-cmd` | Top CPU processes |
| 49 | `free-ram` | Memory free/used |

---

## 🖥️ Contoh Output

```
 ________  ___       ________  ________  ___  ___     
|\   ____\|\  \     |\   ____\|\   ___ \|\  \|\  \   
...
   CLSDH v2.0.0
   CLSDH - Cek Link Sebelum Data Hilang
   CLSDH - Check Links Before Data Loss
   CLI • C++ • Real-time • Tanpa dependensi eksternal

URLs: 2  Concurrency: 30  Timeout: 10s
----------------------------------------------------------------------
[10:51:08] [UP]   http://example.org                                              HTTP 200 OK  (180 ms)
[10:51:08] [DOWN] https://example.com                                             HTTP 400 Bad Request  (190 ms)
----------------------------------------------------------------------
Selesai. Total: 2 | UP: 1 | DOWN: 1
```

---

## 📁 Struktur File

| File | Keterangan |
|------|------------|
| `clsdh.cpp` | Sumber kode C++ (49 tools) |
| `clsdh` | Hasil kompilasi (binary siap jalankan) |
| `README.md` | Panduan ini |
| `.gitignore` | Git ignore file |

---

## 📄 Lisensi

Dibuat untuk keperluan internal. Bebas dimodifikasi dan digunakan.

---

**CLSDH v2.0.0** — Cek Link Sebelum Data Hilang / Check Links Before Data Loss
