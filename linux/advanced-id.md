# 🚀 Panduan Lanjut CLSDH di Linux (Bahasa Indonesia)

> Tips lanjut untuk pengguna Linux.

---

## ⚡ Jalankan di Background
```bash
nohup ./clsdh net-stats > ~/net.log 2>&1 &
```

## 🔐 Akses Port Rendah
```bash
sudo ./clsdh port-scan localhost 1 100
```

## 🔄 Buat Alias (Opsional)
Tambahkan ke `~/.bashrc`:
```bash
alias clsdh="$HOME/CLSDH/clsdh"
```

---

> 🇮🇩 Bahasa Indonesia. Versi Inggris tersedia di `linux/advanced-en.md`.
