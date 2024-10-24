#include <windows.h>
#include <stdio.h>
#include <math.h>

// Определяем структуру точки
typedef struct {
    int index;      // Номер точки
    int isGood;     // Удовлетворяет ли точка условию
    float x;        // Координата X
    float y;        // Координата Y
    float l;        // Параметр L
} point;


int isPointInArea(double i, double j) {
    if ((i + j + 10 <= 0) && (i + j + 20 >= 0)) {
        return 1;
    }
    return 0;
}

double _min_(double a, double b) {
    if(a > b){
        return b;
    }
    return a;
}

double _max_(double a, double b) {
    if(a > b){
        return a;
    }
    return b;
}

int mod(int a, int b) {
    if(a >= 0){
        return a % b;
    }
    return a % b + b;
}

int sign(double a) {
    if(a >= 0){
        return 1;
    }
    return -1;
}

// Глобальная переменная для хранения массива точек
point points_[51];
int n = 4;

void point_gen() {
    double i = -30, j = -4, l = 12;
    int k = 0;
    static int max_k = 51;


    while (k < max_k) {
        points_[k].index = k;
        points_[k].x = i;
        points_[k].y = j;
        points_[k].l = l;
        points_[k].isGood = isPointInArea(i, j);

        if (k == max_k) {
            break;
        }

        double iOld = i, jOld = j;
        i = fabs(iOld - l) + _min_(mod(jOld, 10), mod(l + k, 10)) - 20;       
        j = mod(_max_(k - iOld, _min_(jOld, _max_(iOld - l, jOld - l))), 30);
        l = mod(pow(l, 2), 20) - mod(_max_(iOld, jOld), k + 1);
        k += 1;
    }
}

// Функция отрисовки окна
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_PAINT: {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Настраиваем координатную систему
            SetMapMode(hdc, MM_ISOTROPIC);
            SetWindowExtEx(hdc, 400, 400, NULL);
            SetViewportExtEx(hdc, 500 * n, -500 * n, NULL);  // Отражаем ось Y
            SetViewportOrgEx(hdc, 200 * n, 180 * n, NULL);   // Центр координат в центре окна

            // Отрисовка осей координат
            MoveToEx(hdc, -250 * n, 0, NULL);
            LineTo(hdc, 250 * n, 0);  // Ось X
            MoveToEx(hdc, 0, -250 * n, NULL);
            LineTo(hdc, 0, 250 * n);  // Ось Y
            // Отрисовка прямых
            MoveToEx(hdc, -260 * n, 250 * n, NULL);
            LineTo(hdc, 250 * n, -260 * n); // x + y + 10 = 0
            MoveToEx(hdc, -270 * n, 250 * n, NULL);
            LineTo(hdc, 250 * n, -270 * n); // x + y + 20 = 0

            // Отрисовка точек из массива points_
            float old_x = 0, old_y = 0;
            char str[3];

            for (int i = 0; i < 51; i++) {
                int x = (int)points_[i].x * n;  // Умножаем на 10 для масштабирования
                int y = (int)points_[i].y * n;  // Умножаем на 10 для масштабирования
                int color = mod(5 * i, 256);

                sprintf(str, "%d", i);
                TextOut(hdc, x+2, y+5, str, 2); // Пишем номер точки

                SelectObject(hdc, GetStockObject(DC_PEN));
                if (points_[i].isGood) {
                    // Если точка удовлетворяет условию, рисуем её зелёным
                    SetDCPenColor(hdc, RGB(0, 255, 0));
                } else {
                    // Иначе - красным
                    SetDCPenColor(hdc, RGB(color, 0, 0));
                }
                if (i == 50 || i == 0){
                    SetDCPenColor(hdc, RGB(255, 0, 255));
                }
                // Рисуем точку
                Ellipse(hdc, x-1, y-1, x+1, y+1);  // Рисуем маленький круг
                // Рисуем путь
                if (i != 0) {
                    SetDCPenColor(hdc, RGB(100, color, 100));
                    MoveToEx(hdc, old_x, old_y, NULL);
                    LineTo(hdc, x, y);
                }
                old_x = x; old_y = y;
            }

            EndPaint(hwnd, &ps);
        } break;

        case WM_DESTROY:
            PostQuitMessage(0);
            return 0;

        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    // Генерируем точки
    point_gen();

    // Описание окна
    const char CLASS_NAME[] = "Sample Window Class";
    
    WNDCLASS wc = { };
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    
    RegisterClass(&wc);

    // Создание окна
    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "Point Plotter",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, 500 * n, 500 * n,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);

    // Главный цикл сообщений
    MSG msg = { };
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}
