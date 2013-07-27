#include	"ini.hh"

Ini::Ini(const char *toOpen) : name(toOpen)
{
  this->error = 0;
  this->file.open(toOpen, ios::in);
  if (file.is_open())
    {
      this->getInfo();
      this->file.close();
    }
}

Ini::~Ini()
{
  map<string, string>	tmp;

  if (this->error)
    return;
  this->file.open(this->name, ios::out | ios::trunc);
  for (storage::iterator it = this->list.begin(); it != this->list.end(); ++it)
    {
      this->file << "[" << it->first << "]" << endl;
      tmp = it->second;
      for (map<string, string>::iterator it2 = tmp.begin(); it2 != tmp.end(); ++it2)
	this->file << it2->first << "=" << it2->second << endl;
    }
  this->file.close();
}

void		Ini::getInfo()
{
try
  {
    this->parser();
  }
 catch (int i)
   {
     if (i == 1)
       cerr << "[" << this->name << "] A sections is missing" << endl;
     else
       cerr << "[" << this->name << "] Format error" << endl;
     this->error = 1;
   }
}

void		Ini::parser()
{
  string	tmp;
  string	section;

  while (getline(this->file, tmp))
    {
      if (!tmp.length())
	throw 0;
      if (tmp.at(0) == '[')
	section = tmp.substr(1, tmp.length() - 2);
      else if (tmp.find("=") < tmp.length())
	{
	  if (section.length())
	    list[section][tmp.substr(0, tmp.find("="))] = tmp.substr(tmp.find("=") + 1);
	  else
	    throw 1;
	  }
      else
	throw 0;
    }
}

string		Ini::readini(const string section, const string param)
{
  return this->list[section][param];
}

void		Ini::writeini(const string section, const string param, const string value)
{
  this->list[section][param] = value;
}

void		Ini::remini(const string section, const string param)
{
  if (this->error)
    return;
  if (!param.length())
    this->list.erase(section);
  else
    this->list[section].erase(param);
}
