#ifndef MULTIPOINTCROSS_H
#define MULTIPOINTCROSS_H

#include <iostream>
#include <vector>
#include <algorithm>
#include "cross.h"


/**
 * Croisement multi-points. Un ensemble de pivots triés est nécessaire.
 * On vérifiera à l'exécution que les pivots sont présents et moins 
 * nombreux que le nombre d'items à croiser.
 * @author Ugo 
 */
template <typename T>
class MultiPointCross : public Cross<T> {
private:
  unsigned int _nbPivots;
public:
  
  /* * * * * * * *
   * CONSTRUCTOR *
   * * * * * * * */
  
/**
 * Constructeur nécessitant un pointeur sur unsigned int (ie un ensemble 
 * de pivots). Si le pointeur est non-nul, il contient au moins 1 pivot et
 * le croisement sera au minimum classique.
 * @param pivots : tableau de pivots
 * @param nbPivots : nombre de pivots dans le tableau
 * @author Ugo Rayer
 */
 MultiPointCross(unsigned int nbPivots): _nbPivots(nbPivots)
 {
 
 }
 
 
 /**
  * Constructeur par recopie
  * @param mpc : Un autre opérateur de croisement multi point
  * @author Johan Defaye
  */
 MultiPointCross(const MultiPointCross<T> & mpc): _nbPivots(mpc._nbPivots)
 {
 }
 
 
 /* * * * * *
  * GETTER  *
  * * * * * */
 
 unsigned int getNbPivots() const { return _nbPivots; }
 
 
 
 /* * * * * * * *
  * DESTRUCTOR  *
  * * * * * * * */
 
  
   /* * * * * *
   * METHODS *
   * * * * * */
  
  
/**
 * Croisement multipoint entre deux individus de type Individual<T>
 * Renvoie une erreur si :
 * - Parent null
 * - Pivot trop grand (TODO voir utilisation de modulo(p1.size())
 * - Parents de taille différentes
 * @param parent1 : parent1
 * @param parent2 : parent2
 * @param efant : Enfant résultant du croisement de parent1 et parent2
 * @author Ugo Rayer, Johan Defaye
 */
  void execute(const Individual<T> & parent1, const Individual<T> & parent2, Individual<T> & enfant) {
    
    if( _nbPivots > (parent1.size() - 2)) throw std::string("Erreur, trop de pivots (multiPointCross)");
        
    else if (parent1.size() != parent2.size()) throw std::string("Erreur, les individus parents n'ont pas la même taille (multiPointCross)");
    
    else if( parent1.size() <= 2 || parent2.size() <= 2) throw std::string("Parents de taille <= 2 (multiPointCross)");
    
    else{
      
      // Sélection aléatoires des pivots
      int lim = parent1.size() -2;
      unsigned indice[lim];
      for(int i=0; i < lim; ++i)
	  indice[i] = i+1;
      
      std::vector<int> _pivots;
      
      for(unsigned k = 0; k < _nbPivots; ++k){
	  int alea = rand()%lim;
	  _pivots.push_back(indice[alea]);
	  
	  indice[alea] = indice[lim-1];
	  --lim;	
      }
      
      std::sort(_pivots.begin(), _pivots.end());
      
      enfant.resize(parent1.size());
      unsigned j = 0; // indice du pivot courant
      bool b=true; // Vrai si l'individu fils récupère les données du parent1 et faux si il récupère les données du parent2
      for( int i = 0; i < (int)parent1.size(); ++i){
	
	if (b) enfant[i] = parent1[i];
	else  enfant[i] = parent2[i];
	      
	if( i == _pivots[j] ){
	    b = (!b);
	    if( j < (_nbPivots - 1) ) j++;
	}
      }
    } 
  }
  
};

#endif