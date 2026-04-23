# 🍷 Vinheria Agnello — Sistema de Monitoramento de Luminosidade

> Projeto desenvolvido como parte da disciplina de Sistemas Embarcados.  
> Utiliza Arduino Uno e sensor LDR para monitorar a luminosidade do ambiente de armazenamento de vinhos, acionando alertas visuais e sonoros em tempo real.

---

## Descrição do Projeto

O vinho é sensível à luz: a exposição excessiva degrada seus compostos orgânicos, comprometendo sabor e qualidade. Este sistema monitora continuamente a luminosidade da adega e responde de forma automática conforme o nível detectado pelo sensor LDR.

| Estado | Condição | Luminosidade (valor analógico) | LED | Buzzer |
|--------|----------|-------------------------------|-----|--------|
| ✅ Adequado | Ambiente escuro (ideal) | `< 880` | 🟢 Verde (pino 5) | Desligado |
| ⚠️ Alerta | Luminosidade moderada | `880 – 960` | 🟡 Amarelo (pino 6) | 500 Hz por 3 seg |
| 🚨 Crítico | Muita luz (risco ao vinho) | `> 960` | 🔴 Vermelho (pino 7) | 1000 Hz contínuo |

> Os valores analógicos variam de 0 a 1023 (resolução de 10 bits do Arduino). Quanto maior o valor, maior a luminosidade captada pelo LDR.

---

## 🔌 Circuito

![Circuito do projeto no Tinkercad](./circuito.png)

> Simulação montada no **Tinkercad**. O LDR lê a luminosidade e envia o sinal analógico à porta `A0` do Arduino, que processa e aciona os componentes conforme os limiares definidos no código.

---

## 🎥 Vídeo de Apresentação

[![Assista no YouTube](https://img.shields.io/badge/YouTube-Assistir%20Apresentação-red?style=for-the-badge&logo=youtube)
](https://youtu.be/E_VeabWIuwE?si=LpvlSQirIN8TYRqz)

---

## Componentes Utilizados

### Hardware

| Componente | Quantidade | Pino no Arduino |
|------------|------------|-----------------|
| Arduino Uno | 1 | — |
| Sensor LDR (fotoresistor) | 1 | A0 |
| Resistor 10 kΩ | 1 | Divisor de tensão com o LDR |
| LED Verde (5 mm) | 1 | D5 |
| LED Amarelo (5 mm) | 1 | D6 |
| LED Vermelho (5 mm) | 1 | D7 |
| Resistores 220 Ω | 3 | Um por LED |
| Buzzer Passivo 5V | 1 | D3 |
| Jumpers | ~14 | — |
| Protoboard | 1 | 400 ou 830 pontos |

### Software

- **Arduino IDE** 2.x — [download](https://www.arduino.cc/en/software)
- Nenhuma biblioteca externa necessária (usa apenas funções nativas do Arduino)

---

## Esquema de Ligação

```
                     Arduino Uno
                    ┌───────────┐
          LDR ──────┤ A0        │
                    │           │
      LED Verde ────┤ D5        │
    LED Amarelo ────┤ D6        │
   LED Vermelho ────┤ D7        │
        Buzzer ─────┤ D3        │
                    │           │
            5V ─────┤ 5V        │
           GND ─────┤ GND       │
                    └───────────┘
```

**Divisor de tensão — LDR:**
```
5V ──── [LDR] ──── A0 ──── [10kΩ] ──── GND
```

**LEDs (cada um):**
```
Pino Dx ──── [220Ω] ──── Anodo(+) ──── LED ──── Catodo(−) ──── GND
```

---

## 🚀 Como Reproduzir

### Opção A — Simulação Online (Tinkercad)

1. Acesse [tinkercad.com](https://www.tinkercad.com) e crie um novo circuito com **Arduino Uno**.
2. Monte os componentes conforme o esquema acima e a imagem do circuito.
3. Cole o conteúdo do arquivo `vinheria_agnello.ino` no editor de código.
4. Clique em **Iniciar Simulação** e varie a luz sobre o LDR para testar os três estados.

### Opção B — Hardware Físico

1. Monte o circuito na protoboard conforme o esquema acima.
2. Abra o **Arduino IDE** e instale o driver da placa se necessário.
3. Abra o arquivo `vinheria_agnello.ino`.
4. Selecione a porta correta em **Ferramentas → Porta**.
5. Clique em **Upload** (Ctrl+U).
6. Abra o **Monitor Serial** (9600 baud) para acompanhar os valores lidos pelo LDR em tempo real.
7. Varie a incidência de luz sobre o LDR (use lanterna ou cubra-o) para testar os três estados.

---

## Ajuste dos Limiares

No arquivo `.ino`, as variáveis abaixo controlam os limites de cada estado. Ajuste conforme a iluminação real do ambiente:

```cpp
int limiteOK     = 880;  // Abaixo → estado adequado (LED verde)
int limiteAlerta = 960;  // Entre limiteOK e limiteAlerta → alerta (LED amarelo)
                         // Acima de limiteAlerta → crítico (LED vermelho)
```

Use o Monitor Serial para verificar os valores brutos do LDR no seu ambiente e calibre conforme necessário.

---

## Estrutura do Repositório

```
vinheria-agnello/
├── vinheria_agnello.ino   ← Código-fonte principal
├── circuito.png         ← Imagem do circuito (Tinkercad)
└── README.md              ← Este arquivo
```

---

## Equipe

| Integrante | RM |
|------------|----|
| Guilherme Tome Nogueira| 570144 |
| Lucas de Andrade Astorini | 569119 |
| Sabrina Lopes da Silva | 571870 |
| Sofia Satomi Hagio | 569120 |

---

## Licença

Projeto acadêmico — uso educacional
