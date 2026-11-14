# 🔧 Troubleshooting CLSDH di macOS (Bahasa Indonesia)

> Masalah umum dan solusi di macOS.

---

## ❌ "g++: command not found"
Instal Xcode Command Line Tools:
```bash
xcode-select --install
```

## ❌ "Permission denied"
Berikan izin eksekusi:
```bash
chmod +x clsdh
```

## ❌ Port di bawah 1024
Gunakan sudo:
```bash
sudo ./clsdh port-scan localhost 1 100
```

---

> 🇮🇩 Bahasa Indonesia. Versi Inggris tersedia di `macos/troubleshooting-en.md`.
