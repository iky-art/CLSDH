# 📝 CLSDH Usage Examples on macOS (English)

> Real scripts for macOS.

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

> 🇬🇧 English documentation. Indonesian version available at `macos/examples-id.md`.
