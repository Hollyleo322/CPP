#version 330 core
out vec4 FragColor;

in float texCoord;  // Текстурная координата вдоль линии (0-1)

uniform vec4 u_lineColor = vec4(1.0, 1.0, 1.0, 1.0); // Цвет линии
uniform bool u_isDotted;
uniform float dashSize = 0.142;  // Длина штриха (в нормализованных единицах линии)
uniform float gapSize = 0.142;  // Длина промежутка (в нормализованных единицах линии)
uniform float softness = 0.05;     // Плавность переходов (0.0 - резкий, больше - мягкий)

float proceduralDash(float coord) {
  
    // Длина одного паттерна
    float patternLength = dashSize + gapSize;
    // Позиция внутри паттерна
    float patternPos = mod(coord, patternLength);
    
    // Создаём плавный переход для штриха
    float dashEdge = dashSize - softness;
    // float alpha = smoothstep(0.0, softness, patternPos) * (1.0 - smoothstep(dashEdge, dashSize, patternPos));
    float alpha = 1.0;
    if(patternPos > dashSize) {
        alpha = 0.0;
    }
    return alpha;  // 1.0 - штрих, 0.0 - промежуток
}

void main() {
    // Вычисляем значение "текстуры" для текущей координаты
    float dashValue = u_isDotted ? proceduralDash(texCoord) : 1.0;
    
    // Если значение близко к 0, пропускаем фрагмент
    if (dashValue < 0.01) {
        discard;
    } else {
        FragColor = vec4(u_lineColor.rgb, u_lineColor.a * dashValue);
    }
}