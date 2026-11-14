# 🗑️ Uninstall CLSDH dari Termux (Bahasa Indonesia)

> Cara menghapus CLSDH dari perangkat Android.

---

## 🗑️ Langkah Uninstall

1. Masuk ke folder CLSDH:
   ```bash
   cd ~/CLSDH
   ```

2. Hapus binary dan folder:
   ```bash
   rm -f clsdh
   cd ..
   rm -rf CLSDH
   ```

3. Atau langsung hapus folder:
   ```bash
   rm -rf ~/CLSDH
   ```

---

## 🧹 Bersihkan Cache (Opsional)

```bash
pkg clean
```

---

> 🇮🇩 Bahasa Indonesia. Versi Inggris tersedia di `termux/uninstall-en.md`.
