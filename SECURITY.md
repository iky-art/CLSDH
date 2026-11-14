# Security Policy

## Supported Versions

| Version | Supported          |
|---------|-------------------|
| 2.0.0   | :white_check_mark: |

## Reporting a Vulnerability

Jika kamu menemukan kerentanan keamanan di CLSDH, silakan laporkan langsung melalui **Instagram DM**:

📱 **Instagram**: https://instagram.com/iky-art

Mohon sertakan detail berikut dalam laporan kamu:
1. Deskripsi kerentanan
2. Langkah-langkah reproduksi
3. Dampak potensial
4. Saran perbaikan (jika ada)

Kami akan menanggapi laporan dalam **48 jam** dan memberikan update progres perbaikan.

## Support

Butuh bantuan atau memiliki pertanyaan tentang CLSDH?

📱 **Instagram DM**: https://instagram.com/iky-art
🐛 **GitHub Issues**: https://github.com/iky-art/CLSDH/issues

Kami siap membantu melalui Instagram DM paling cepat.

## Keamanan Penggunaan

CLSDH menggunakan raw TCP socket dan tidak bergantung pada library eksternal seperti OpenSSL, sehingga risiko supply chain attack minimal. Namun, beberapa hal perlu diperhatikan:

- Link `https://` tidak didukung secara penuh karena butuh TLS/SSL. Gunakan untuk `http://` atau cek port TCP/UDP saja.
- Beberapa tool memanggil perintah sistem melalui `popen()` (mis. `whois`, `ping`, `openssl`). Pastikan tool tersebut terinstal di sistem tujuan.
- Jangan menjalankan `clsdh` sebagai `root` kecuali diperlukan (mis. untuk port scan di port < 1024).
