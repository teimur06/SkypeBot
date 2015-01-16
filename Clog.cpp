#include "Clog.h"

Clog::Clog(QString module, QString pathLog, int level)
{
    if (!setlog(pathLog)) throw - 2;
    setModule(module);
    setLevel(level);
}

Clog::Clog(){}


void Clog::setModule(QString module)
{
   this->module = module;
}

Clog::~Clog()
{
    fout.close(); // закрываем файл
}


    void Clog::writeLn(QString text)
	{
        QTextStream out(&fout);
		
        out << QDateTime::currentDateTime().date().day() << '.' << QDateTime::currentDateTime().date().month() << '.' << QDateTime::currentDateTime().date().year() << ' ' \
            << QDateTime::currentDateTime().time().hour() << ':' << QDateTime::currentDateTime().time().minute() << ':' << QDateTime::currentDateTime().time().second() << ' ' \
			 <<	module << " > " << text << '\n';
        out.flush();

	}


    void Clog::writeLn(QString text, int level)
	{
		if (level <= this->level)
			this->writeLn(text);
	}


	void Clog::setLevel(int level)
	{
		level > 10 ? this->level = 10 : this->level = level;
		level <  1 ? this->level = 1 : this->level = level;
	}

	int Clog::getLevel()
	{
		return this->level;
	}

    Clog &Clog::operator << (QString text)
	{
        this->writeLn(text);
        return *this;
	}


bool Clog::setlog(QString pathLog)
{
    fout.setFileName(pathLog);
    fout.open(QIODevice::Append | QIODevice::Text);
    if (!fout.isOpen())
    {

        return false;
    } else return true;
}
