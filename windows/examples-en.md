# 📝 CLSDH Usage Examples on Windows (English)

> Real scripts for Windows.

---

## 📊 Network Monitor
```bash
nohup ./clsdh net-stats > ~/network.log 2>&1 &
```

## 🔍 SSL Check
```bash
./clsdh ssl-cert google.com 443
```

## 💾 System Backup
```bash
{
  ./clsdh hostname
  ./clsdh ip-addr
  ./clsdh disk-usage
} > ~/system.txt
```

---

> 🇬🇧 English documentation. Indonesian version available at `windows/examples-id.md`.
