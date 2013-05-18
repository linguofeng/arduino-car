#define STOP   1 // 停止状态
#define RUNING 0 // 正在运行状态

const int PINS[] = {5, 6, 10, 11};          // 马达控制接口
const int H[] = {HIGH, LOW, LOW, HIGH};     // 左
const int J[] = {LOW, HIGH, LOW, HIGH};     // 下
const int K[] = {HIGH, LOW, HIGH, LOW};     // 上
const int L[] = {LOW, HIGH, HIGH, LOW};     // 右

bool status = STOP;
char lastCommand = ' ';

void setup() {
    Serial.begin(9600);

    for (int i = 0; i < 4; ++i) {
        pinMode(PINS[i], OUTPUT);
    }
}

void loop() {
    while (Serial.available()) {
        char command = Serial.read();

        switch (command) {
            case 'H':
                if (lastCommand == command) break;
                pause();
                setMode(H);
                break;
            case 'J':
                if (lastCommand == command) break;
                pause();
                setMode(J);
                break;
            case 'K':
                if (lastCommand == command) break;
                pause();
                setMode(K);
                break;
            case 'L':
                if (lastCommand == command) break;
                pause();
                setMode(L);
                break;
            case 'X':
                stop();
                break;
            default:
                stop();
                Serial.println("COMMAND ERROR");
                break;
        }

        lastCommand = command;
    }
}

void pause() {
    if (status) return;

    for (int i = 0; i < 4; ++i) {
        digitalWrite(PINS[i], LOW); // 全部停止,LOW表示慢速停止,HIGH表示快速停止
    }

    delay(500);
}

void stop() {
    pause();

    status = STOP;
}

void setMode(const int *modes) {
    for (int i = 0; i < 4; ++i) {
        digitalWrite(PINS[i], modes[i]);
    }

    status = RUNING;
}
