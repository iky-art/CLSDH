# 🔧 CLSDH Troubleshooting on Linux (English)

> Common issues and solutions on Linux.

---

## ❌ "g++: command not found"
```bash
sudo apt install g++    # Ubuntu/Debian
sudo dnf install gcc-c++  # CentOS/Fedora
```

## ❌ "Permission denied"
```bash
chmod +x clsdh
```

## ❌ Ports below 1024
```bash
sudo ./clsdh port-scan localhost 1 100
```

---

> 🇬🇧 English documentation. Indonesian version available at `linux/troubleshooting-id.md`.
