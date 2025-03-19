#!/bin/bash

# Definindo a animação de carregamento
spin=("⠁" "⠃" "⠇" "⠧" "⠷" "⠿" "⠷" "⠧" "⠇" "⠃")

# Animar carregamento
for i in {1..1}; do
  for j in "${spin[@]}"; do
    echo -ne "$j\r"
    sleep 0.1
  done
done
