FROM ubuntu:22.04 AS builder

# Установка зависимостей
RUN apt-get update && \
    apt-get install -y cmake g++ && \
    rm -rf /var/lib/apt/lists/*

WORKDIR /app

# Копируем только исходные файлы (исключаем build-директорию)
COPY CMakeLists.txt ./
COPY src/ ./src/
COPY include/ ./include/
COPY tests/ ./tests/
# Сборка проекта
RUN cmake -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build --target rpn_calculator --parallel 2

# Финальный образ
FROM ubuntu:22.04

WORKDIR /app

# Копируем только собранный бинарник
COPY --from=builder /app/build/rpn_calculator .

# Устанавливаем зависимости для runtime (если нужны)
RUN apt-get update && \
    apt-get install -y libstdc++6 && \
    rm -rf /var/lib/apt/lists/*

CMD ["./rpn_calculator"]
