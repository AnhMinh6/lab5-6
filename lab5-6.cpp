#include <iostream>
#include <fstream>
#include <cstring>

using namespace std;
//Вариант 7

class Article
{
private:
    char* authors = nullptr;        //список авторов
    char* title = nullptr;          //название статьи
    double citation_coeff;          //коэф цитирования
    int volume;                     //объем статьи
    char* language = nullptr;       //язык статьи

public:
    //конутруктор без параметров
    Article(){                          
        setAll("Авторы", "Название статьи", 0, 0, "Язык статьи");
    }
    //конструктор с параметрами
    Article(const char* s_authors, const char* s_title, double s_citation_coeff, int s_volume, const char* s_language) { 
        setAll(s_authors, s_title, s_citation_coeff, s_volume, s_language);
    }
    //конструктор копирования
    Article( const Article & article){  
        setAll(article.authors, article.title, article.citation_coeff, article.volume, article.language);
    } 

    //вывод на экран каждого поля
    void printAuthors() const {
        cout << "Список авторов: " << authors << endl;
    }
    void printTitle() const {
        cout << "Название статьи: " << title << endl;
    }
    void printCitation_coeff() const {
        cout << "Коэффициент цитирования: " << citation_coeff << endl;
    }
    void printVolume() const {
        cout << "Объем статьи: " << volume << endl;
    }
    void printLanguage() const {
        cout << "Язык статьи: " << language << endl;
    }
    void printAll() const {
        cout << "Список авторов: " << authors << endl;
        cout << "Название статьи: " << title << endl;
        cout << "Коэффициент цитирования: " << citation_coeff << endl;
        cout << "Объем статьи: " << volume << endl;
        cout << "Язык статьи: " << language << endl;
    }

    //редактирование каждого поля
    void setAuthors(const char* s_authors) {
        delete[] authors;
        authors = new char[strlen(s_authors) + 1];
        strcpy(authors, s_authors);
    }
    void setTitle(const char* s_title){
        delete[] title;
        title = new char[strlen(s_title) + 1];
        strcpy(title, s_title);
    }
    void setCitation_coeff(double s_citation_coeff){
        citation_coeff = s_citation_coeff;
    }
    void setVolume(int s_volume){
        volume = s_volume;
    }
    void setLanguage(const char* s_language){
        delete[] language;
        language = new char[strlen(s_language) + 1];
        strcpy(language, s_language);
    }
    void setAll(const char* s_authors, const char* s_title, double s_citation_coeff, int s_volume, const char* s_language){
        setAuthors(s_authors);
        setTitle(s_title);
        citation_coeff = s_citation_coeff;
        volume = s_volume;
        setLanguage(s_language);
    }

    //получение значений каждого поля
    const char* getAuthors() const {
        return authors;
    }
    const char* getTitle() const {
        return title;
    }
    double getCitation_coeff() const {
        return citation_coeff;
    }
    int getVolume() const {
        return volume;
    }
    const char* getLanguage() const {
        return language;
    }

    // //1 функция определяющая количество статей у автора
    // int count_articles_by_author(const char* author) { 
    //     int count = 0;
    //     if (strstr(authors, author)) {              // strstr – поиск первого вхождения строки А в строку В
    //         count++; 
    //     }
    //     return count;
    // }

    //функция сравнения одинаковых строк
    static bool CompareStrings(const char* name1, const char* name2){ 
        return strcmp(name1, name2) == 0;
    }

    //1 функция определяющая количество статей у автора
    static int artic_counts(Article* titles, int count, const char* author){
        int articles = 0;                   //количество статьей 
        for (int i = 0; i < count; i++){
            if (CompareStrings(titles[i].getAuthors(), author)){
                articles ++;
            }
        }
        return articles; 
    }

    //2 функция определяющая средний объем статей с КЦ больше N
    static float average_article_length(Article* titles, int count, int N){
        int lengths = 0;                    //длина/обьем статьи чтобы не запутаться в volume
        int articles = 0;                   //количество статьей 
        for (int i = 0; i < count; i++){
            if (titles[i].getCitation_coeff() > N) {
                lengths += titles[i].getVolume();
                articles += 1;
            }
        }
        return lengths/articles;
    }

    //функция вычисляет цитируемость автора (средняя цитируемость всех его статей)
    static float average_auhors_CC(Article* titles, int count, const char* author) {
        double CC = 0;                  //коэфициент цитируемости 
        int articles = 0;               //количество статьей 
        for (int i = 0; i < count; i++){
            if (CompareStrings(titles[i].getAuthors(), author)){
                CC += titles[i].getCitation_coeff();
                articles += 1;
            }
        }
        return CC/articles;
    }

    //3 Список авторов по цитируемости 
    //функция используется для сортировки списка авторов по их среднему коэффициенту цитирования (CC)
    static const char** list_coeff(Article* titles, int count, int & number_of_authors){
        const char** authors = new const char* [count];
        float* CC = new float [count];
        for (int i = 0; i <  count; i++){
            authors[i] = titles[i].getAuthors();
            CC[i] = titles[i].average_auhors_CC(titles, count, titles[i].getAuthors());
        }
        for (int i = 0; i < count; i++){ 
            for (int j = 0; j < count; j++){
                if (CC[j] < CC[j+1]){
                    float temp_CC = CC[j + 1];
                    const char* temp_authors = authors[j];
                    CC[j] = CC[j + 1];
                    authors[j] = authors[j + 1];
                    CC[j + 1] = temp_CC;
                    authors[j + 1] = temp_authors;
                }
            }
        }
        //функция используется для создания списка уникальных авторов 
        number_of_authors = 1;
        for (int i = 0; i < count - 1; i++){
            if (!CompareStrings(authors[i], authors[i +1])){
                number_of_authors += 1;
            }
        }

        const char** list = new const char*[number_of_authors];
        int k = 0;
        for (int i = 0; i < count; i++){
            if (k > 0 && CompareStrings(list[k - 1], authors[i])) {
                continue;
            }
            list[k] = authors[i];
            k++;
        }
        delete [] CC;
        delete [] authors;
        return list;
    }

    ~Article(){ //деструктор
        delete[] authors;
        delete[] title;
        delete[] language;
    }
};

int main(){
    Article first;
    first.setAuthors("К.С.Петров");
    first.setTitle("Мировая экономика и ее изменения за последние 3 года");
    first.setCitation_coeff(33.51);
    first.setVolume(71);
    first.setLanguage("Русский");

    first.printAuthors();
    first.printTitle();
    first.printCitation_coeff();
    first.printVolume();
    first.printLanguage();
    cout << endl;

    Article second("А.С.Морозов", "Польза витаминов зимой", 17.46, 52, "Русский");
    second.printAll();
    cout << endl;

    Article third(first);
    third.printAll();
    cout << endl;

    cout << "Введите количество статьей:" << endl;
    int count;
    cin >> count;
    Article* titles = new Article[count];
    for (int i = 0; i < count; i++) {
        cout << i + 1 << ". статья" << endl;

        cout << "Введите автора статьи:" << endl;
        char* authors = new char[32];
        cin >> authors;
        titles[i].setAuthors(authors);
        delete[] authors;

        cout << "Введите название статьи:" << endl;
        char* title = new char[64];
        cin >> title;
        titles[i].setAuthors(title);
        delete[] title;

        cout << "Введите коэффициент цитируемости статьи:" << endl;
        float CC;
        cin >> CC;
        titles[i].setCitation_coeff(CC);

        cout << "Введите объем статьи:" << endl;
        int volume;
        cin >> volume;
        titles[i].setVolume(volume);

        cout << "Введите язык статьи:" << endl;
        char* language = new char[16];
        cin >> language;
        titles[i].setLanguage(language);
        delete[] language;
        cout << endl;     
    }
    //Количество статьей у автора Х
    cout << "Введите имя автора чтобы узнать количество его статей: ";
    char* author = new char[32];
    cin >> author;
    cout << "У автора " << author << ": " << Article::artic_counts(titles, count, author) << " статьей." << endl << endl;

    //Средний объем статей с КЦ больше N
    cout << "Введите коэфициент цитирования N, чтобы узнать средний обьем статьей больше: ";
    float N;
    cin >> N;
    cout << "Средний обьем статьей с коэффициентом цитирования больше " << N << ": " << Article::average_article_length(titles, count, N) << endl << endl;

    //Список авторов по цитируемости
    cout << " " << endl;
    int number_of_authors;
    const char** list = Article::list_coeff(titles, count, number_of_authors);
    for (int i = 0; i < number_of_authors; i++) {
        cout << i + 1 << ". " << list[i] << " (цитируемость автора - " << Article::average_auhors_CC(titles, count, list[i]) << ")"<< endl;
    }
    delete [] titles;
    delete [] list;
    return 0; 

}