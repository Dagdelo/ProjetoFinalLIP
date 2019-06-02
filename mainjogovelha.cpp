#include "mainjogovelha.h"
#include "ui_mainjogovelha.h"

#include <QPainter>
#include <QPen>

MainJogoVelha::MainJogoVelha(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainJogoVelha),
  JV(),
  NumX("-"),
  NumO("-")
{
  ui->setupUi(this);

  // Fixa o comportamento de selecao do jogo da velha
  ui->jogoVelha->setSelectionMode(QAbstractItemView::NoSelection);
  ui->jogoVelha->setTabKeyNavigation(false);

  // Fixa as propriedades dos QLabel do jogador da vez e do vitorioso
  ui->imgVez->setAlignment(Qt::AlignCenter);
  ui->imgVez->setStyleSheet("background: white");

  ui->imgVencedor->setAlignment(Qt::AlignCenter);
  ui->imgVencedor->setStyleSheet("background: white");

  // Cria os widgets QLabel que compoem a tabela do jogo da velha
  // Depois de criado, insere em cada QLabel a imagem correta
  for (int i=0; i<3; i++) for (int j=0; j<3; j++)
  {
    QLabel *prov = new QLabel;
    prov->setAlignment(Qt::AlignCenter);
    //prov->setGeometry(0,0,30,30);
    prov->setStyleSheet("background: lightcyan");
    ui->jogoVelha->setCellWidget(i,j,prov);
    exibirImagem(i,j);
  }

  // Exibe as imagens do jogador da vez e do vitorioso
  exibirJogadores();

  // Insere os widgets da barra de status
  statusBar()->insertWidget(0,new QLabel("Jogador X: "));
  statusBar()->insertWidget(1,&NumX);
  statusBar()->insertWidget(2,new QLabel("   Jogador O: "));
  statusBar()->insertWidget(3,&NumO);
  // Exibe os numeros de casas corretos
  exibirNumeroCasas();
}

void MainJogoVelha::exibirImagem(int I, int J)
{
  QLabel *cell = (QLabel*)ui->jogoVelha->cellWidget(I,J);
  cell->setText(QString(JV(I,J)));
}

void MainJogoVelha::exibirJogadores()
{
  // Imagem do jogador da vez
  ui->imgVez->setText(QString(JV.jogadorVez()));

  // Imagem do jogador vitorioso
  ui->imgVencedor->setText(QString(JV.vencedor()));
}

void MainJogoVelha::exibirNumeroCasas()
{
  NumX.setText(QString::number(JV.numX()));
  NumO.setText(QString::number(JV.numO()));
}

MainJogoVelha::~MainJogoVelha()
{
  delete ui;
}

void MainJogoVelha::on_actionSair_triggered()
{
  QCoreApplication::quit();
}

void MainJogoVelha::on_jogoVelha_doubleClicked(const QModelIndex &index)
{
  int I = index.row();
  int J = index.column();
  if (JV.jogadaValida(I,J))
  {
    JV.fazerJogada(I,J);
    exibirImagem(I,J);
  }
  exibirJogadores();
  exibirNumeroCasas();
}

void MainJogoVelha::on_actionReiniciar_triggered()
{
  JV.reiniciar();
  for (int i=0; i<3; i++) for (int j=0; j<3; j++)
  {
    exibirImagem(i,j);
  }
  exibirJogadores();
  exibirNumeroCasas();
}
