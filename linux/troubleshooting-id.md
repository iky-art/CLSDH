# 🔧 Troubleshooting CLSDH di Linux (Bahasa Indonesia)

> Masalah umum dan solusi di Linux.

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

## ❌ Port di bawah 1024
```bash
sudo ./clsdh port-scan localhost 1 100
```

---

> 🇮🇩 Bahasa Indonesia. Versi Inggris tersedia di `linux/troubleshooting-en.md`.
