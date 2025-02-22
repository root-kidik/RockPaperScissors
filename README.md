# Rock Paper Scissors

## Build

### Важно

- Нужно немного подождать
  - `conan` - пытается выкачать `qt6`, т.к. мы в `России` - с официального сайта не получается и он перебирает зеркала (минут `5`)
  - `Qt6`: 
    - `Linux` в данный момент сборка не закеширована в следствии чего один раз локально будет собираться из исходников
    - `Windows` закешированный, но всёравно нужно выкачать бинари, поэтому всёравно будет зеркала перебирать

### Linux (Ubuntu 24.10)

- сборка и запуск: `./build_and_run_linux.sh`
- запуск: `./run_linux.sh`

### Windows (Windows 11 24H2)

- [git](https://github.com/git-for-windows/git/releases/download/v2.47.1.windows.2/Git-2.47.1.2-64-bit.exe)
- [visual studio](https://visualstudio.microsoft.com/ru/thank-you-downloading-visual-studio/?sku=Community&channel=Release&version=VS2022&source=VSLandingPage&cid=2030&passive=false)
- [python](https://www.python.org/ftp/python/3.13.1/python-3.13.1-amd64.exe)
- [cmake](https://github.com/Kitware/CMake/releases/download/v3.31.5/cmake-3.31.5-windows-x86_64.msi)

в powershell от имени администратора (нужно для использования `python3-venv`)
```sh
Set-ExecutionPolicy RemoteSigned
```

- сборка и запуск: `.\build_and_run_windows.bat`
- запуск: `.\run_windows.bat`

## Принятые решения для реализации задачи

- `docs` - документация, которая была написана в 1 день разработки (план минимум), всё готово, доку нужно обновить
- `assets` - игровые ресурсы
- разделение проекта на `2` библиотеки + `1` исполняемый файл:
- `src`
  - `domain` - доменная часть, которая отвечает за бизнес задачи.
    - `entity` - сущности, которыми оперирует `client`
    - `handler`:
      - `request` - обработчики запросов от `server`
      - `response` - обработчики ответов от `server`
    - `interface` - интерфейсы, которые предоставляет `client`
    - `model` - модели, которые `client` симулирует
    - `usecase` - атомарные бизнес задачи
    - `util` - всё, что нужно в `domain` части но ни к чему не относится
      - `Property.hpp` - грубо-говоря, что-то похожее на паттерн `observer` или `signal/slots`, `pub/sub`, не суть, главное, что помогает сделать реактивное программирование (например: связать данные с их представлением)
  - `infrastructure` - инфраструктурная часть, которая отвечает за всё остальное, что не имеет прямого отношения к бизнесу.
    - `client` - конкретная реализация интерфейса общения с `client`
    - `storage` - конкретные реализации хранилищ (пока что все `InMemory`)
    - `util` - всё, что нужно в `infrastructure` части но ни к чему не относится
    - `widget` - представление/отображение `model`
      - `Manager` - фабрика по связыванию текущего режима с отображением
    - `RockPaperScissors.[hpp|cpp]` - объединение всех компонентов системы
  - `Main.cpp` - точка входа
- тесты - не хватило времени
