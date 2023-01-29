%% Conexión al Puerto 
clear all; 
puerto = input("A qué puerto deseas conectarte? ", "s"); 
baud_rate = input("Baud rate: "); 
s = serialport(puerto, baud_rate); 
comenzar = input("Desea empezar a leer? ", "s");
samples = 1024;

% Vectores de Almacenamiento de datos del ADC
vector_de_datos = cell(1, 2); % Usamos por 3 porque haremos 3 lecturas
for ii=1:length(vector_de_datos)
    vector_de_datos{ii} = zeros(1, samples);
end

ith_entry = 1; 
% Lectura de los datos
while true
    vector_de_datos{1}(ith_entry) = str2double(readline(s));
    vector_de_datos{2}(ith_entry) = str2double(readline(s));
    % Transformación de datos a binario 
    arreglo_binario_1 = string(dec2bin(vector_de_datos{1}(ith_entry)));
    arreglo_binario_2 = string(dec2bin(vector_de_datos{2}(ith_entry)));
    % Envío de datos de regreso
    writeline(s, arreglo_binario_1);
    writeline(s, arreglo_binario_2);

    if ith_entry == 1024
        ith_entry = 0;
    end
end
