# 🚀 Panduan Lanjut CLSDH di Termux (Bahasa Indonesia)

> Tips dan trik lanjut untuk pengguna Termux.

---

## ⚡ Optimasi Performansi

### Jalankan dengan prioritas tinggi
```bash
nice -n -10 ./clsdh cpu-monitor
```

### Jalankan di background
```bash
nohup ./clsdh net-stats > ~/net.log 2>&1 &
```

### Batasi concurrency untuk link-check
```bash
./clsdh link-check https://site.com --concurrency 5 --timeout 15
```

---

## 🔐 Akses Penyimpanan

Izinkan Termux mengakses penyimpanan internal:
```bash
termux-setup-storage
```

Lalu simpan hasil ke:
```bash
./clsdh link-check https://site.com -o ~/storage/downloads/hasil.txt
```

---

## 🔄 Otomatisasi dengan Cron

Termux mendukung cron melalui `crond`:
```bash
pkg install cronie
crond
crontab -e
```

Tambahkan jadwal:
```
*/5 * * * * /data/data/com.termux/files/home/CLSDH/clsdh link-check https://site.com >> ~/monitor.log
```

---

## 📱 Termux:Widget

Buat shortcut di layar utama Android:
1. Buka Termux:Widget
2. Pilih skrip CLSDH favorit
3. Tambahkan widget ke layar utama

---

> 🇮🇩 Bahasa Indonesia. Versi Inggris tersedia di `termux/advanced-en.md`.
