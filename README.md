# Đồ án môn LTHĐT - Nhóm 05

Đề tài về chương trình quản lý đội bóng của nhóm 05, với sự giúp đỡ của cô Trần Thị Kim Oanh và các thành viên trong nhóm.
### Đồ án có sử dụng thư viện [SFML](https://www.sfml-dev.org/) để xử lý âm thanh trong chương trình.

## Các bước cài đặt và sử dụng
Cài đật [Visual Studio Code](https://code.visualstudio.com/) để bắt đầu sử dụng.

Cài đặt bộ cômg cụ [MSYS2](msys2.org) đã bao gồm trình biên dịch MinGW. Các bước cài đặt có thể xem [tại đây](https://code.visualstudio.com/docs/cpp/config-mingw)

Cài đặt Extension [Code Runner](https://marketplace.visualstudio.com/items?itemName=formulahendry.code-runner) để biên dịch code C++ trong VS Code.

Sau khi cài đặt xong VS Code và các Extension, hãy cài thư viện [SFML](https://www.sfml-dev.org/) để xử lý âm thanh trong chương trình.

1. Download [GCC 7.3.0 MinGW (SEH) - 64-bit](https://www.sfml-dev.org/files/SFML-2.5.1-windows-gcc-7.3.0-mingw-64-bit.zip) và giải nén.


2. Copy các file trong thư mục `SFML 2.5.1/bin` vừa giải nén vào `C:\msys64\mingw64\bin`

![This is an image](https://i.imgur.com/B4pCsec.png)

3. Tiếp tục copy các file trong thư mục `SFML 2.5.1/lib` vừa giải nén vào `C:\msys64\mingw64\lib`

![This is an image](https://i.imgur.com/QeQ2vxb.png)

## Hướng dẫn sử dụng

1. Clone repository này hoăc download `.zip` file và mở file source code `Main_MS_DOS.cpp` biên dịch và chạy hoặc cũng có thể chạy trực tiếp file `Main_MS_DOS.exe` được biên dịch sẵn. và đây là kết quả: 

![This is an image](https://i.imgur.com/rLfzVum.png)

 2. Để bật/tắt âm thanh, mở file `Main_MS_DOS.cpp` và sửa:

```cpp
...
bool isAudioOn = true; //true = on, false = off
...
```
## Các thành viên của nhóm

#### Bùi Trương Phương [@buitruongphuong](https://github.com/buitruongphuong)
#### Nguyễn Ngọc Anh Tuấn [@Tuan2002](https://github.com/Tuan2002)
#### Nguyễn Duy Nguyên [@Nguyen160603](https://github.com/Nguyen160603)
#### Dương Đình Tuấn [@tuan27227](https://github.com/tuan27227)


