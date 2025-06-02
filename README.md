# GeoRelato — Cadastro de Catástrofes Naturais

#O que é o código?

Um programa em linguagem C que permite cadastrar relatos de catástrofes, com dados do relator, localização e distância até um ponto fixo (em São Paulo).

#O que o código faz?

- Cadastra nome, documento, email, telefone e localização do relator
- Cadastra tipo, descrição, data, hora, latitude e longitude da catástrofe
- Calcula automaticamente se a catástrofe está dentro de 10 km de um ponto central
- Permite buscar relatos por tipo, localização ou data

#Como rodar?

1. Instale o compilador GCC 
2. Abra o terminal na pasta do projeto
3. Compile com este comando:
gcc main.c -o georelato -lm
4. Depois, rode com:
./georelato

#Por que fiz assim?

- Usamos `struct` para organizar bem os dados
- Calculamos a distância com a fórmula de Haversine (certa para latitude/longitude)
- Usamos `fgets()` + `limparBuffer()` para evitar bugs de leitura
- A interface é texto (terminal) porque é simples e funciona em qualquer computador

#Alunos

- Nome: Luiz Gustavo Lima da Silva, Vicente Casellato Rodriguez 
- RM: 563554, 563865
- Disciplina: Data Structures and Algorithms
- Professor: Erick Toshio Yamamoto
- Ano: 2025


