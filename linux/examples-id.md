# 📝 Contoh Penggunaan CLSDH di Linux (Bahasa Indonesia)

> Contoh skrip nyata untuk Linux.

---

## 📊 Monitor Jaringan
```bash
nohup ./clsdh net-stats > ~/network.log 2>&1 &
```

## 🔍 Pengecekan SSL
```bash
./clsdh ssl-cert google.com 443
```

## 💾 Backup Sistem
```bash
{
  ./clsdh hostname
  ./clsdh ip-addr
  ./clsdh disk-usage
} > ~/sistem.txt
```

---

> 🇮🇩 Bahasa Indonesia. Versi Inggris tersedia di `linux/examples-en.md`.
