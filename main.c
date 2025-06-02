#include <stdio.h>      // Biblioteca para entrada e saída padrão
#include <string.h>     // Biblioteca para manipulação de strings
#include <stdlib.h>     // Biblioteca padrão para funções como malloc, free, etc.
#include <math.h>       // Biblioteca para funções matemáticas como pow, sin, etc.

#define PI 3.141592653589793     // Definição de PI com precisão
#define R 6371.0                 // Raio da Terra em km
#define MAX_RELATOS 10          // Número máximo de relatos permitidos

// Estrutura para armazenar dados do relator
struct Relator {
  char nome[50];
  char documento[20];
  char email[80];
  char telefone[20];
  char localizacao[50];
};

// Estrutura para armazenar dados do relato
struct Relato {
  char tipo[50];
  char descricao[200];
  char data[11];
  char hora[6];
  double latitude;
  double longitude;
};

// Estrutura para armazenar coordenadas geográficas
struct Coordenadas {
  double latitude;
  double longitude;
};

// Protótipo necessário para evitar erros de tipo conflitante
double calculaDistancia(struct Coordenadas pontoFixo, struct Coordenadas pontoUsuario);

// Função para converter graus em radianos
double grausParaRadianos(double graus) {
    return graus * PI / 180.0;
}

// Coordenadas do ponto fixo (ex: corpo de bombeiros)
struct Coordenadas pontoFixo = {-23.550370, -46.634470};

// Função para limpar o buffer de entrada
void limparBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF) { }
}

// Função para cadastrar os dados do relator
void CadastrarRelator(struct Relator *r) {
  printf("\nDigite seu nome: ");
  fflush(stdout);
  fgets(r->nome, sizeof(r->nome), stdin);
  r->nome[strcspn(r->nome, "\n")] = '\0';

  printf("Digite seu documento (CPF/RG): ");
  fflush(stdout);
  fgets(r->documento, sizeof(r->documento), stdin);
  r->documento[strcspn(r->documento, "\n")] = '\0';

  printf("Digite seu email: ");
  fflush(stdout);
  fgets(r->email, sizeof(r->email), stdin);
  r->email[strcspn(r->email, "\n")] = '\0';

  printf("Digite seu telefone: ");
  fflush(stdout);
  fgets(r->telefone, sizeof(r->telefone), stdin);
  r->telefone[strcspn(r->telefone, "\n")] = '\0';

  printf("Digite sua localização: ");
  fflush(stdout);
  fgets(r->localizacao, sizeof(r->localizacao), stdin);
  r->localizacao[strcspn(r->localizacao, "\n")] = '\0';
}

// Função para cadastrar os dados do relato
void CadastrarRelato(struct Relato *r) {
  printf("\nDigite o tipo da catástrofe: ");
  fflush(stdout);
  fgets(r->tipo, sizeof(r->tipo), stdin);
  r->tipo[strcspn(r->tipo, "\n")] = '\0';

  printf("Digite a descrição da catástrofe: ");
  fflush(stdout);
  fgets(r->descricao, sizeof(r->descricao), stdin);
  r->descricao[strcspn(r->descricao, "\n")] = '\0';

  printf("Digite a data da catástrofe (YYYY-MM-DD): ");
  fflush(stdout);
  if (fgets(r->data, sizeof(r->data), stdin)) {
    char *p = strchr(r->data, '\n');
    if (p) {
      *p = '\0';
    } else {
      limparBuffer();  // Limpa o buffer se necessário
    }
  }

  printf("Digite a hora da catástrofe (HH:MM): ");
  fflush(stdout);
  fgets(r->hora, sizeof(r->hora), stdin);
  r->hora[strcspn(r->hora, "\n")] = '\0';

  printf("Digite a latitude do local da catástrofe: ");
  fflush(stdout);
  scanf("%lf", &r->latitude);
  limparBuffer();

  printf("Digite a longitude do local da catástrofe: ");
  fflush(stdout);
  scanf("%lf", &r->longitude);
  limparBuffer();
}

// Função para listar todos os relatos cadastrados
void AbrirLista(struct Relator lista_relatores[], struct Relato lista_relatos[], int total_cadastrados) {
  printf("\n==== Lista de Relatos ====\n\n");
  for (int i = 0; i < total_cadastrados; i++) {
    printf("==== Relato #%d ====\n", i + 1);
    printf("--- Relator ---\n");
    printf("| Nome: %s\n", lista_relatores[i].nome);
    printf("| Documento: %s\n", lista_relatores[i].documento);
    printf("| Email: %s\n", lista_relatores[i].email);
    printf("| Telefone: %s\n", lista_relatores[i].telefone);
    printf("| Localização: %s\n", lista_relatores[i].localizacao);
    printf("-------------------\n");
    printf("==== Detalhes do Relato %d ====\n", i + 1);
    printf("| Tipo: %s\n", lista_relatos[i].tipo);
    printf("| Descrição: %s\n", lista_relatos[i].descricao);
    printf("| Data: %s\n", lista_relatos[i].data);
    printf("| Hora: %s\n", lista_relatos[i].hora);
    printf("| Latitude: %.6f\n", lista_relatos[i].latitude);
    printf("| Longitude: %.6f\n", lista_relatos[i].longitude);
    printf("-------------------\n");
  }
}

// Função para calcular a distância entre dois pontos geográficos
double calculaDistancia(struct Coordenadas pontoFixo, struct Coordenadas pontoUsuario) {
  double lat1 = grausParaRadianos(pontoFixo.latitude);
  double lon1 = grausParaRadianos(pontoFixo.longitude);
  double lat2 = grausParaRadianos(pontoUsuario.latitude);
  double lon2 = grausParaRadianos(pontoUsuario.longitude);
  double deltaLat = lat2 - lat1;
  double deltaLon = lon2 - lon1;
  double a = pow(sin(deltaLat/2), 2)
           + cos(lat1)*cos(lat2)*pow(sin(deltaLon/2),2);
  a = fmax(0.0, fmin(1.0, a));  // Corrige possíveis erros de precisão
  double c = 2 * atan2(sqrt(a), sqrt(1 - a));
  double d = R * c;
  if (d > 10)
    printf("\nA catástrofe está fora do raio de 10km do ponto central.\n");
  else
    printf("\nA catástrofe está no raio de 10km do ponto central, ligue e aguarde ajuda.\n");
  return d;
}

// Função para buscar relatos por tipo
void Procurar_Tipo(struct Relato lista_relatos[], int total_cadastrados) {
  char tipo_busca[50];
  printf("\nDigite o tipo de catástrofe que deseja buscar: ");
  fflush(stdout);
  fgets(tipo_busca, sizeof(tipo_busca), stdin);
  tipo_busca[strcspn(tipo_busca, "\n")] = '\0';
  int achou = 0;
  for (int i = 0; i < total_cadastrados; i++) {
    if (strcmp(lista_relatos[i].tipo, tipo_busca) == 0) {
      printf("\n--- Relato encontrado ---\n");
      printf("| Tipo: %s\n", lista_relatos[i].tipo);
      printf("| Descrição: %s\n", lista_relatos[i].descricao);
      printf("| Data: %s\n", lista_relatos[i].data);
      printf("| Hora: %s\n", lista_relatos[i].hora);
      achou = 1;
    }
  }
  if (!achou)
    printf("\nNenhum relato encontrado com o tipo '%s'.\n", tipo_busca);
}

// Função para buscar relatos por localização do relator
void Procurar_Localizacao(struct Relator lista_relatores[], struct Relato lista_relatos[], int total_cadastrados) {
  char localizacao_busca[50];
  printf("\nDigite a localização da catástrofe que deseja buscar: \n");
  fflush(stdout);
  fgets(localizacao_busca, sizeof(localizacao_busca), stdin);
  localizacao_busca[strcspn(localizacao_busca, "\n")] = '\0';
  int achou = 0;
  for (int i = 0; i < total_cadastrados; i++) {
    if (strcmp(lista_relatores[i].localizacao, localizacao_busca) == 0) {
      printf("\n--- Relato encontrado ---\n");
      printf("| Tipo: %s\n", lista_relatos[i].tipo);
      printf("| Descrição: %s\n", lista_relatos[i].descricao);
      printf("| Data: %s\n", lista_relatos[i].data);
      printf("| Hora: %s\n", lista_relatos[i].hora);
      achou = 1;
    }
  }
  if (!achou)
    printf("\nNenhum relato encontrado com a localização '%s'.\n", localizacao_busca);
}

// Função para buscar relatos por data
void Procurar_Data(struct Relato lista_relatos[], int total_cadastrados) {
  char data_busca[11];
  printf("\nDigite a data da catástrofe que deseja buscar (YYYY-MM-DD): ");
  fflush(stdout);
  fgets(data_busca, sizeof(data_busca), stdin);
  data_busca[strcspn(data_busca, "\n")] = '\0';
  int achou = 0;
  for (int i = 0; i < total_cadastrados; i++) {
    if (strcmp(lista_relatos[i].data, data_busca) == 0) {
      printf("\n--- Relato encontrado ---\n");
      printf("| Tipo: %s\n", lista_relatos[i].tipo);
      printf("| Descrição: %s\n", lista_relatos[i].descricao);
      printf("| Data: %s\n", lista_relatos[i].data);
      printf("| Hora: %s\n", lista_relatos[i].hora);
      achou = 1;
    }
  }
  if (!achou)
    printf("\nNenhum relato encontrado com a data '%s'.\n", data_busca);
}

// Função principal
int main() {
  struct Relator relatores[MAX_RELATOS];
  struct Relato relatos[MAX_RELATOS];
  int num_relatos_cadastrados = 0;
  char opcao = 's', continuar_busca = 's';
  int escolha_busca;

  // Loop para cadastro de relatos
  while ((opcao=='s'||opcao=='S') && num_relatos_cadastrados < MAX_RELATOS) {
    printf("\n--- Cadastro de Novo Relato (%d/%d) ---",
           num_relatos_cadastrados+1, MAX_RELATOS);
    CadastrarRelator(&relatores[num_relatos_cadastrados]);
    CadastrarRelato(&relatos[num_relatos_cadastrados]);
    num_relatos_cadastrados++;
    if (num_relatos_cadastrados<MAX_RELATOS) {
      printf("\nDeseja cadastrar outro relato? (s/n): ");
      fflush(stdout);
      scanf(" %c",&opcao); limparBuffer();
    } else {
      printf("\nNúmero máximo de relatos (%d) atingido.\n", MAX_RELATOS);
      break;
    }
  }

  AbrirLista(relatores, relatos, num_relatos_cadastrados);

  // Calcula a distância de cada relato até o ponto fixo
  for (int i = 0; i < num_relatos_cadastrados; i++) {
    struct Coordenadas pontou = { relatos[i].latitude, relatos[i].longitude };
    double d = calculaDistancia(pontoFixo, pontou);
    printf("Distância até o corpo de bombeiros: %.2fkm\n", d);
  }

  // Loop para buscas
  printf("\nDeseja procurar um relato? (s/n): ");
  fflush(stdout);
  scanf(" %c",&continuar_busca); limparBuffer();
  while (continuar_busca=='s'||continuar_busca=='S') {
    printf("\n--- Opções de Busca ---");
    printf("\n1. Buscar por Tipo de Catástrofe");
    printf("\n2. Buscar por Localização do Relator");
    printf("\n3. Buscar por Período (Data) da Catástrofe");
    printf("\nDigite o número da opção desejada: ");
    fflush(stdout);
    if (scanf("%d",&escolha_busca)!=1) escolha_busca = -1;
    limparBuffer();

    switch (escolha_busca) {
      case 1: Procurar_Tipo(relatos, num_relatos_cadastrados); break;
      case 2: Procurar_Localizacao(relatores, relatos, num_relatos_cadastrados); break;
      case 3: Procurar_Data(relatos, num_relatos_cadastrados); break;
      default: printf("\nOpção inválida.\n");
    }

    printf("\n\nDeseja procurar outro relato? (s/n): ");
    fflush(stdout);
    scanf(" %c",&continuar_busca); limparBuffer();
  }

  printf("\n--- Fim do Programa ---\n");
  return 0;
}





