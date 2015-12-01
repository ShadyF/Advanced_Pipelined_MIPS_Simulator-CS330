#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <string>
#include <iostream>
MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  CP(),
  ui(new Ui::MainWindow)
{
  CP.init("/Users/macbookpro/Desktop/Advanced_Pipelined_MIPS_Simulator-CS330/gui/Text.txt");
  ui->setupUi(this);
  ui->slot0->setText("");
  ui->slot1->setText("");
  ui->slot2->setText("");
  ui->slot3->setText("");
  ui->slot4->setText("");
  ui->slot5->setText("");
  ui->slot6->setText("");
  ui->slot7->setText("");
  ui->slot8->setText("");
  ui->slot9->setText("");
  ui->slot10->setText("");
  Labels.push_back(make_pair(ui->slot0, -2));
  Labels.push_back(make_pair(ui->slot1, -2));
  Labels.push_back(make_pair(ui->slot2, -2));
  Labels.push_back(make_pair(ui->slot3, -2));
  Labels.push_back(make_pair(ui->slot4, -2));
  Labels.push_back(make_pair(ui->slot5, -2));
  Labels.push_back(make_pair(ui->slot6, -2));
  Labels.push_back(make_pair(ui->slot7, -2));
  Labels.push_back(make_pair(ui->slot8, -2));
  Labels.push_back(make_pair(ui->slot9, -2));
  Labels.push_back(make_pair(ui->slot10, -2));
  memset(used, 0, sizeof(used));
  memset(count, 0, sizeof(count));
  numOfLabelsToUpdate = 0;
  QWidget::setWindowTitle ("Pipelined CPU Simulator with BTB");
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_NextCycle_clicked()
{
  static int w = 0;   //used static int because using numOfLabelsToUpdate caused a wierd bug
                      //where checking if it was < 11 caused it to be forced to 1
  if (w < 11)
    w++;

  CP.run_one_cycle();
  ui->ClockLabel->setText("Clock: " + QString::number(CP.clock - 1));
  ui->FetchBrowser->setText("PC = " + QString::number(CP.FetchStage.pc - 1) +"\r\n" +QString::fromStdString(CP.Parse.getInst(CP.FetchStage.pc - 1)));
  ui->DecodeBrowser->setText("PC = " + QString::number(CP.DecodeStage.pc) +"\r\n" +QString::fromStdString(CP.Parse.getInst(CP.DecodeStage.pc)));
  ui->ExecuteBrowser->setText("PC = " + QString::number(CP.ExecuteStage.pc) +"\r\n" +QString::fromStdString(CP.Parse.getInst(CP.ExecuteStage.pc)));
  ui->MemoryBrowser->setText("PC = " + QString::number(CP.MemoryStage.pc) +"\r\n" +QString::fromStdString(CP.Parse.getInst(CP.MemoryStage.pc)));
  ui->WriteBackBrowser->setText("PC = " + QString::number(CP.WBStage.pc) +"\r\n" +QString::fromStdString(CP.Parse.getInst(CP.WBStage.pc)));
  //show regs
  ui->R0->setText(QString::number(CP.Regs->at(0)));
  ui->R1->setText(QString::number(CP.Regs->at(1)));
  ui->R2->setText(QString::number(CP.Regs->at(2)));
  ui->R3->setText(QString::number(CP.Regs->at(3)));
  ui->R4->setText(QString::number(CP.Regs->at(4)));
  ui->R5->setText(QString::number(CP.Regs->at(5)));
  ui->R6->setText(QString::number(CP.Regs->at(6)));
  ui->R7->setText(QString::number(CP.Regs->at(7)));
  ui->R8->setText(QString::number(CP.Regs->at(8)));
  ui->R9->setText(QString::number(CP.Regs->at(9)));
  ui->R10->setText(QString::number(CP.Regs->at(10)));
  ui->R11->setText(QString::number(CP.Regs->at(11)));
  ui->R12->setText(QString::number(CP.Regs->at(12)));
  ui->R13->setText(QString::number(CP.Regs->at(13)));
  ui->R14->setText(QString::number(CP.Regs->at(14)));
  ui->R15->setText(QString::number(CP.Regs->at(15)));

  //show data memory
  ui->D0->setText(QString::number(CP.DataMemory->at(0)));
  ui->D1->setText(QString::number(CP.DataMemory->at(1)));
  ui->D2->setText(QString::number(CP.DataMemory->at(2)));
  ui->D3->setText(QString::number(CP.DataMemory->at(3)));
  ui->D4->setText(QString::number(CP.DataMemory->at(4)));
  ui->D5->setText(QString::number(CP.DataMemory->at(5)));
  ui->D6->setText(QString::number(CP.DataMemory->at(6)));
  ui->D7->setText(QString::number(CP.DataMemory->at(7)));
  ui->D8->setText(QString::number(CP.DataMemory->at(8)));
  ui->D9->setText(QString::number(CP.DataMemory->at(9)));
  ui->D10->setText(QString::number(CP.DataMemory->at(10)));
  ui->D11->setText(QString::number(CP.DataMemory->at(11)));
  ui->D12->setText(QString::number(CP.DataMemory->at(12)));
  ui->D13->setText(QString::number(CP.DataMemory->at(13)));
  ui->D14->setText(QString::number(CP.DataMemory->at(14)));
  ui->D15->setText(QString::number(CP.DataMemory->at(15)));
  ui->D16->setText(QString::number(CP.DataMemory->at(16)));
  ui->D17->setText(QString::number(CP.DataMemory->at(17)));
  ui->D18->setText(QString::number(CP.DataMemory->at(18)));
  ui->D19->setText(QString::number(CP.DataMemory->at(19)));
  ui->D20->setText(QString::number(CP.DataMemory->at(20)));
  ui->D21->setText(QString::number(CP.DataMemory->at(21)));
  ui->D22->setText(QString::number(CP.DataMemory->at(22)));
  ui->D23->setText(QString::number(CP.DataMemory->at(23)));
  ui->D24->setText(QString::number(CP.DataMemory->at(24)));
  ui->D25->setText(QString::number(CP.DataMemory->at(25)));
  ui->D26->setText(QString::number(CP.DataMemory->at(26)));
  ui->D27->setText(QString::number(CP.DataMemory->at(27)));
  ui->D28->setText(QString::number(CP.DataMemory->at(28)));
  ui->D29->setText(QString::number(CP.DataMemory->at(29)));
  ui->D30->setText(QString::number(CP.DataMemory->at(30)));
  ui->D31->setText(QString::number(CP.DataMemory->at(31)));



  if(!CP.DecodeStage.returnStack.empty())
  {
    ui->RS->setText(QString::number(CP.DecodeStage.returnStack.top()));
  }
  else{
      ui->RS->setText(QString::number(-1));
    }

  for(int i = 0; i < w; i++)
  {
      if(Labels[i].first->text() == "" && CP.FetchStage.pc - 1 > -1)
      {
        Labels[i].first->setText("Instruction " +QString::number(CP.FetchStage.pc - 1)+": IF -->" );
        Labels[i].second = CP.FetchStage.pc - 1;
        used[i] = 1;
      }
      else if(Labels[i].second == CP.DecodeStage.pc && used[i] == 1)
      {
        Labels[i].first->setText(Labels[i].first->text() + "DC -->");
        used[i] = 2;
      }
      else if(Labels[i].second == CP.ExecuteStage.pc && used[i] == 2)
      {
        Labels[i].first->setText(Labels[i].first->text() + "EX -->");
        used[i] = 3;
      }
      else if(Labels[i].second == CP.MemoryStage.pc && used[i] == 3)
      {
        Labels[i].first->setText(Labels[i].first->text() + "MEM-->");
        used[i] = 4;
      }
      else if(Labels[i].second == CP.WBStage.pc && used[i] == 4)
      {
        Labels[i].first->setText(Labels[i].first->text() + "WB");
        used[i] = 5;
      }
      else if(used[i] < 5 && used[i] > 0 && count[i]+used[i] < 5)
      {
        Labels[i].first->setText(Labels[i].first->text() + "## -->");
        count[i]++;
      }
    }
}

void MainWindow::on_pushButton_clicked()
{

    /*QString filename = QFileDialog::getOpenFileName(this, tr("Open File"),
    "",
    tr("Files (.)"));
    std::string utf8_text = filename.toUtf8().constData();*/

    CP.init("/Users/macbookpro/Desktop/Advanced_Pipelined_MIPS_Simulator-CS330/gui/Text.txt");
}
