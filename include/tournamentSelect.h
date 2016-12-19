#ifndef TOURNAMENTSELECT_H
#define TOURNAMENTSELECT_H

#include "selectPolicy.h"

/**
 * Cette classe représente le DP Strategy appliqué à la politique de sélection
 * des parents au cours d'un algorithme génétique.
 * Un nombre P de participants au tournoi est nécessaire. 
 * Les P candidats sont sélectionnés aléatoirement et les parents choisis
 * sont les meilleurs représentants parmi ces candidats au regard de leur
 * score
 * @param int NbParticipants
 * @author Ugo Rayer
 */

template <typename T>
class TournamentSelect : public SelectPolicy<T> {
  
private:
    unsigned int _nbP;
  
public:
  
    /* * * * * * * *
     * CONSTRUCTOR *
     * * * * * * * */
    
    /**
     * Constructeur unique nécessitant un nombre de participants au tournoi.
     * @param P : nombre de participants
     * @author Ugo Rayer
     */
    TournamentSelect(int P): _nbP(P)
    {}
    
    
    /**
     * Constructeur par recopie
     * @param t : une autre politique de sélection des parents pour un croisement entre individus
     * @author Johan Defaye
     */
    TournamentSelect(const TournamentSelect<T> & t): _nbP(t.getNbParticipant())
    {}
    
    
    unsigned int getNbParticipant() const { return _nbP;}
    
    void setNbParticipant(unsigned int nbP) { _nbP = nbP; }
    
    
    /* * * * * *
     * METHODS *
     * * * * * */
    
    /**
     * Sélection aléatoire de _nbp participants. Extraction des 2 meilleurs.
     * @param pop : population
     * @return Paire d'entier correspondant aux indices des parents sélectionnés dans la population
     * @author Ugo Rayer
     */
      std::pair<int,int> execute(const std::vector<Individual<T> *> & pop) const
      {
	if (_nbP < 2) throw std::string("Erreur, impossible d'exécuter une sélection par tournoi avec un nombre de participant inférieur à 2");
	else if (_nbP > pop.size()) throw std::string("Erreur, impossible d'exécuter une sélection par tournoi avec un nombre de participant supérieur à la taille de la population");
	else if (pop.size() < 2) throw std::string("Erreur, impossible d'exécuter une sélection par tournoi avec une population possédant moins de deux individus");
	else {
	  
	  unsigned int sizePop = pop.size();
	  unsigned indice[sizePop];
	  
	  for(unsigned int i = 0; i < sizePop; ++i) indice[i] = i;
	  
	  int candidats[_nbP];
	  
	  for (unsigned int i = 0; i < _nbP; ++i) {
	      int select = rand() % sizePop;
	      candidats[i] = indice[select];
	      indice[select] = indice[sizePop - 1];
	      indice[sizePop - 1] = candidats[i];
	      --sizePop;
	  }
	  
	  // Extraction des deux meilleurs individus
	  int b1 = candidats[0];
	  int b2 = candidats[1];
	  
	  if ( pop[b1]->getScore() < pop[b2]->getScore() ) {
	      b2 = b1;
	      b1 = candidats[1];
	  }
	  
	  for (unsigned int i = 2; i < _nbP; ++i){
	      if ( pop[candidats[i]]->getScore() > pop[b1]->getScore() ) {
		  b2 = b1;
		  b1 = candidats[i];
	      }
	      else if ( pop[candidats[i]]->getScore() > pop[b2]->getScore() ) {
		  b2 = candidats[i];
	      }
	  }
	  
	  return std::make_pair(b1, b2);
	}
	
	return std::make_pair(-1, -1);
      }
    
};
#endif
