./l15e1 < ./lista_15_input.output/entrada_01.txt > ./lista_15_input.output/vitor_01.txt
./l15e1 < ./lista_15_input.output/entrada_02.txt > ./lista_15_input.output/vitor_02.txt
./l15e1 < ./lista_15_input.output/entrada_03.txt > ./lista_15_input.output/vitor_03.txt
./l15e1 < ./lista_15_input.output/entrada_04.txt > ./lista_15_input.output/vitor_04.txt
./l15e1 < ./lista_15_input.output/entrada_05.txt > ./lista_15_input.output/vitor_05.txt

diff ./lista_15_input.output/saida_01.txt ./lista_15_input.output/vitor_01.txt
diff ./lista_15_input.output/saida_02.txt ./lista_15_input.output/vitor_02.txt
diff ./lista_15_input.output/saida_03.txt ./lista_15_input.output/vitor_03.txt
diff ./lista_15_input.output/saida_04.txt ./lista_15_input.output/vitor_04.txt
diff ./lista_15_input.output/saida_05.txt ./lista_15_input.output/vitor_05.txt