# 🔧 CLSDH Troubleshooting on macOS (English)

> Common issues and solutions on macOS.

---

## ❌ "g++: command not found"
Install Xcode Command Line Tools:
```bash
xcode-select --install
```

## ❌ "Permission denied"
Give execute permission:
```bash
chmod +x clsdh
```

## ❌ Ports below 1024
Use sudo:
```bash
sudo ./clsdh port-scan localhost 1 100
```

---

> 🇬🇧 English documentation. Indonesian version available at `macos/troubleshooting-id.md`.
