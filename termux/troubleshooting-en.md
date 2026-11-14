# 🔧 CLSDH Troubleshooting on Termux (English)

> Guide to handle CLSDH issues specific to Termux.

---

## ❗ Common Issues

### "pkg: command not found"
Make sure you use the official Termux (from F-Droid), not the unsupported Play Store version.

### "g++: command not found"
Install compiler first:
```bash
pkg install clang make -y
```

### "Permission denied" when running ./clsdh
Give execute permission:
```bash
chmod +x clsdh
```

### https:// links timeout
CLSDH doesn't use OpenSSL. Use http:// or check TCP port:
```bash
./clsdh tcp-port example.com 443
```

### Monitor stops by itself
Ensure no battery saving settings restrict Termux. Use:
```bash
termux-wake-lock
```

---

## 📞 Support

Instagram DM: https://instagram.com/iky-art

---

> 🇬🇧 English documentation. Indonesian version available at `termux/troubleshooting-id.md`.
