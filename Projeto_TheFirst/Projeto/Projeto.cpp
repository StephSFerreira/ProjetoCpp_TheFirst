#include <iostream>
// #include <ctime> // permite obter horario e data diretamente da maquina
#include <string>
#include <chrono>
#include <iomanip> // para poder definir largura na matriz
#include <locale> // biblioteca para caracteres
using namespace std;




void printMatriz(string** mat, int l, int c)
{
    // Cabeçalho
    cout << left << setw(10) << "ID" << setw(20) << "Descrição" << setw(15) << "Quantidade" << setw(15) << "Preço" << endl;
    cout << "------------------------------------------------------------" << endl;

    for (int i = 0; i < l; i++)
    {
        cout << setw(10) << mat[i][0]   // ID do produto
            << setw(20) << mat[i][1]   // Descrição do produto
            << setw(15) << mat[i][2]   // Quantidade
            << setw(15) << fixed << setprecision(2) << stod(mat[i][3])  // Preço
            << endl;

    }
    return;
}


void printVendas(string** vendas, string** produto, int linha)
{
    // Cabeçalho
    cout << left << setw(10) << "ID" << setw(20) << "Descrição" << setw(15) << "Qtd Vendida" << setw(15) << "Total Vendido" << endl;
    cout << "------------------------------------------------------------" << endl;

    // Imprime as vendas
    for (int i = 0; i < linha; i++) {
        cout << setw(10) << produto[i][0]    // ID do produto
            << setw(20) << produto[i][1]    // Descrição do produto
            << setw(15) << vendas[i][0]    // Quantidade vendida
            << setw(15) << fixed << setprecision(2) << stod(vendas[i][1])  // Total vendido
            << endl;
    }
}


string addZero(int num)
{
    if (num < 10)
    {
        return "0" + to_string(num); // Se num for menor que 10, a função retorna o número com um "0" à esquerda
    }
    return to_string(num); // retorna o num em string
}


void printTime()
{
    // Pega o tempo atual do sistema
    auto now = chrono::system_clock::now();
    time_t now_time = chrono::system_clock::to_time_t(now);

    // Usa localtime_s para obter a data e hora atual
    struct tm time_info;
    localtime_s(&time_info, &now_time);  // Note que aqui usamos localtime_s

    // Exibe a data e hora formatada
    cout << "Data e Hora: "
        << addZero(time_info.tm_mday) << "/"  // Adiciona 0 no dia, se necessário
        << addZero(time_info.tm_mon + 1) << "/"  // Adiciona 0 no mês, se necessário (mês começa de 0)
        << (time_info.tm_year + 1900) << " "  // Ano com 1900 adicionado
        << addZero(time_info.tm_hour) << ":"  // Adiciona 0 na hora, se necessário
        << addZero(time_info.tm_min) << ":"  // Adiciona 0 no minuto, se necessário
        << addZero(time_info.tm_sec) << endl;  // Adiciona 0 no segundo, se necessário
}


void matStock(string**& produto, string**& vendas, int StockMax) // matriz initida manualmente para já ter dados exibidos
{
    vendas = new string * [StockMax];
    produto = new string * [StockMax];
    for (int i = 0; i < StockMax; i++)
    {
        produto[i] = new string[4]; // 4 colunas (ID, descrição, Qt, preço)
        vendas[i] = new string[2];   // 2 colunas: Quantidade vendida, Total vendido
        vendas[i][0] = "0";          // Inicializa a quantidade vendida como 0
        vendas[i][1] = "0";          // Inicializa o total vendido como 0
    }

    produto[0][0] = "1"; // coluna ID produto
    produto[0][1] = "Nintendo"; // coluna descrição
    produto[0][2] = "11"; // coluna Qt
    produto[0][3] = "299"; // coluna preço

    produto[1][0] = "2"; // coluna ID produto
    produto[1][1] = "PS5"; // coluna descrição
    produto[1][2] = "4"; // coluna Qt
    produto[1][3] = "449"; // coluna preço


    produto[2][0] = "3"; // coluna ID produto
    produto[2][1] = "Xbox"; // coluna descrição
    produto[2][2] = "19"; // coluna Qt
    produto[2][3] = "379"; // coluna preço

    produto[3][0] = "4"; // coluna ID produto
    produto[3][1] = "PC Gaming"; // coluna descrição
    produto[3][2] = "9"; // coluna Qt
    produto[3][3] = "999"; // coluna preço

    produto[4][0] = "5"; // coluna ID produto
    produto[4][1] = "Monitor"; // coluna descrição
    produto[4][2] = "15"; // coluna Qt
    produto[4][3] = "239"; // coluna preço

    produto[5][0] = "6"; // coluna ID produto
    produto[5][1] = "TV"; // coluna descrição
    produto[5][2] = "22"; // coluna Qt
    produto[5][3] = "499"; // coluna preço

}


void atualizarProduto(string**& produto, int StockMax)
{
    string check;  // Permite voltar atrás no menu
    string idAtualizarStr;
    bool entradaValida = false;

    // Pedir um ID válido ao utilizador
    do {
        cout << "Digite o ID do produto a ser atualizado: ";
        cin >> idAtualizarStr;
        entradaValida = true;

        for (char c : idAtualizarStr)
        {
            if (!isdigit(c))
            {
                cout << "Erro: O ID deve conter apenas números positivos. Tente novamente." << endl;
                entradaValida = false;
                break;
            }
        }

        if (entradaValida && stoi(idAtualizarStr) <= 0)
        {
            cout << "Erro: O ID deve ser maior que 0. Tente novamente." << endl;
            entradaValida = false;
        }

    } while (!entradaValida);


    int idAtualizar = stoi(idAtualizarStr);
    bool encontrado = false;

    for (int i = 0; i < StockMax; ++i)
    {
        if (stoi(produto[i][0]) == idAtualizar)
        {
            encontrado = true;
            string novaQuantidade;
            bool quantidadeValida = false;

            cout << "Produto encontrado!" << endl;
            cout << "Digite a quantidade que deseja (0 para cancelar e voltar): ";
            cin >> check;
            if (check == "0")
            {
                break;
            }
            // Pedir uma quantidade válida (não pode ser negativa)
            do {
                cout << "Atualize a quantidade: (0 para cancelar e voltar): " << endl;
                cin >> novaQuantidade;
                if (novaQuantidade == "0")
                {
                    return;
                }
                quantidadeValida = true;

                for (char c : novaQuantidade) {
                    if (!isdigit(c)) {
                        cout << "Erro: A quantidade deve conter apenas números positivos. Tente novamente." << endl;
                        quantidadeValida = false;
                        break;
                    }
                }

                if (quantidadeValida && stoi(novaQuantidade) < 0)
                {
                    cout << "Erro: A quantidade não pode ser negativa. Tente novamente." << endl;
                    quantidadeValida = false;
                }

            } while (!quantidadeValida);

            produto[i][2] = novaQuantidade; // Atualizar a quantidade no stock
            cout << "Produto atualizado com sucesso!" << endl;
            return;
        }
    }

    if (!encontrado)
    {
        cout << "Erro: Produto não encontrado." << endl;
    }
}


void criarProduto(string**& produto, int& linha)
{
    string id, descricao, quantidade, preco;
    char confirmacao;
    bool idRepetido, entradaValida;

    do
    {
        do
        {
            entradaValida = true;
            cout << "Digite o ID do novo produto (0 para cancelar e voltar): ";
            cin >> id;

            if (id == "0") return;

            // Verificar se o ID contém apenas números
            for (char c : id)
            {
                if (!isdigit(c))
                {
                    cout << "Erro: O ID deve conter apenas números. Tente novamente." << endl;
                    entradaValida = false;
                    break;
                }
            }
            if (!entradaValida) continue;

            idRepetido = false;
            for (int i = 0; i < linha; i++)
            {
                if (produto[i][0] == id)
                {
                    cout << "Erro: ID já existente. Tente novamente." << endl;
                    idRepetido = true;
                    break;
                }
            }
        } while (idRepetido || !entradaValida);

        cout << "Digite a descrição do produto (0 para cancelar e voltar): ";
        cin >> descricao;
        if (descricao == "0")
            return;

        do
        {
            entradaValida = true;
            cout << "Digite a quantidade (0 para cancelar e voltar): ";
            cin >> quantidade;

            if (quantidade == "0")
                return;

            for (char c : quantidade)
            {
                if (!isdigit(c))
                {
                    cout << "Erro: A quantidade deve conter apenas números inteiros positivos. Tente novamente." << endl;
                    entradaValida = false;
                    break;
                }
            }
        } while (!entradaValida);

        do
        {
            entradaValida = true;
            cout << "Digite o preço (0 para cancelar e voltar): ";
            cin >> preco;

            if (preco == "0")
                return;

        } while (!entradaValida);

        // Exibir os dados inseridos para confirmação
        cout << endl;
        cout << "Confirme os dados inseridos:" << endl;
        cout << "ID: " << id << endl;
        cout << "Descrição: " << descricao << endl;
        cout << "Quantidade: " << quantidade << endl;
        cout << "Preço: " << preco << endl;

        cout << "Se não deseja confirmar os dados prima (n/N), caso pretenda confirmar prima (s/S): ";
        cin >> confirmacao;
        cout << endl;

    } while (confirmacao == 'n' || confirmacao == 'N');

    // Calcular o preço de venda com 30% de lucro
    double precoVenda = stod(preco) * 1.30;

    // Realocar a memória para adicionar o novo produto
    produto[linha] = new string[4];
    produto[linha][0] = id;
    produto[linha][1] = descricao;
    produto[linha][2] = quantidade;
    produto[linha][3] = to_string(precoVenda);
    linha++;

    cout << "Produto criado com sucesso!" << endl;
}


void eliminarProduto(string**& produto, int& linha)
{
    string idEliminar;
    bool entradaValida = false;

    // Pedir um ID válido ao utilizador
    do {
        cout << "Digite o ID do produto a ser eliminado (0 para cancelar e voltar): ";
        cin >> idEliminar;

        if (stoi(idEliminar) == 0)
        {
            return;
        }

        entradaValida = true; // Supomos que é válido

        for (char c : idEliminar)
        {
            if (!isdigit(c))
            {
                cout << "Erro: O ID nao pode conter letras. " << endl;
                entradaValida = false;
                break;
            }
        }

        if (entradaValida && stoi(idEliminar) <= 0)
        {
            cout << "Erro: O ID deve ser maior que 0. " << endl;
            entradaValida = false;
        }

    } while (!entradaValida);


    int id = stoi(idEliminar); // Agora que temos certeza, podemos converter para int
    bool encontrado = false;

    for (int i = 0; i < linha; ++i)
    {
        if (stoi(produto[i][0]) == id)
        {
            encontrado = true;

            // Confirmação antes de eliminar
            char confirmacao;
            cout << "Produto encontrado." << endl << "Deseja realmente elimina-lo? (S / N): ";
            cin >> confirmacao;

            if (confirmacao == 'n' || confirmacao == 'N')
            {
                cout << "Eliminação cancelada." << endl;
                return;
            }

            // Deslocar os produtos seguintes
            for (int j = i; j < linha - 1; ++j)
            {
                produto[j] = produto[j + 1];
            }

            linha--;  // Reduzir a quantidade de produtos
            cout << "Produto eliminado com sucesso!" << endl;
            return;
        }
    }

    cout << "Produto não encontrado!" << endl;
    system("pause");
}


void efetuarVenda(string**& produto, string**& vendas, int& linha, int& faturaID) {


    srand(time(0));  // Inicializa o gerador de números aleatórios
    int numCliente = rand() % 9000 + 1000; // Gera número entre 1000 e 9999
    // Carrinho de compras (máximo 20 produtos por venda)
    const int MAX_ITEMS = 20;  // máximo de itens no carrinho é de 20 (podemos alterar, mas isso pode impactar o código)
    string carrinho[MAX_ITEMS][3]; // 3 Colunas para cada um das saídas: Nome do produto, Quantidade, Total por item
    int itensNoCarrinho = 0;

    double subtotal = 0.0, totalIVA = 0.0;
    const double IVA = 0.23; // IVA de 23%
    char continuar;
    int id, quantidade;

    do {
        system("cls");
        cout << " *** Efetuar Venda ***" << endl;
        printMatriz(produto, linha, 4);

        // Opção para voltar ao menu anterior
        cout << "Digite 0 para voltar ao menu anterior." << endl;
        cout << "Digite o ID do produto que deseja comprar: ";
        cin >> id;

        if (id == 0)
        {
            cout << "Voltando ao menu anterior..." << endl;
            system("pause");
            return; // Sai da função para retornar ao menu principal
        }

        // Verificação se o produto existe na matriz
        bool encontrado = false;
        for (int i = 0; i < linha; i++)
        {
            if (stoi(produto[i][0]) == id)
            {
                encontrado = true;

                // Quantidade em stock
                cout << "Digite a quantidade que deseja (0 para cancelar e voltar): ";
                cin >> quantidade;

                if (quantidade == 0)
                {
                    cout << "Operação cancelada. Voltando ao menu anterior..." << endl;
                    system("pause");
                    return;
                }

                if (quantidade > stoi(produto[i][2]))
                {
                    cout << "Quantidade insuficiente em stock! Tente novamente." << endl;
                    system("pause");
                    break;
                }

                // Adição ao carrinho 
                carrinho[itensNoCarrinho][0] = produto[i][1]; // Nome do produto
                carrinho[itensNoCarrinho][1] = to_string(quantidade); // Quantidade
                double precoVenda = stod(produto[i][3]); // preço
                carrinho[itensNoCarrinho][2] = to_string(precoVenda * quantidade); // Total por item
                itensNoCarrinho++;

                // Atualizar subtotal e stock
                subtotal += precoVenda * quantidade;
                produto[i][2] = to_string(stoi(produto[i][2]) - quantidade); // Atualizar stock

                // Atualiza a matriz de vendas
                vendas[i][0] = to_string(stoi(vendas[i][0]) + quantidade);  // Atualiza a quantidade vendida
                vendas[i][1] = to_string(stod(vendas[i][1]) + (precoVenda * quantidade));  // Atualiza o total vendido

                break;
            }
        }

        if (!encontrado) {
            cout << "Produto não encontrado! Tente novamente." << endl;
        }

        // Perguntar se deseja continuar comprando
        cout << "Deseja comprar outro produto? (S/N): ";
        cin >> continuar;

    } while ((continuar == 'S' || continuar == 's') && itensNoCarrinho < MAX_ITEMS);

    // Sorteio da venda gratuita (1 em cada 10 vendas)
    bool vendaGratuita = (rand() % 5 == 0);

    if (vendaGratuita)
    {
        cout << "PARABÉNS!   ESTA VENDA É GRATUITA!" << endl;
        subtotal = 0.0; // Zerar o valor total
    }

    // Calcular total com IVA
    double valorIVA = subtotal * IVA;
    double totalSemIva = subtotal - valorIVA;



    // Resumo de venda
    system("cls");
    cout << " *** Resumo de Venda ***" << endl << endl;
    printTime();
    cout << endl;
    //cout << "Número da Fatura: " << faturaID++ << endl;
    //cout << "Número do Cliente: " << numCliente << endl; // <-- Aqui adicionamos o número do cliente
    cout << "------------------------------------------------------" << endl;
    cout << left << setw(20) << "Produto" << setw(10) << "Qtd" << setw(10) << "Preço und." << setw(15) << "Preço total" << endl;

    for (int i = 0; i < itensNoCarrinho; i++) {
        cout << left << setw(20) << carrinho[i][0]
            << setw(10) << carrinho[i][1]
            << setw(10) << fixed << setprecision(2) << stod(carrinho[i][2]) / stod(carrinho[i][1])
            << setw(15) << fixed << setprecision(2) << stod(carrinho[i][2]) << endl;
    }

    cout << "------------------------------------------------------" << endl;
    cout << "Valor (s/IVA): " << fixed << setprecision(2) << totalSemIva << "$" << endl;
    cout << "IVA (23%): " << fixed << setprecision(2) << valorIVA << "$" << endl;
    cout << "Total (c/IVA): " << fixed << setprecision(2) << subtotal << "$" << endl;
    cout << endl;

    // Se a venda for gratuita, não há pagamento
    if (vendaGratuita) {
        cout << "!!!!! VENDA GRATUITA! O CLIENTE NÃO PAGA NADA!!!!!!!!" << endl;
        system("pause");
        return;
    }


    // Pagamento
    double valorEntregue, troco;
    cout << "Digite o valor entregue pelo cliente: ";
    cin >> valorEntregue;

    while (valorEntregue < subtotal)
    {
        cout << "Valor insuficiente. Digite um valor maior ou igual a " << fixed << setprecision(2) << subtotal << ": ";
        cin >> valorEntregue;
    }

    troco = valorEntregue - subtotal;
    cout << "Troco: " << fixed << setprecision(2) << troco << "$" << endl;

    system("pause");


    // Talão de venda
    system("cls");
    cout << endl << endl;
    cout << " *** Talão de Venda ***" << endl << endl;
    printTime();
    cout << endl;
    cout << "Número da Fatura: " << faturaID++ << endl;
    cout << "Número do Cliente: " << numCliente << endl; // <-- Aqui adicionamos o número do cliente
    cout << "------------------------------------------------------" << endl;
    cout << left << setw(20) << "Produto" << setw(10) << "Qtd" << setw(10) << "Preço und." << setw(15) << "Preço total" << endl;

    for (int i = 0; i < itensNoCarrinho; i++) {
        cout << left << setw(20) << carrinho[i][0]
            << setw(10) << carrinho[i][1]
            << setw(10) << fixed << setprecision(2) << stod(carrinho[i][2]) / stod(carrinho[i][1])
            << setw(15) << fixed << setprecision(2) << stod(carrinho[i][2]) << endl;
    }

    cout << "------------------------------------------------------" << endl;
    cout << "Valor (s/IVA): " << fixed << setprecision(2) << totalSemIva << "$" << endl;
    cout << "IVA (23%): " << fixed << setprecision(2) << valorIVA << "$" << endl;
    cout << "Total (c/IVA): " << fixed << setprecision(2) << subtotal << "$" << endl;
    cout << "Total Pago: " << valorEntregue << "$" << endl;
    cout << "Troco: " << troco << "$" << endl;
    cout << "------------------------------------------------------" << endl << endl;
    cout << "Obrigado pela preferência. Volte sempre! " << endl << endl;

    system("pause");

}


void MenuVenda(string**& produto, string**& vendas, int& linha, int& faturaID)
{
    char opção;
    do
    {
        system("cls"); // limpar consola

        printMatriz(produto, linha, 4);
        cout << endl << endl;
        cout << "**************************************" << endl;
        cout << "*           MENU VENDAS              *" << endl;
        cout << "**************************************" << endl;
        cout << "*  1. Efetuar venda                  *" << endl;
        cout << "*  2. Histórico de Vendas            *" << endl;
        cout << "*  3. Sair                           *" << endl;
        cout << "**************************************" << endl << endl;
        cout << endl;
        printTime();
        cout << endl;
        cout << "Escolha uma opção de 1 a 3: " << endl;

        while (true) {
            cin >> opção;

            // Verifica se a entrada é válida (1 ou 3)
            if (opção >= '1' && opção <= '3') {
                break;
            }
            else {
                cout << "Escolha inválida. Por favor, insira um número de 1 a 3." << endl;
                system("pause");
            }
        }

        switch (opção)
        {
        case '1':
            cout << endl << " *** Efetuar venda *** " << endl;
            efetuarVenda(produto, vendas, linha, faturaID);
            return;

        case '2':
            system("cls");
            cout << "Histórico de vendas: " << endl << endl;
            printVendas(vendas, produto, linha);

        case '3':
            cout << endl << "Voltar para Menu inicial " << endl;
            system("pause");
            break;

        }

    } while (opção != '3');
}


void MenuStock(string**& produto, int& linha, int StockMax)
{
    char opção;
    do
    {

        system("cls"); // limpar consola

        printMatriz(produto, linha, 4);
        cout << endl << endl;

        cout << "**************************************" << endl;
        cout << "*            MENU STOCK              *" << endl;
        cout << "**************************************" << endl;
        cout << "*  1. Atualizar produtos             *" << endl;
        cout << "*  2. Criar produtos                 *" << endl;
        cout << "*  3. Sair                           *" << endl;
        cout << "**************************************" << endl << endl;
        printTime();
        cout << endl;
        cout << "Escolha uma opção de 1 a 3: " << endl;

        while (true) {
            cin >> opção;

            // Verifica se o valor de "opção" está dentro do intervalo esperado (1 a 3)
            if (opção >= '1' && opção <= '3')
            {
                break;  // Se a entrada for válida (entre 1 e 3), sai do loop
            }
            else
            {
                cout << "Escolha inválida. Por favor, insira um número de 1 a 3." << endl;
                system("pause");
                break;
            }

        }

        switch (opção)
        {
        case '1':
            cout << endl << " *** Atualizar produtos *** " << endl;
            atualizarProduto(produto, StockMax);
            return;


        case '2':
            cout << endl << " *** Criar produtos *** " << endl;
            criarProduto(produto, linha);

            return;

        default:
            cout << "Escolha uma opção válida. " << endl;
        }

    } while (opção != '3');
}


void MenuEliminar(string**& produto, int& linha)
{
    char opção;
    do
    {
        system("cls"); // limpar consola

        printMatriz(produto, linha, 4);
        cout << endl << endl;
        cout << "**************************************" << endl;
        cout << "*          MENU ELIMINAR            *" << endl;
        cout << "**************************************" << endl;
        cout << "*  1. Eliminar produtos             *" << endl;
        cout << "*  2. Sair                          *" << endl;
        cout << "**************************************" << endl << endl;

        /* printMatriz(produto, linha, 4);
         cout << endl;*/

        cout << "Escolha uma opção de 1 a 2 : " << endl;
        while (true) {
            cin >> opção;

            // Verifica se o valor de "opção" está dentro do intervalo esperado (1 a 2)
            if (opção >= '1' && opção <= '2')
            {
                break;  // Se a entrada for válida (entre 1 e 2), sai do loop
            }
            else
            {
                cout << "Escolha inválida. Por favor, insira um número de 1 a 2." << endl;
                system("pause");
                break;
            }

        }

        switch (opção)
        {
        case '1':
            cout << endl << " *** Eliminar produtos *** " << endl;
            eliminarProduto(produto, linha);

            return;

        case '2':
            cout << "Voltar para Menu inicial " << endl;
            break;

        default:
            cout << "Escolha uma opção válida. " << endl;
        }


    } while (opção != '2');
}


void Menu()
{
    // Cabeçalho com bordas e título
    cout << "*****************************************************" << endl;
    cout << "*                                                   *" << endl;
    cout << "*              *** MENU PRINCIPAL ***               *" << endl;
    cout << "*                                                   *" << endl;
    cout << "*****************************************************" << endl << endl;

    // Exibe as opções com destaque
    cout << setw(5) << "" << "1. Efetuar venda / Consultar Histórico" << endl;
    cout << setw(5) << "" << "2. Criar / Atualizar produto" << endl;
    cout << setw(5) << "" << "3. Eliminar produto" << endl;
    cout << setw(5) << "" << "4. Sair" << endl << endl;

    // Barra separadora
    cout << "-----------------------------------------------------" << endl;

    // Exibe a data/hora atual
    cout << endl;
    printTime();
    cout << endl;

    // Mensagem final
    cout << "*****************************************************" << endl << endl;
    cout << "Escolha uma opção (1-4): ";
}


int main()
{
    int linha = 6; // define a primeira vazia a atualizar
    int StockMax = 20;
    int totalTaloes = 0; // Número de talões registados


    int faturaID = 1; // Inicia o número da fatura a partir de 1
    string** produto;
    string** vendas;
    matStock(produto, vendas, StockMax);
    setlocale(LC_ALL, ""); //configura a localidade global para a localidade padrão do sistema.
    char opção;
    do
    {
        system("cls"); // limpar consola
        Menu();
        while (true) {
            cin >> opção;

            // Verifica se o valor de "opção" está dentro do intervalo esperado (1 a 4)
            if (opção >= '1' && opção <= '4')
            {
                break;  // Se a entrada for válida (entre 1 e 4), sai do loop
            }
            else
            {
                cout << "Escolha inválida. Por favor, insira um número de 1 a 4." << endl;
                system("pause");
                break;
            }

        }

        switch (opção)
        {
        case '1':
            cout << endl << "Vendas: " << endl;
            MenuVenda(produto, vendas, linha, faturaID);
            break;

        case '2':
            cout << endl << "Criar / Atualizar produto: " << endl << endl;
            MenuStock(produto, linha, StockMax);
            break;

        case '3':
            cout << endl << "Eliminar produto: " << endl;
            MenuEliminar(produto, linha);
            break;

        case '4':
            cout << endl << "Programa encerrado. " << endl;
            break;

        default:
            cout << "Escolha uma opção válida. " << endl;
            system("pause");
        }

    } while (opção != '4');

}
