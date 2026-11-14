# 📝 CLSDH Usage Examples on Termux (English)

> Real scripts and commands for Termux.

---

## 📊 24-Hour Network Monitor
```bash
nohup ./clsdh net-stats > ~/network.log 2>&1 &
```

## 🔍 Mass Link Checking
```bash
cat urls.txt | while read url; do
  ./clsdh link-check "$url" --timeout 5
done > ~/link-results.txt
```

## 🔐 SSL Certificate Check
```bash
./clsdh ssl-cert google.com 443
./clsdh ssl-cert github.com 443
```

## 📦 Backup System Information
```bash
{
  echo "=== Hostname ==="
  ./clsdh hostname
  echo "=== IP ==="
  ./clsdh ip-addr
  echo "=== Disk ==="
  ./clsdh disk-usage
} > ~/system-info.txt
```

## 🔑 Generate Random Password
```bash
./clsdh password-gen 20
```

---

> 🇬🇧 English documentation. Indonesian version available at `termux/examples-id.md`.
