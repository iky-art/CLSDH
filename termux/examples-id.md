# 📝 Contoh Penggunaan CLSDH di Termux (Bahasa Indonesia)

> Contoh skrip dan perintah nyata untuk Termux.

---

## 📊 Monitor Jaringan 24 Jam
```bash
nohup ./clsdh net-stats > ~/network.log 2>&1 &
```

## 🔍 Pengecekan Link Massal
```bash
cat urls.txt | while read url; do
  ./clsdh link-check "$url" --timeout 5
done > ~/link-results.txt
```

## 🔐 Pengecekan SSL Cert
```bash
./clsdh ssl-cert google.com 443
./clsdh ssl-cert github.com 443
```

## 📦 Backup Informasi Sistem
```bash
{
  echo "=== Hostname ==="
  ./clsdh hostname
  echo "=== IP ==="
  ./clsdh ip-addr
  echo "=== Disk ==="
  ./clsdh disk-usage
} > ~/sistem-info.txt
```

## 🔑 Generate Password Acak
```bash
./clsdh password-gen 20
```

---

> 🇮🇩 Bahasa Indonesia. Versi Inggris tersedia di `termux/examples-en.md`.
