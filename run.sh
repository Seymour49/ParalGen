#!/bin/bash
#export LC_NUMERIC="en_US.UTF-8"

EXE="./build/paralGen"
JSONFILE="$1"
JSONSCHEMA="json/schema.json"
CMDFILE="json/cmd.txt"
#nbDecimalFloat=4

# Si le schema json valide le fichier json passé en paramètre
$(json validate --schema-file=$JSONSCHEMA --document-file=$JSONFILE) &&
{
	# On récupère le nombre d'exécution que l'on devra executer
	nbExec=$(jshon -e tabAlgoGen -l < $JSONFILE)
	declare -a tableauExecution
	
	# Récupération des données relatives à la migration des individus entre les différentes exécutions de l'algorithme génétique
	nbMig=$(jshon -e migration -e nbCandidatMigration < $JSONFILE)
	stepMig=$(jshon -e migration -e stepMigration < $JSONFILE)
	
	# Récupération du nom général des executions
	nom=$(jshon -e name < $JSONFILE)
	nom=${nom:1:$((${#nom}-2))}
	
	# Initialisation des lignes d'exécutions
	for ((i=0 ; $i<$nbExec ; i++))
	do 
		# ajout des options courtes aux lignes d'exécutions
		
		identifiant=$(jshon -e tabAlgoGen -e $i -e id < $JSONFILE)
		
		taillePop=$(jshon -e tabAlgoGen -e $i -e initParam -e taillePop < $JSONFILE)
		nbGeneration=$(jshon -e tabAlgoGen -e $i -e initParam -e nbGeneration < $JSONFILE)
		jeuDeDonnee=$(jshon -e tabAlgoGen -e $i -e initParam -e dataFile < $JSONFILE)
		jeuDeDonnee=${jeuDeDonnee:1:$((${#jeuDeDonnee}-2))}
		probaCroisement=$(jshon -e tabAlgoGen -e $i -e initParam -e probaCroisement < $JSONFILE)
		#probaCroisement= printf '%.*f\n' $nbDecimalFloat $probaCroisement2
		probaMutation=$(jshon -e tabAlgoGen -e $i -e initParam -e probaMutation < $JSONFILE)
		
		nbProba=$(jshon -e tabAlgoGen -e $i -e initParam -e tabProbaMigration -l < $JSONFILE)
		if  [ $nbExec -ne $nbProba ]
		then 
			echo "Erreur, attribut tabProbaMigration incorrecte !"
		else
			proba=$(jshon -e tabAlgoGen -e $i -e initParam -e tabProbaMigration -e 0 < $JSONFILE)
			for ((j=1 ; $j<nbExec ; j++))
			do
				newProba=$(jshon -e tabAlgoGen -e $i -e initParam -e tabProbaMigration -e $j < $JSONFILE)
				proba="$proba:$newProba"
			done
			
		fi
		
		# ajout des options longues aux lignes d'exécutions
		
		typeIndividu=$(jshon -e tabAlgoGen -e $i -e initParam -e classUsed -e typeInd -e class < $JSONFILE)
		typeIndividu=${typeIndividu:1:$((${#typeIndividu}-2))}
		typePrimitif=$(jshon -e tabAlgoGen -e $i -e initParam -e classUsed -e typeInd -e typePrimitif < $JSONFILE)
		typePrimitif=${typePrimitif:1:$((${#typePrimitif}-2))}
		
		
		# Initialisation de la population
		
		populate=$(jshon -e tabAlgoGen -e $i -e initParam -e classUsed -e populate -e class < $JSONFILE)
		populate=${populate:1:$((${#populate}-2))}
		nbArg=$(jshon -e tabAlgoGen -e $i -e initParam -e classUsed -e populate -l < $JSONFILE)
		if [ $nbArg -eq 2 ]
		then
			paramPopulate=$(jshon -e tabAlgoGen -e $i -e initParam -e classUsed -e populate -e param < $JSONFILE)
		else
			paramPopulate=""
		fi
		
		
		# Evaluation d'un individu
		
		evaluation=$(jshon -e tabAlgoGen -e $i -e initParam -e classUsed -e evaluate -e class < $JSONFILE)
		evaluation=${evaluation:1:$((${#evaluation}-2))}
		nbArg=$(jshon -e tabAlgoGen -e $i -e initParam -e classUsed -e evaluate -l < $JSONFILE)
		if [ $nbArg -eq 2 ]
		then
			paramEvaluation=$(jshon -e tabAlgoGen -e $i -e initParam -e classUsed -e evaluate -e param < $JSONFILE)
		else
			paramEvaluation=""
		fi
		
		
		# Croisement de deux individus
		
		croisement=$(jshon -e tabAlgoGen -e $i -e initParam -e classUsed -e crossover -e class < $JSONFILE)
		croisement=${croisement:1:$((${#croisement}-2))}
		nbArg=$(jshon -e tabAlgoGen -e $i -e initParam -e classUsed -e crossover -l < $JSONFILE)
		if [ $nbArg -eq 2 ]
		then
			paramCroisement=$(jshon -e tabAlgoGen -e $i -e initParam -e classUsed -e crossover -e param < $JSONFILE)
		else
			paramCroisement=""
		fi
		
		
		# Mutation d'un individu
		
		mutation=$(jshon -e tabAlgoGen -e $i -e initParam -e classUsed -e mutator -e class < $JSONFILE)
		mutation=${mutation:1:$((${#mutation}-2))}
		nbArg=$(jshon -e tabAlgoGen -e $i -e initParam -e classUsed -e mutator -l < $JSONFILE)
		if [ $nbArg -eq 2 ]
		then
			paramMutation=$(jshon -e tabAlgoGen -e $i -e initParam -e classUsed -e mutator -e param < $JSONFILE)
		else
			paramMutation=""
		fi
		
		
		# Sélection d'un individu
		
		selection=$(jshon -e tabAlgoGen -e $i -e initParam -e classUsed -e selectPolicy -e class < $JSONFILE)
		selection=${selection:1:$((${#selection}-2))}
		nbArg=$(jshon -e tabAlgoGen -e $i -e initParam -e classUsed -e selectPolicy -l < $JSONFILE)
		if [ $nbArg -eq 2 ]
		then
			paramSelection=$(jshon -e tabAlgoGen -e $i -e initParam -e classUsed -e selectPolicy -e param < $JSONFILE)
		else
			paramSelection=""
		fi
		
		
		# Ajout/Suppression d'un individu
		
		inDel=$(jshon -e tabAlgoGen -e $i -e initParam -e classUsed -e indelPolicy -e class < $JSONFILE)
		inDel=${inDel:1:$((${#inDel}-2))}
		nbArg=$(jshon -e tabAlgoGen -e $i -e initParam -e classUsed -e indelPolicy -l < $JSONFILE)
		if [ $nbArg -eq 2 ]
		then
			paramInDel=$(jshon -e tabAlgoGen -e $i -e initParam -e classUsed -e indelPolicy -e param < $JSONFILE)
		else
			paramInDel=""
		fi
		
		
			
		# Ecriture des ligne d'exécution avec les options courtes et les options longues
		
		tableauExecution[$i]="$EXE -k $nbMig -s $stepMig -i $identifiant -u $nom -n $taillePop -g $nbGeneration -d $jeuDeDonnee -c $probaCroisement -m $probaMutation -l $nbExec -t $proba --$typeIndividu --$typePrimitif --$populate $paramPopulate --$evaluation $paramEvaluation --$croisement $paramCroisement --$mutation $paramMutation --$selection $paramSelection --$inDel $paramInDel"
		mkdir $nom$identifiant
		
	done
	
	
	echo ${tableauExecution[0]} > $CMDFILE
	
	for ((j=1 ; j<$nbExec ; j++))
	do
		echo ${tableauExecution[$j]} >> $CMDFILE
	done
	
	
	# Lancement des exécutions parallels
	parallel --no-notice :::: $CMDFILE 


}
