# 📋 Panduan Penggunaan CLSDH di Termux (Bahasa Indonesia)

> Panduan detail menjalankan setiap tool CLSDH di lingkungan Termux.

---

## 🔗 Pengecekan Link

```bash
./clsdh link-check https://example.com http://example.org
./clsdh link-check https://site.com --concurrency 20 --timeout 10
./clsdh link-check https://site.com -o ~/link-result.txt
```

## 🔌 Pengecekan Port

```bash
./clsdh tcp-port google.com 443
./clsdh tcp-port localhost 8080 5000
./clsdh udp-port 8.8.8.8 53
```

## 🖥️ Monitor Sistem

```bash
./clsdh cpu-monitor      # Tekan Ctrl+C untuk berhenti
./clsdh mem-monitor      # Tekan Ctrl+C untuk berhenti
./clsdh disk-monitor /   # Tekan Ctrl+C untuk berhenti
./clsdh net-stats        # Tekan Ctrl+C untuk berhenti
./clsdh load-avg         # Tekan Ctrl+C untuk berhenti
```

## 🌐 Jaringan & DNS

```bash
./clsdh ping google.com 4
./clsdh dns-lookup google.com
./clsdh reverse-dns 8.8.8.8
./clsdh http-headers https://example.com
./clsdh port-scan localhost 1 100
```

## 🔐 Keamanan & SSL

```bash
./clsdh ssl-cert google.com 443
./clsdh banner-grab localhost 22
./clsdh smtp-test mail.com 25
```

## 🔧 Utilitas

```bash
./clsdh md5 "clsdh"
./clsdh sha256 "clsdh"
./clsdh base64-enc "halo"
./clsdh base64-dec "aGFsbw=="
./clsdh uuid
./clsdh password-gen 16
./clsdh url-encode "clsdh v2"
./clsdh url-decode "clsdh%20v2"
```

## 💾 File & Sistem

```bash
./clsdh file-checksum ~/file.txt
./clsdh line-count ~/log.txt
./clsdh file-watch ~/config.ini
./clsdh uptime
./clsdh hostname
./clsdh ip-addr
./clsdh free-ram
./clsdh disk-usage
```

---

## 💡 Tips Khusus Termux

1. **Gunakan Termux:Widget** untuk menambahkan shortcut CLSDH ke layar utama Android.
2. **Simpan hasil ke `~/`** (home directory) agar mudah diakses dari file manager.
3. **Gunakan `termux-wake-lock`** jika ingin monitor berjalan dalam waktu lama tanpa tidur.

---

> 🇮🇩 Bahasa Indonesia. Versi Inggris tersedia di `termux/usage-en.md`.
