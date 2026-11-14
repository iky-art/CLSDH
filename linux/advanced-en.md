# 🚀 Advanced CLSDH Guide on Linux (English)

> Advanced tips for Linux users.

---

## ⚡ Run in Background
```bash
nohup ./clsdh net-stats > ~/net.log 2>&1 &
```

## 🔐 Low Port Access
```bash
sudo ./clsdh port-scan localhost 1 100
```

## 🔄 Create Alias (Optional)
Add to `~/.bashrc`:
```bash
alias clsdh="$HOME/CLSDH/clsdh"
```

---

> 🇬🇧 English documentation. Indonesian version available at `linux/advanced-id.md`.
