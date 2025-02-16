#include "visualize.h"
#include "uno_logic.h"
# include <graphics.h>
//��Ϸ�����ʼ�Ľ��棬���������ʼ��Ϸ��
Card_image card_images[MAX_CARDS];
Player_image player_images[MAX_PLAYERS];
Color_card_image color_card_images[5];

int initialize_startgame() 
{
    int choicetemp = 0;
    // ��ʼ��ͼ�δ��ڣ���СΪ800x600
    initgraph(800, 600);
    IMAGE backgroud_image;

    // ���ر���ͼƬ����ʼ��IMAGE����
    loadimage(&backgroud_image, _T("background2.jpg"));
    putimage(0, 0, &backgroud_image); // ��ʾ����ͼƬ
    // ��ȡ���ں�ͼƬ�Ĵ�С 
    /*int window_width = getwidth();
    int window_height = getheight();
    int image_width = getwidth();
    int image_height = getheight();*/

    // ����ͼƬ��λ�ã���ȷ��ͼƬ����
   /* int x = (window_width - image_width) / 2;
    int y = (window_height - image_height) / 2;*/
    int x;
    int y;

    // ���Ʊ���ͼƬ 
    setbkcolor(0); // ���ñ���ɫΪ��ɫ
    setfillstyle(SOLID_FILL, BLACK); // �������ɫΪ��ɫ


    // �ڴ�������ʾ"UNO Game"����
    settextcolor(WHITE); // �����ı���ɫΪ��ɫ������߶Աȶ�
    settextstyle(40, 0, _T("Consolas"));
    outtextxy(380, 250, _T("UNO"));

    // ����"��ʼ��Ϸ"��ť
    //ctangle(300, 300, 500, 350);
    outtextxy(330, 310, _T("��ʼ��Ϸ"));

    // �ȴ��û����"��ʼ��Ϸ"��ť
    MOUSEMSG msg;  // ���������Ϣ
    while (true)// ѭ���ȴ��û����
    {
        // ��ȡһ�������Ϣ
        msg = GetMouseMsg();

        // �ж��Ƿ��������
        if (msg.uMsg == WM_LBUTTONDOWN)
        {
            // �ж��Ƿ���"��ʼ��Ϸ"��ť��
            if (msg.x >= 300 && msg.x <= 500 && msg.y >= 300 && msg.y <= 350)
            {
                cleardevice(); // �������

                putimage(0,0,&backgroud_image); // ��ʾ����ͼƬ

                settextcolor(WHITE); // �����ı���ɫΪ��ɫ
                settextstyle(40, 0, _T("Consolas"));
                outtextxy(312, 50, _T("2 player"));
                outtextxy(312, 150, _T("3 player"));
                outtextxy(312, 250, _T("4 player"));
                outtextxy(312, 350, _T("5 player"));
                outtextxy(312, 450, _T("6 player"));
                outtextxy(312, 550, _T("7 player"));
                //�ж��û�ѡ���˼�����Ϸ
                while (true)
                {
                    // ��ȡһ�������Ϣ
                    msg = GetMouseMsg();

                    // �ж��Ƿ���"3 player_images"��ť��
                    if (msg.uMsg == WM_LBUTTONDOWN)
                    {
                        if (msg.x >= 312 && msg.x <= 450 && msg.y >= 50 && msg.y <= 100)
                        {
                            choicetemp = 2;
                            cleardevice();
                            return choicetemp;
                        }
                        else if (msg.x >= 312 && msg.x <= 450 && msg.y >= 150 && msg.y <= 200)
                        {
                            choicetemp = 3;
                            cleardevice();
                            return choicetemp;
                        }
                        else if (msg.x >= 312 && msg.x <= 450 && msg.y >= 250 && msg.y <= 300)
                        {
                            choicetemp = 4;
                            cleardevice();

                            return choicetemp;
                        }
                        else if (msg.x >= 312 && msg.x <= 450 && msg.y >= 350 && msg.y <= 400)
                        {
                            choicetemp = 5;
                            cleardevice();

                            return choicetemp;
                        }
                        else if (msg.x >= 312 && msg.x <= 450 && msg.y >= 450 && msg.y <= 500)
                        {
                            choicetemp = 6;
                            cleardevice();

                            return choicetemp;
                        }
                        else if (msg.x >= 312 && msg.x <= 450 && msg.y >= 550 && msg.y <= 600)
                        {
                            choicetemp = 7;
                            cleardevice();
                            return choicetemp;
                        }
                    }
                }
            }
        }
    }

    // ˢ��ͼ�δ���
    // ��ʾ����ͼƬ

    // ������׼����ʼ��Ϸ
    
}

//�������п���ͼƬ
void initialize_card_image()
{
    loadimage(&card_images[0].image_card, _T("red_0.png"));
    loadimage(&card_images[1].image_card, _T("red_0.png"));
   
    loadimage(&card_images[2].image_card, _T("red_1.png"));
    loadimage(&card_images[3].image_card, _T("red_1.png"));
   
    loadimage(&card_images[4].image_card, _T("red_2.png"));
    loadimage(&card_images[5].image_card, _T("red_2.png"));

    loadimage(&card_images[6].image_card, _T("red_3.png"));
    loadimage(&card_images[7].image_card, _T("red_3.png"));

    loadimage(&card_images[8].image_card, _T("red_4.png"));
    loadimage(&card_images[9].image_card, _T("red_4.png"));

    loadimage(&card_images[10].image_card, _T("red_5.png"));
    loadimage(&card_images[11].image_card, _T("red_5.png"));

    loadimage(&card_images[12].image_card, _T("red_6.png"));
    loadimage(&card_images[13].image_card, _T("red_6.png"));

    loadimage(&card_images[14].image_card, _T("red_7.png"));
    loadimage(&card_images[15].image_card, _T("red_7.png"));

    loadimage(&card_images[16].image_card, _T("red_8.png"));
    loadimage(&card_images[17].image_card, _T("red_8.png"));

    loadimage(&card_images[18].image_card, _T("red_9.png"));
    loadimage(&card_images[19].image_card, _T("red_9.png"));

    loadimage(&card_images[20].image_card, _T("green_0.png"));
    loadimage(&card_images[21].image_card, _T("green_0.png"));

    loadimage(&card_images[22].image_card, _T("green_1.png"));
    loadimage(&card_images[23].image_card, _T("green_1.png"));

    loadimage(&card_images[24].image_card, _T("green_2.png"));
    loadimage(&card_images[25].image_card, _T("green_2.png"));

    loadimage(&card_images[26].image_card, _T("green_3.png"));
    loadimage(&card_images[27].image_card, _T("green_3.png"));

    loadimage(&card_images[28].image_card, _T("green_4.png"));
    loadimage(&card_images[29].image_card, _T("green_4.png"));

    loadimage(&card_images[30].image_card, _T("green_5.png"));
    loadimage(&card_images[31].image_card, _T("green_5.png"));

    loadimage(&card_images[32].image_card, _T("green_6.png"));
    loadimage(&card_images[33].image_card, _T("green_6.png"));

    loadimage(&card_images[34].image_card, _T("green_7.png"));
    loadimage(&card_images[35].image_card, _T("green_7.png"));

    loadimage(&card_images[36].image_card, _T("green_8.png"));
    loadimage(&card_images[37].image_card, _T("green_8.png"));

    loadimage(&card_images[38].image_card, _T("green_9.png"));
    loadimage(&card_images[39].image_card, _T("green_9.png"));

    loadimage(&card_images[40].image_card, _T("blue_0.png"));
    loadimage(&card_images[41].image_card, _T("blue_0.png"));

    loadimage(&card_images[42].image_card, _T("blue_1.png"));
    loadimage(&card_images[43].image_card, _T("blue_1.png"));

    loadimage(&card_images[44].image_card, _T("blue_2.png"));
    loadimage(&card_images[45].image_card, _T("blue_2.png"));

    loadimage(&card_images[46].image_card, _T("blue_3.png"));
    loadimage(&card_images[47].image_card, _T("blue_3.png"));

    loadimage(&card_images[48].image_card, _T("blue_4.png"));
    loadimage(&card_images[49].image_card, _T("blue_4.png"));

    loadimage(&card_images[50].image_card, _T("blue_5.png"));
    loadimage(&card_images[51].image_card, _T("blue_5.png"));

    loadimage(&card_images[52].image_card, _T("blue_6.png"));
    loadimage(&card_images[53].image_card, _T("blue_6.png"));

    loadimage(&card_images[54].image_card, _T("blue_7.png"));
    loadimage(&card_images[55].image_card, _T("blue_7.png"));

    loadimage(&card_images[56].image_card, _T("blue_8.png"));
    loadimage(&card_images[57].image_card, _T("blue_8.png"));

    loadimage(&card_images[58].image_card, _T("blue_9.png"));
    loadimage(&card_images[59].image_card, _T("blue_9.png"));

    loadimage(&card_images[60].image_card, _T("yellow_0.png"));
    loadimage(&card_images[61].image_card, _T("yellow_0.png"));

    loadimage(&card_images[62].image_card, _T("yellow_1.png"));
    loadimage(&card_images[63].image_card, _T("yellow_1.png"));


    loadimage(&card_images[64].image_card, _T("yellow_2.png"));
    loadimage(&card_images[65].image_card, _T("yellow_2.png"));

    loadimage(&card_images[66].image_card, _T("yellow_3.png"));
    loadimage(&card_images[67].image_card, _T("yellow_3.png"));

    loadimage(&card_images[68].image_card, _T("yellow_4.png"));
    loadimage(&card_images[69].image_card, _T("yellow_4.png"));

    loadimage(&card_images[70].image_card, _T("yellow_5.png"));
    loadimage(&card_images[71].image_card, _T("yellow_5.png"));

    loadimage(&card_images[72].image_card, _T("yellow_6.png"));
    loadimage(&card_images[73].image_card, _T("yellow_6.png"));

    loadimage(&card_images[74].image_card, _T("yellow_7.png"));
    loadimage(&card_images[75].image_card, _T("yellow_7.png"));

    loadimage(&card_images[76].image_card, _T("yellow_8.png"));
    loadimage(&card_images[77].image_card, _T("yellow_8.png"));

    loadimage(&card_images[78].image_card, _T("yellow_9.png"));
    loadimage(&card_images[79].image_card, _T("yellow_9.png"));


    //���غ�ɫ�ļ��ܿ��ƣ���6�ţ�80-85��˳��ΪSKIP-REVERSE-PLUS2��ÿ�ֹ���������

    loadimage(&card_images[80].image_card, _T("red_skip.png"));
    loadimage(&card_images[81].image_card, _T("red_skip.png"));

    loadimage(&card_images[82].image_card, _T("red_reverse.png"));
    loadimage(&card_images[83].image_card, _T("red_reverse.png"));

    loadimage(&card_images[84].image_card, _T("red_+2.png"));
    loadimage(&card_images[85].image_card, _T("red_+2.png"));

    //������ɫ�ļ��ܿ��ƣ���6�ţ�86-91��˳��ΪSKIP-REVERSE-PLUS2��ÿ�ֹ���������

    loadimage(&card_images[86].image_card, _T("green_skip.png"));
    loadimage(&card_images[87].image_card, _T("green_skip.png"));

    loadimage(&card_images[88].image_card, _T("green_reverse.png"));
    loadimage(&card_images[89].image_card, _T("green_reverse.png"));

    loadimage(&card_images[90].image_card, _T("green_+2.png"));
    loadimage(&card_images[91].image_card, _T("green_+2.png"));

    //������ɫ�ļ��ܿ��ƣ���6�ţ�92-97��˳��ΪSKIP-REVERSE-PLUS2��ÿ�ֹ���������

    loadimage(&card_images[92].image_card, _T("blue_skip.png"));
    loadimage(&card_images[93].image_card, _T("blue_skip.png"));

    loadimage(&card_images[94].image_card, _T("blue_reverse.png"));
    loadimage(&card_images[95].image_card, _T("blue_reverse.png"));

    loadimage(&card_images[96].image_card, _T("blue_+2.png"));
    loadimage(&card_images[97].image_card, _T("blue_+2.png"));

    //���ػ�ɫ�ļ��ܿ��ƣ���6�ţ�98-103��˳��ΪSKIP-REVERSE-PLUS2��ÿ�ֹ���������

    loadimage(&card_images[98].image_card, _T("yellow_skip.png"));
    loadimage(&card_images[99].image_card, _T("yellow_skip.png"));

    loadimage(&card_images[100].image_card, _T("yellow_reverse.png"));
    loadimage(&card_images[101].image_card, _T("yellow_reverse.png"));

    loadimage(&card_images[102].image_card, _T("yellow_+2.png"));
    loadimage(&card_images[103].image_card, _T("yellow_+2.png"));

    //���غ�ɫ��WILD��WILD+4����8�ţ�104-108��˳��ΪWILD-WILD+4��ÿ�Ŷ�������

    loadimage(&card_images[104].image_card, _T("black_wildcard.png"));
    loadimage(&card_images[105].image_card, _T("black_wildcard.png"));
    loadimage(&card_images[106].image_card, _T("black_+4.png"));
    loadimage(&card_images[107].image_card, _T("black_+4.png"));
  
}

void initialize_player_image()
{
    //printf("%d\n", 113);
    loadimage(&player_images[0].image_player, _T("player0.jpg"));

    loadimage(&player_images[1].image_player, _T("player1.jpg"));

    loadimage(&player_images[2].image_player, _T("player2.jpg"));

    loadimage(&player_images[3].image_player, _T("player3.jpg"));

    loadimage(&player_images[4].image_player, _T("player4.jpg"));

    loadimage(&player_images[5].image_player, _T("player5.jpg"));

    loadimage(&player_images[6].image_player, _T("player6.jpg"));
}

void initialize_color_card_image() {
        loadimage(&color_card_images[0].image_color, _T("red.png")); 

        loadimage(&color_card_images[1].image_color, _T("green.png"));

        loadimage(&color_card_images[2].image_color, _T("blue.png"));

        loadimage(&color_card_images[3].image_color, _T("yellow.png"));

        loadimage(&color_card_images[4].image_color, _T("black.png"));
}

//����Ļ��ѡ��WIL�Ƶ���ɫ
int select_color_visualize(){
    initialize_color_card_image();
    
  /*  IMAGE backgroud_image_1;
    loadimage(&backgroud_image_1, _T("background2.jpg"));
    putimage(0, 0, &backgroud_image_1);*/

    int color_temp = 0;
    setbkcolor(BLACK);
    settextcolor(WHITE);
    settextstyle(20, 0, _T("Arial"));
    outtextxy(300, 200, _T("ѡ��ת�Ƶ���ɫ"));
    //����ɫ��ƬͼƬ��ʾ����
    for (int i = 0; i < 4; i++) {
        putimage(200 + i * 100, 400, &color_card_images[i].image_color);
    }
    //�ȴ��û�ѡ����ɫ������Ļ������λ�û�ȡ��ɫ���
    MOUSEMSG msg;  // ���������Ϣ
    while (true)// ѭ���ȴ��û����
    {
        // ��ȡһ�������Ϣ
        msg = GetMouseMsg();

        // �ж��Ƿ��������
        if (msg.uMsg == WM_LBUTTONDOWN)
        {
            // �ж��Ƿ���ĳһ����ɫ��Ƭ��
            for (int i = 0; i < 4; i++) {
                if (msg.x >= 100 + i * 100 && msg.x <= 100 + i * 100 + color_card_images[i].image_color.getwidth() 
                    && msg.y >= 200 && msg.y <= 200 + color_card_images[i].image_color.getheight() ) {
                    color_temp = i;
                    break; 
                }
            }
            break; // �˳�ѭ��
        }
    }
    //closegraph();
    return color_temp;
}

//����Ļ�ϻ�ȡҪ����Ŀ���
//int select_color_visualize()

//�����ſ�����ʾ����Ļ��

void show_hand_cards(Card** temp, bool* result, int count) {
    
   /* if (getwidth() != 0) {
        initgraph(800, 600);
    }*/
    //printf("%d\n", 85);
    IMAGE backgroud_image_1;

    loadimage(&backgroud_image_1, _T("background2.jpg"));

    putimage(0, 0, &backgroud_image_1);
   // printf("%d\n", 111);
    attention_grab_card();
    show_grab_card();
    draw_line_to_hold_thecards();
    //printf("%d\n", 221);
    if (count > 10) {
        for (int i = 0; i < 10; i++) {
           // printf("%d\n", 13141);
            put_card_screen(temp[i], result[i], 20 + 76 * i, 320);
            Sleep(100);
        }
        for (int i = 10; i < count; i++) {
            //printf("%d\n", 13141);
            put_card_screen(temp[i], result[i], 30 + 76 * (i -10), 450);
            Sleep(100);
        }
    } else if(count < 10) {
        for (int i = 0; i < count; i++) {
            //printf("%d\n", 13141);
            put_card_screen(temp[i], result[i], 30 + 76 * i, 320);
            Sleep(100);
        }
    }
    //printf("%d\n", 134);
    Sleep(500);    
}

void put_card_screen(Card* card, bool result, int x, int y) {
    if (result == false) {
        putimage(x, y, &card_images[card->card_id].image_card);

    }
    else {
        putimage(x, y-20, &card_images[card->card_id].image_card);
    }
    return;
}

//����Ļ��ѡ��Ҫ����Ŀ���,���ؿ��Ƶı��
int select_card_screen() {
    //printf("%d\n", 2233);
    //initgraph(800, 600);
    while (true) {
        //�ȴ��û����
        MOUSEMSG msg;  // ���������Ϣ
        while (true)// ѭ���ȴ��û����
        {
            // ��ȡһ�������Ϣ
            msg = GetMouseMsg();

            // �ж��Ƿ��������

            if (msg.uMsg == WM_LBUTTONDOWN)
            {
                // �ж��Ƿ���ĳһ����Ƭ��
                for (int i = 0; i < 10; i++) {
                    if (msg.x >= 30 + 76 * i && msg.x <= 30 + 76 * i + card_images[i].image_card.getwidth()
                        && msg.y >= 320 && msg.y <= 320 + card_images[i].image_card.getheight()) {
                        return i;
                    }
                }
                for (int i = 10; i < 20; i++) {
                    if (msg.x >= 30 + 76 * (i -10) && msg.x <= 30 + 76 * (i-10) + card_images[i].image_card.getwidth()
                        && msg.y >= 450 && msg.y <= 450 + card_images[i].image_card.getheight()) {
                        return i;
                    }
                }
                if (msg.x >= 300 && msg.x <= 300 + color_card_images[4].image_color.getwidth() && msg.y >= 100 && msg.y <= 100 + color_card_images[4].image_color.getheight()) {
                    return -1;
                }
                break; // �˳�ѭ��
            }
        }
    }
    return 0;
}

void show_last_card(Card* lastcard) {
    putimage(600, 100, &card_images[lastcard->card_id].image_card);
    //printf("%d\n", lastcard->card_id);

}

void show_grab_card(){
    /*if (color_card_images[4].image_color.getwidth() == 0){
        initialize_color_card_image();
    }*/
    //printf("%d\n", 123);
   
    //printf("%d\n", 124);
    putimage(300, 100, &color_card_images[4].image_color);
    //printf("%d\n", 125);
    /*rectangle(300, 230, 300 + color_card_images[4].image_color.getwidth(), 230 + 0.30*color_card_images[4].image_color.getheight());*/
    settextstyle(36, 0, _T("Arial"));
    outtextxy(300, 230, _T("ץ��"));
}

void attention_grab_card() {
    //printf("%d\n", 112);
    IMAGE attention;
    loadimage(&attention, _T("attention.jpg"));
    putimage(700,500, &attention);
}

void draw_line_to_hold_thecards() {
    setlinecolor(RGB(100,100,100));
    setfillcolor(RGB(100, 100, 100));
    fillrectangle(0,320 + card_images[0].image_card.getheight(), 800, 326 + card_images[0].image_card.getheight());
}
void show_player(int player_id,int x, int y){
    putimage(x,y,&player_images[player_id].image_player);
}

void show_players(int aiplayercount) {
    for (int i = 1; i < aiplayercount+1; i++) {
        show_player(i, 100 * i, 600);
    }
}