#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <iostream>
/**
 * Classe abstraite représentant un individu générique.
 * Dispose de méthodes de mutation et de croisement.
 * On conserve pour un individu son âge et son score.
 * @author Ugo Rayer
 */

class Individual {

private:
  int _age;
  int _score;
  
public:
  /**
   * Destructeur
   */
  virtual ~Individual() {}
  
  /**
   * Accesseurs  
   */
  int getAge() const { return _age; }
  int getScore() const { return _score; }
  
  /* * * * * * 
   * METHODS *
   * * * * * */
  
  /**
   * Méthode faisant muter un individu. Modifie de manière aléatoire
   * une seule information de l'individu. 
   */
  virtual void Mutate() = 0;
  
  /**
   * Croisement monopoint entre deux individus. Le parent 1 est l'objet
   * courant et le parent 2 est passé en paramètre. La position du pivot
   * est également passsé en paramètre.
   * @param ind Parent 2
   * @param pos Indice du pivot
   * @return nouvel individu
   */
  virtual Individual& CrossClassic(const Individual& ind,std::size_t pos) = 0;
  
 
  /* * * * * * * * * * * * *
   * SURCHARGE D'OPÉRATEUR *
   * * * * * * * * * * * * */
  
  
  
/** 
  * Affiche l'itemSet dans le flux passé en paramètre
  * @param flux Un flux pour l'affichage
  */
  virtual void print(std::ostream & flux) const;
  
  
};


/** 
* Surcharge de l'opérateur d'affichage
* @param flux Un flux pour l'affichage
* @param i Individu à afficher
*/
std::ostream& operator<<(std::ostream &flux, const Individual & i);

  


#endif