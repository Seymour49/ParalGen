#ifndef FREQPOP_H
#define FREQPOP_H

#include "initPop.h"
#include "dataSet.h"
#include "dataSetO.h"

/**
 * Cette classe représente une implémentation de la fonction d'initialisation
 * de la population de notre algorithme génétique. La densité nécessaire cor-
 * respond au nombre de bits allant être fixé à 1 lors de la construction d'un
 * individu. 
 * La méthode de construction calcule la fréquence de chaque élément et 
 * catégorise ensuite d'une part les éléments les plus fréquents et d'autre
 * part les suivants de sorte que le nombre total des éléments choisis soit
 * égal à la densité passée en paramètre. Nous recommandons une densité faible
 * ( < 5% ).
 * L'algorithme d'initialisation a également besoin d'avoir accès au jeu de données
 * mais cette classe n'est pas chargée de les détruire.
 * TODO: Ajouter en paramètre une liste des valeurs que peuvent prendre les items d'un individu ('0' et '1' dans notre cas)
 * TODO: Éviter de juste récupérer le pointeur sur les jeux de données (introspection)
 * @var float density
 * @author Ugo Rayer
 * 
 */

class FreqPop : public InitPop<char> {

private:
  DataSet<char> * _data;
  DataSetO<char> * _dataO;
  float _density;
  
public: 
  
  /* * * * * * * *
   * CONSTRUCTOR *
   * * * * * * * */
  
  /**
   * Constructeur initialisant le jeu de donné et la densité à 5 % si non spécifié
   * @param data : dataset utilisé
   * @param density : densité souhaitée
   * @author Ugo Rayer
   */
  FreqPop(DataSet<char> * const data, float density = 0.05);

  
  /**
   * Constructeur initialisant le jeu de donné optimisé et la densité à 5 % si non spécifié
   * @param data : datasetO utilisé
   * @param density : densité souhaitée
   * @author Ugo Rayer
   */
  FreqPop(DataSetO<char> * const data, float density = 0.05);
  
  
  /**
   * Constructeur initialisant le jeu de donné non optimisé et l'optimisé, et la densité à 5 % si non spécifié
   * @param data : dataset non optimisé
   * @param dataO : data optimisé
   * @param density : densité souhaitée
   * @author Ugo Rayer
   */
  FreqPop(DataSet<char> * const data, DataSetO<char> * const dataO, float density = 0.05);
  
  
  /**
   * Constructeur par recopie
   * @author Johan Defaye
   */
  FreqPop(const FreqPop & f);
  

  
  
  /* * * * * * * * * * *
   * GETTER ET SETTER  *
   * * * * * * * * * * */
  
  float getDensity() const {return _density;}
  
  void setDensity(float density) {_density = density;}
    
  void setData(DataSet<char> * const data) { _data = data; }
    
  void setDataO(DataSetO<char> * const dataO) { _dataO = dataO; }
  
  
  

  /* * * * * * 
   * METHODS *
   * * * * * */
/**
 * Rempli un vecteur d'individu initialement null avec des individu fréquent dans le jeu de donnée
 * Retourne une exception si :
 *  - population vide
 *  - jeu de donné non initalisé
 *  - jeu de donné vide
 * @param pop :  Référence sur le vecteur à remplir
 * @author Ugo Rayer
 */
  void execute(std::vector<Individual<char> *> & pop);

/**
 * Rempli un vecteur d'individu initialement null avec des individu fréquent dans le jeu de donnée optimisé
 * Retourne une exception si :
 *  - population vide
 *  - jeu de donné optimisé non initalisé
 *  - jeu de donné optimisé vide
 * @param pop : Référence sur le vecteur à remplir
 * @author Ugo Rayer
 */
  void executeO(std::vector<Individual<char> *> & pop);
  
  
  
  /* * * * * * * *
   * DESTRUCTOR  *
   * * * * * * * */
  
    ~FreqPop();
  
};
#endif