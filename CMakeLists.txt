cmake_minimum_required(VERSION 3.12)
project(TetrisMirror)
set(CMAKE_BUILD_TYPE "Release")


set(SOURCES
Src/Accounts.cpp
Src/Application.cpp
Src/button.cpp
Src/Command.cpp
Src/CommandQueue.cpp
Src/Component.cpp
Src/Container.cpp
Src/GameoverState.cpp
Src/GameSettingsState.cpp
Src/GameState.cpp
Src/KeySettingState.cpp
Src/Label.cpp
Src/LoadSavesState.cpp
Src/LoginState.cpp
Src/MagicState.cpp
Src/Main.cpp
Src/MenuState.cpp
Src/MusicPlayer.cpp
Src/PauseState.cpp
Src/RankState.cpp
Src/SaveGameState.cpp
Src/Saves.cpp
Src/SoundPlayer.cpp
Src/State.cpp
Src/StateStack.cpp
Src/TextField.cpp
Src/TitleState.cpp
Src/Utility.cpp
)

set(HEADERS
Inc/Accounts.h
Inc/Application.h
Inc/Button.h
Inc/Command.h
Inc/CommandQueue.h
Inc/Component.h
Inc/Container.h
Inc/Foreach.h
Inc/GameoverState.h
Inc/GameSettingsState.h
Inc/GameState.h
Inc/KeyBindingButton.h
Inc/KeySettingState.h
Inc/Label.h
Inc/LoadSavesState.h
Inc/LoginState.h
Inc/MagicState.h
Inc/MenuState.h
Inc/MusicPlayer.h
Inc/PauseState.h
Inc/RankState.h
Inc/ResourceHolder.h
Inc/ResourceHolder.inl
Inc/ResourceIdentifiers.h
Inc/SaveGameState.h
Inc/Saves.h
Inc/SoundPlayer.h
Inc/State.h
Inc/StateIdentifiers.h
Inc/StateStack.h
Inc/TextField.h
Inc/TitleState.h
Inc/Utility.h
)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)  # 或者使用适当的C++标准版本

# 设置SFML库的路径
set(SFML_DIR "build/SFML-2.5.1/lib/cmake/SFML")  
# 查找SFML库的依赖项
find_package(SFML 2.5.1 COMPONENTS system window graphics REQUIRED)

# 添加可执行文件
add_executable(TetrisMirror ${SOURCES} ${HEADERS})

# 链接SFML库
target_link_libraries(TetrisMirror sfml-system sfml-window sfml-graphics sfml-audio)

target_include_directories(TetrisMirror PRIVATE Inc)
