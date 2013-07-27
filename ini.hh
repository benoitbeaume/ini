#ifndef		__INI_HH__
# define	__INI_HH__

#include	<iostream>
#include	<string>
#include	<fstream>
#include	<map>

using namespace	std;

typedef map<string, map<string, string> > storage;

class		Ini
{
private:
  fstream	file;
  const char   	*name;
  storage	list;
  int		error;

  void		getInfo();
  void		parser();

public:
  Ini(const char*);
  ~Ini();

  string       	readini(const string section, const string param);
  void		writeini(const string section, const string param, const string value);
  void		remini(const string param, const string section = "");
};

#endif		// __INI_HH__
