# 📚 Referensi API CLSDH (Bahasa Indonesia)

> Referensi lengkap semua command line tool dan argumen yang didukung CLSDH.

---

## 📋 Format Umum

```bash
./clsdh <tool> [argumen...]
```

---

## 🌐 Jaringan (Network Tools)

| Tool | Argumen | Deskripsi | Contoh |
|------|---------|-----------|--------|
| `link-check` | `<url>... [--concurrency N] [--timeout T]` | Pengecekan link HTTP real-time | `./clsdh link-check https://a.com --concurrency 10` |
| `tcp-port` | `<host> <port> [timeoutMs]` | Cek port TCP terbuka | `./clsdh tcp-port google.com 443` |
| `udp-port` | `<host> <port> [timeoutMs]` | Cek port UDP reachable | `./clsdh udp-port 8.8.8.8 53` |
| `ping` | `<host> [count]` | Ping host | `./clsdh ping google.com 4` |
| `dns-lookup` | `<domain>` | Resolusi DNS ke IP | `./clsdh dns-lookup google.com` |
| `reverse-dns` | `<ip>` | Reverse DNS (PTR record) | `./clsdh reverse-dns 8.8.8.8` |
| `http-headers` | `<url>` | Lihat header HTTP (HEAD) | `./clsdh http-headers https://site.com` |
| `port-scan` | `<host> [start] [end]` | Scan port 1-1000 | `./clsdh port-scan host.com 1 100` |
| `ntp-time` | `[host]` | Sinkronisasi waktu NTP | `./clsdh ntp-time pool.ntp.org` |
| `smtp-test` | `<host> [port]` | Cek banner SMTP | `./clsdh smtp-test mail.com 25` |
| `http-post` | `<url> [data]` | Kirim request HTTP POST | `./clsdh http-post https://api.com "data=1"` |
| `http-get` | `<url>` | Request HTTP GET | `./clsdh http-get https://api.com` |
| `whois` | `<domain>` | Lookup WHOIS domain | `./clsdh whois example.com` |
| `ssl-cert` | `<host> [port>` | Info sertifikat SSL/TLS | `./clsdh ssl-cert google.com 443` |
| `banner-grab` | `<host> <port>` | Ambil banner service | `./clsdh banner-grab host.com 22` |

---

## 🖥️ Sistem (System Tools)

| Tool | Argumen | Deskripsi | Contoh |
|------|---------|-----------|--------|
| `cpu-monitor` | - | Monitor CPU real-time | `./clsdh cpu-monitor` |
| `mem-monitor` | - | Monitor memori real-time | `./clsdh mem-monitor` |
| `disk-monitor` | `[path]` | Monitor disk real-time | `./clsdh disk-monitor /` |
| `uptime` | - | Waktu hidup sistem | `./clsdh uptime` |
| `load-avg` | - | Beban sistem real-time | `./clsdh load-avg` |
| `proc-list` | `[limit]` | Daftar proses teratas | `./clsdh proc-list 20` |
| `proc-watch` | `[nama]` | Pantau proses | `./clsdh proc-watch nginx` |
| `net-stats` | - | Statistik jaringan real-time | `./clsdh net-stats` |
| `hostname` | - | Nama host | `./clsdh hostname` |
| `kernel` | - | Info kernel | `./clsdh kernel` |
| `os-info` | - | Info sistem operasi | `./clsdh os-info` |
| `ip-addr` | - | Alamat IP | `./clsdh ip-addr` |
| `route` | - | Tabel routing | `./clsdh route` |
| `proc-tree` | - | Pohon proses | `./clsdh proc-tree` |
| `disk-usage` | - | Penggunaan disk | `./clsdh disk-usage` |
| `users-list` | - | Daftar pengguna sistem | `./clsdh users-list` |
| `free-ram` | - | Memori beas/digunakan | `./clsdh free-ram` |
| `top-cmd` | `[n]` | Top proses CPU | `./clsdh top-cmd 10` |

---

## 📁 File & Utilitas

| Tool | Argumen | Deskripsi | Contoh |
|------|---------|-----------|--------|
| `file-checksum` | `<file>` | SHA256 checksum | `./clsdh file-checksum file.txt` |
| `file-watch` | `<file>` | Pantau perubahan file | `./clsdh file-watch config.ini` |
| `line-count` | `<file>` | Hitung baris file | `./clsdh line-count log.txt` |
| `date-time` | - | Waktu saat ini | `./clsdh date-time` |
| `calendar` | - | Kalender | `./clsdh calendar` |
| `unix-timestamp` | - | Timestamp Unix | `./clsdh unix-timestamp` |
| `base64-enc` | `<text>` | Encode Base64 | `./clsdh base64-enc halo` |
| `base64-dec` | `<text>` | Decode Base64 | `./clsdh base64-dec aGFsbw==` |
| `md5` | `<text>` | Hash MD5 | `./clsdh md5 "clsdh"` |
| `sha1` | `<text>` | Hash SHA1 | `./clsdh sha1 "clsdh"` |
| `sha256` | `<text>` | Hash SHA256 | `./clsdh sha256 "clsdh"` |
| `uuid` | - | Generate UUID | `./clsdh uuid` |
| `password-gen` | `[panjang]` | Generate password | `./clsdh password-gen 16` |
| `url-encode` | `<text>` | Encode URL | `./clsdh url-encode "clsdh v2"` |
| `url-decode` | `<text>` | Decode URL | `./clsdh url-decode clsdh%20v2` |
| `crontab-list` | - | Lihat cron jobs | `./clsdh crontab-list` |

---

## 🔧 Opsi Global

| Opsi | Deskripsi |
|------|-----------|
| `-v, --version` | Tampilkan versi |
| `-h, --help` | Tampilkan bantuan |
| `list` | Daftar semua tools |
| `upd, --update` | Auto-update ke versi terbaru |
| `--no-color` | Matikan warna ANSI |

---

> 🇮🇩 Bahasa Indonesia. Versi Inggris tersedia di `api-reference-en.md`.
