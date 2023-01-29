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

% Lectura de los datos
for ith_entry = 1:samples
    vector_de_datos{1}(ith_entry) = str2double(readline(s));
    vector_de_datos{2}(ith_entry) = str2double(readline(s));
end

% Transformación de datos a binario 
arreglo_binario_1 = string(dec2bin(vector_de_datos{1}(1:end)));
arreglo_binario_2 = string(dec2bin(vector_de_datos{2}(1:end)));

% Envío de datos de regreso
for jj = 1: length(arreglo_binario_1)
    writeline(s, arreglo_binario_1(jj));
    writeline(s, arreglo_binario_2(jj));
end
