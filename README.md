# AEDA.mmxvi-mmxvii
AEDA repositorium abertum est


Tema   8   –   Boleias   Partilhadas   (Parte   1) 


Uma empresa deseja explorar o conceito de carpooling e ridesharing  , e pretende criar um sistema para a                                  gestão de uma rede social de partilha de boleias. Poderá haver dois tipos de utilizadores: os registados no                               sistema e aqueles que utilizam o sistema ocasionalmente. Entre os utilizadores, também haverá aqueles que                               desejam disponibilizar as suas viaturas, e aqueles que não têm viaturas para partilhar, mas apenas partilham
as viagens. 

Quando um utilizador disponibiliza o seu veículo no sistema, deverá indicar o número de lugares disponíveis, e o                           itinerário que realiza como uma lista de pontos de passagem, sendo o primeiro ponto o endereço de origem da                               viagem e o último ponto o endereço de destino. Utilizadores que possam ter interesse em partilhar a viagem toda                           ou trechos das viagens, podem candidatar-se aos lugares disponíveis. É possível que fiquem vagos lugares no                               decorrer da viagem, podendo estar disponíveis a quem desejar realizar o trecho ou parte do trecho                                 remanescente. 

Sendo construído em torno do conceito de redes socais, o sistema também privilegia a formação de grupos de                                 partilha de viagem entre pessoas próximas entre si; os utilizadores, ao se registarem no sistema, podem                                 associar-se como “buddy” de outros utilizadores – desta forma é possível criar uma rede de relações diretas e                             indiretas entre utilizadores. O serviço de partilha é mantido pelos próprios utilizadores. Os utilizadores que têm                   
viatura própria e a partilham no sistema, pagam apenas uma taxa de manutenção; os utilizadores registados sem                             viatura, pagam uma mensalidade fixa de manutenção mais o que realizarem em número de viagens, durante o                                   mês; os utilizadores que utilizam o serviço esporadicamente devem efetuar pagamento em cada viagem.

O sistema, para além de guardar as relações de amizade (“buddies”) dos utilizadores registados, também                               mantém o histórico das viagens realizadas, incluindo o nome do utilizador proprietário da viatura, os pontos de                         origem e destino da viagem, a hora de início e de fim, assim como o dia emque foi realizada. Adicionalmente                               poderá considerar veículos diferentes, nomeadamente veículos ligeiros (5 lugares), vans (de 7 lugares), entre                             outras opções. 


--------------------- Parte II ----------------------


● A empresa decidiu disponibilizar aos clientes informação sobre as viaturas disponíveis; alguns clientes
poderão condicionar suas opções de parlha
de viagem em função do po
de viatura. Assim, a empresa
guarda numa Árvore Binária de Pesquisa informação de todas as viaturas disponíveis no sistema,
devendo ser possível idenficar
o seu dono (quem disponibiliza a viatura). As viaturas são ordenadas
alfabecamente
pelo nome do fabricante (Ford, Renault, etc) e pelo nome do modelo. Para viaturas da
mesma marca e modelo, estas são ordenadas pelo seu ano, sendo exibidas as mais recentes em
primeiro. Deve ser permido
inserir novas viaturas, eliminar viaturas existentes ou alterar o dono da
viatura. O cliente também pode pesquisar viaturas.

● Para melhor gerir a procura por determinados desnos
de várias pessoas, acima da capacidade das
viaturas, a empresa decide priorizar aquelas com relação de amizade mais próxima do motorista, e
depois aquelas com distância mais próxima do inerário
original a ser executado pelo motorista. Os
candidatos à parlha
da viagem são então ordenados numa Fila de Prioridade, a fim de preencher as
vagas disponíveis nas viaturas.

● Para efeitos de promoção do sistema de parlhas,
a empresa decide manter numa Tabela de Dispersão
os membros inavos,
ou seja, aqueles que não ulizam
o sistema há mais de um determinado período
de tempo. Sempre que um cliente inavo
realiza uma nova viagem, ele passa novamente a avo.
As
moradas são atualizadas, em campanhas promocionais, de tempos em tempos, de forma a ter esta
informação sempre válida no sistema, para os clientes inavos.

