# 🖥️ Panduan Tools Sistem CLSDH (Bahasa Indonesia)

> Penjelasan detail tentang semua tools pemantauan sistem di CLSDH.

---

## 📊 Monitor Real-time

### CPU Monitor
```bash
./clsdh cpu-monitor
```
Menampilkan persentase penggunaan CPU setiap detik. Tekan **Ctrl+C** untuk berhenti.

### Memory Monitor
```bash
./clsdh mem-monitor
```
Menampilkan persentase penggunaan RAM, memori tersedia, dan total memori dalam MB.

### Disk Monitor
```bash
./clsdh disk-monitor /
```
Menampilkan persentase penggunaan disk, ruang yang digunakan, dan total dalam MB.

### Network Stats
```bash
./clsdh net-stats
```
Menampilkan kecepatan transfer jaringan (KB/s) secara real-time.

### Load Average
```bash
./clsdh load-avg
```
Menampilkan beban sistem 1, 5, dan 15 menit setiap detik.

---

## 📁 Informasi Sistem

| Tool | Fungsi | Contoh |
|------|--------|--------|
| `hostname` | Nama host | `./clsdh hostname` |
| `kernel` | Versi kernel | `./clsdh kernel` |
| `os-info` | Info OS | `./clsdh os-info` |
| `ip-addr` | Alamat IP | `./clsdh ip-addr` |
| `route` | Tabel routing | `./clsdh route` |
| `uptime` | Uptime sistem | `./clsdh uptime` |
| `free-ram` | RAM bebas/digunakan | `./clsdh free-ram` |
| `disk-usage` | Penggunaan disk | `./clsdh disk-usage` |

---

## 🔧 Manajemen Proses

| Tool | Fungsi | Contoh |
|------|--------|--------|
| `proc-list` | Proses teratas | `./clsdh proc-list 20` |
| `proc-watch` | Pantau proses | `./clsdh proc-watch nginx` |
| `proc-tree` | Pohon proses | `./clsdh proc-tree` |
| `top-cmd` | Top CPU | `./clsdh top-cmd 10` |
| `users-list` | Pengguna sistem | `./clsdh users-list` |
| `crontab-list` | Cron jobs | `./clsdh crontab-list` |

---

## ⏹️ Menghentikan Monitor

Semua tool monitor (cpu-monitor, mem-monitor, disk-monitor, net-stats, load-avg) dapat dihentikan dengan menekan **Ctrl+C**.

---

> 🇮🇩 Bahasa Indonesia. Versi Inggris tersedia di `system-tools-en.md`.
