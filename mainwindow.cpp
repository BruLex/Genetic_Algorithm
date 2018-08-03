#include "mainwindow.h"
#include "ui_mainwindow.h"



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked(){
    global_iter++;
    ui->lineEdit->setText(std::to_string(global_iter).c_str());
    GenDev();
}
void MainWindow::on_pushButton_2_clicked(){
    global_iter+=10;
    ui->lineEdit->setText(std::to_string(global_iter).c_str());
    for(int i=0;i<10;i++)
        GenDev();
}

void MainWindow::sort(){
    for(int i = 0; i < CNT_GEN-1; i++){
        for(int j = 0; j < CNT_GEN-1; j++){
            if(genBuf[j].get_Fx() < genBuf[j+1].get_Fx()){
                Generic buf = genBuf[j];
                genBuf[j] = genBuf[j+1];
                genBuf[j+1] = buf;
            }
        }
    }
}

void MainWindow::GenDev(){
    srand(time(NULL));
    std::string outText;
    Generic bufer[CNT_GEN];
    char *buf = new char[100];
    static bool check = true;
    double sumProz = 0, sumFx = 0;
    int newPopul[CNT_GEN];
    if(check){
        count_normFx(CNT_GEN);
        sprintf(buf," N \t рядок \t значення \t fx \t\t fnorm\n");
        outText.append(buf);
        for(int i = 0; i < CNT_GEN; i++){
            sprintf(buf," %i \t", i + 1);
            outText.append(buf);
            for(int j = 0; j < GEN_SIZE; j++)outText.append(std::to_string(generic[i].get_individ_for_pos(j)));
            sprintf(buf,"\t %i \t %6.3f \t\t %6.3f \n", generic[i].get_x(), generic[i].get_Fx(),generic[i].get_normFx());
            outText.append(buf);
        }
        check = false;
    }
    for(int i = 0; i < CNT_GEN; i++) genBuf[i].copyGen(generic[i]);
    sort();
    count_normFx(CNT_GEN/2);
    sprintf(buf,"\n\n N \t рядок \t значення \t Критерiй якостi \t %спiввiдн.\n");
    outText.append(buf);
    for(int i = 0; i < CNT_GEN / 2; i++){
        sprintf(buf," %i \t", i + 1);
        outText.append(buf);
        for(int j = 0; j < GEN_SIZE; j++)outText.append(std::to_string(genBuf[i].get_individ_for_pos(j)));
        sprintf(buf,"\t %i \t %6.3f \t\t %6.3f \n", genBuf[i].get_x(), genBuf[i].get_Fx(),genBuf[i].get_normFx());
        outText.append(buf);
    }
    for(int k=0;k<CNT_GEN/2;k++) sumProz += genBuf[k].get_normFx();
    for(int k=0;k<CNT_GEN/2;k++) sumFx += genBuf[k].get_Fx();
    sprintf(buf,"\t Разом \t  \t %6.3f \t\t\t %6.3f\n",sumFx,sumProz*100);
    outText.append(buf);
    for(int i = 0; i < CNT_GEN / 2; i++) generic[i].copyGen(genBuf[i]);
    for(int i = 0; i < CNT_GEN / 2; i++) generic[i+CNT_GEN / 2].copyGen(genBuf[i]);
    sprintf(buf,"Нове поколiння: ");
    outText.append(buf);
    count_normFx(CNT_GEN);
    for(int i = 0; i<CNT_GEN; i++){
        for(int i = 0; i<CNT_GEN; i++){
            double point = rand() % 1001 /1000.0f;
            double crnt = generic[0].get_normFx();
            for(int k = 0; k < CNT_GEN-1;k++){
                if(point <= crnt) {
                    newPopul[i]=k; break;
                }
                crnt+=generic[k+1].get_normFx();
            }
        }
        outText.append(std::to_string(newPopul[i]+1)).append(" ");
    }
    outText.append("\n");
    for(int i = 0; i < CNT_GEN; i++) bufer[i].copyGen(generic[i]);
    for(int i = 0; i < CNT_GEN; i++) generic[i].copyGen(bufer[newPopul[i]]);

    for(int i = 0; i < CNT_GEN; i += 2){
        double selection = rand() % 101 / 100.0f;
        if(selection < GEN_SELECTION){
            int pos = rand() % 8;
            int posto = rand() % 8;
            if(pos > posto){
                int lol = pos;
                pos = posto;
                posto=lol;
            }
            int newX[2] = {0,0};
            bool individ[GEN_SIZE][3];
            for(int k = pos; k < posto; k++){
                individ[k][0] = generic[i].get_individ_for_pos(k);
                individ[k][1] = generic[i].get_individ_for_pos(k);
                individ[k][2] = generic[i+1].get_individ_for_pos(k);
            }
            for(int k = pos; k < posto; k++){
                double mutation = rand() % 101 / 100.0f;
                individ[k][1] = individ[k][2];
                if(mutation < GEN_MUTATION) individ[k][1] = !individ[k][1];
                mutation = rand() % 101 / 100.0f;
                individ[k][2] = individ[k][0];
                if(mutation < GEN_MUTATION) individ[k][2] = !individ[k][2];
            }
            for(int k = 0, binary = 128; k < CNT_GEN; k++, binary /= 2){
                if(individ[k][1]) newX[0] += binary;
                if(individ[k][2]) newX[1] += binary;
            }
            generic[i].set_x(newX[0]);
            generic[i+1].set_x(newX[1]);
        }
    }
    count_normFx(CNT_GEN);
    sprintf(buf," N \t рядок \t значення \t fx \t\t fnorm\n");
    outText.append(buf);
    for(int i = 0; i < CNT_GEN; i++){
        sprintf(buf," %i \t", i + 1);
        outText.append(buf);
        for(int j = 0; j < GEN_SIZE; j++)outText.append(std::to_string(generic[i].get_individ_for_pos(j)));
        sprintf(buf,"\t %i \t %6.3f \t %6.3f \n", generic[i].get_x(), generic[i].get_Fx(),generic[i].get_normFx());
        outText.append(buf);
    }
    delete [] buf;
    ui->textEdit->append(outText.c_str());
}



void MainWindow::count_normFx(int gran){
    double sumFx = 0;
    for(int i = 0; i < gran; i++){
        sumFx += generic[i].get_Fx();
    }
    for(int i = 0; i < gran; i++){
        generic[i].set_normFx(generic[i].get_Fx() / sumFx);
    }
}

