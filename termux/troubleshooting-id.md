# 🔧 Troubleshooting CLSDH di Termux (Bahasa Indonesia)

> Panduan menangani masalah CLSDH khusus Termux.

---

## ❗ Masalah Umum

### "pkg: command not found"
Pastikan kamu menggunakan Termux asli (dari F-Droid), bukan versi Play Store yang sudah tidak didukung.

### "g++: command not found"
Instal compiler terlebih dahulu:
```bash
pkg install clang make -y
```

### "Permission denied" saat menjalankan ./clsdh
Berikan izin eksekusi:
```bash
chmod +x clsdh
```

### Link https:// timeout
CLSDH tidak menggunakan OpenSSL. Gunakan http:// atau cek port TCP:
```bash
./clsdh tcp-port example.com 443
```

### Monitor berhenti sendiri
Pastikan tidak ada pengaturan penghemat baterai yang membatasi Termux. Gunakan:
```bash
termux-wake-lock
```

---

## 📞 Dukungan

Instagram DM: https://instagram.com/iky-art

---

> 🇮🇩 Bahasa Indonesia. Versi Inggris tersedia di `termux/troubleshooting-en.md`.
