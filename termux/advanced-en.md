# 🚀 Advanced CLSDH Guide on Termux (English)

> Tips and tricks for advanced Termux users.

---

## ⚡ Performance Optimization

### Run with high priority
```bash
nice -n -10 ./clsdh cpu-monitor
```

### Run in background
```bash
nohup ./clsdh net-stats > ~/net.log 2>&1 &
```

### Limit concurrency for link-check
```bash
./clsdh link-check https://site.com --concurrency 5 --timeout 15
```

---

## 🔐 Storage Access

Allow Termux to access internal storage:
```bash
termux-setup-storage
```

Then save results to:
```bash
./clsdh link-check https://site.com -o ~/storage/downloads/result.txt
```

---

## 🔄 Automation with Cron

Termux supports cron via `cronie`:
```bash
pkg install cronie
crond
crontab -e
```

Add schedule:
```
*/5 * * * * /data/data/com.termux/files/home/CLSDH/clsdh link-check https://site.com >> ~/monitor.log
```

---

## 📱 Termux:Widget

Create shortcut on Android home screen:
1. Open Termux:Widget
2. Select your favorite CLSDH script
3. Add widget to home screen

---

> 🇬🇧 English documentation. Indonesian version available at `termux/advanced-id.md`.
