# 📝 Contoh Penggunaan CLSDH di Windows (Bahasa Indonesia)

> Contoh skrip nyata untuk Windows.

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

> 🇮🇩 Bahasa Indonesia. Versi Inggris tersedia di `windows/examples-en.md`.
