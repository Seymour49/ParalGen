#ifndef INDELPOLICY_H
#define INDELPOLICY_H

#include <iostream>
#include <vector>

#include "individual.h"

/**
 * Cette classe abstraite représente la fonction de gestion de la population
 * lors d'une passe d'un algorithme génétique.
 * Chaque implémentation doit donc définir ses choix en matières d'individus à
 * supprimer et selon quel critères.
 * La méthode execute applique cette politique à partir d'un individu et d'une
 * population passés en paramètres.
 * @author Ugo Rayer
 */

template <typename T>
class IndelPolicy {
public:
  

    
    /* * * * * *
     * METHODS *
     * * * * * */
    
    /**
     * Méthode d'application de la politique de gestion de la population vis à 
     * vis d'un individu à potentiellement insérer.
     * @param ind : individu
     * @param pop : population
     * @author Ugo Rayer 
     */
    virtual void execute(const Individual<T> & ind, std::vector<Individual<T> *> & pop) = 0;
  
    
    
    /* * * * * * * *
     * DESTRUCTOR  *
     * * * * * * * */
    
    
    virtual ~IndelPolicy()
    {}
};
#endif