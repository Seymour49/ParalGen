#ifndef MULTIPOINTCROSS_H
#define MULTIPOINTCROSS_H

#include <iostream>
#include <vector>
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
  unsigned int * _pivots;
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
 MultiPointCross(const unsigned int * pivots, unsigned int nbPivots): _nbPivots(nbPivots)
 {
   _pivots = new unsigned int[_nbPivots];
   for (unsigned int i = 0; i < _nbPivots; ++i) _pivots[i] = pivots[i];
 }
 
/**
 * Constructeur nécessitant un vecteurd de unsigned int (ie un ensemble 
 * de pivots).
 * @param v : vecteur contenant des pivots
 * @author Johan Defaye
 */
 MultiPointCross(const std::vector<unsigned int> & v): _nbPivots(v.size())
 {
   _pivots = new unsigned int[_nbPivots];
   for (unsigned int i = 0; i < _nbPivots; ++i) _pivots[i] = v[i];
 }
 
 
 /**
  * Constructeur par recopie
  * @param mpc : Un autre opérateur de croisement multi point
  * @author Johan Defaye
  */
 MultiPointCross(const MultiPointCross<T> & mpc): _nbPivots(mpc.getNbPivots())
 {
   _pivots = new unsigned int[_nbPivots];
   for (unsigned int i = 0; i < _nbPivots; ++i) _pivots[i] = mpc.getPivots()[i];
 }
 
 
 /* * * * * *
  * GETTER  *
  * * * * * */
 
 unsigned int getNbPivots() const { return _nbPivots; }
 
 unsigned int * getPivots() const { return _pivots; }
 
 
 /* * * * * * * *
  * DESTRUCTOR  *
  * * * * * * * */
 
 
/**
 * Redéfinition du destructeur virtuel
 */
  ~MultiPointCross()
  {
    delete [] _pivots;
  }
  
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
    
    if( _pivots == NULL ) throw std::string("Erreur, aucun indices de pivots n'ont été définis");
    
    else if( _nbPivots > parent1.size() ) throw std::string("Erreur, trop de pivots");
    
    else if( _pivots[0] == 0 || _pivots[_nbPivots-1] > (parent1.size() -2) ) throw std::string("Erreur, pivots trop grand et/ou trop petit");
    
    else if (parent1.size() != parent2.size()) throw std::string("Erreur, les individus parents n'ont pas la même taille");
    
    else{
      enfant.resize(parent1.size());
      unsigned j = 0; // indice du pivot courant
      bool b=true; // Vrai si l'individu fils récupère les données du parent1 et faux si il récupère les données du parent2
      for(unsigned int i = 0; i < parent1.size(); ++i){
	
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