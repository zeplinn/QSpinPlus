#include "qspin/models/QsVerificationResults.h"

//// set of local utility functions
namespace{

void readboolAttribute(QObjectBase* obj,QXmlStreamAttributes& attr, const QString& id,std::function<void(bool)> func){

    QString r;
    if(attr.hasAttribute(id)){
        r = attr.value(id).toString();
        if(r == "false")
            func(false);
        else if (r == "true") {
            func(true);
        }
        else {
            func(false);
            obj->toConsole(QString("%1 is not a boolean (%2),  is set to false").arg(id).arg(r));
        }
    }
    else {
        func(false);
        obj->toConsole(QString("%1 do not exist, value is set to false").arg(id));
    }
}

void readAttribute(QObjectBase* obj,QXmlStreamAttributes& attr, const QString& id,std::function<void(qreal)> func){
    double r;
    if(attr.hasAttribute(id)){
        bool valid = false;
        r = attr.value(id).toDouble(&valid);
        if( valid)
            func(r);
        else{
            func(-1);
            obj->toConsole(QString("%1 is not a number (%2), is set to -1").arg(id).arg(r));
        }
    } else {
        func(-1);
        obj->toConsole(QString("%1 do not exist value is set to -1").arg(id));
    }
}

struct xmlName{
    static constexpr const char  partialOrderReduction[]    = "PartialOrderReduction";
    static constexpr const char  neverClaim[]               = "NeverClaim";
    static constexpr const char  assertionViolations[]      = "AssertionViolations";
    static constexpr const char  acceptanceCycles[]         = "AcceptanceCycles";
    static constexpr const char  invalidEndStates[]         = "InvalidEndStates";

    static constexpr const char  depthReached[]             = "DepthReached";
    static constexpr const char  storedStates[]             = "StoredStates";
    static constexpr const char  matchedStates[]            = "MatchedStates";
    static constexpr const char  transistionTaken[]         = "TransistionTaken";
    static constexpr const char  atomicSteps[]              = "AtomicSteps";
    static constexpr const char  stateSize[]                = "StateSize";
    static constexpr const char  hashConflicts[]            = "HashConflicts";
    static constexpr const char  hashSize[]             	= "HashSize";

    static constexpr const char  forStates[]                = "ForStates";
    static constexpr const char  forHashTable[]             = "ForHashTable";
    static constexpr const char  forSearchStack[]           = "forSearchStack";
    static constexpr const char  inTotal[]              	= "InTotal";

};

}// end of anonymous namespace


qreal VerificationResults::errorCount() const{ return _errorCount; }

void VerificationResults::setErrorCount(qreal value){
    _errorCount = value;
    emit errorCountChanged();
}

QString VerificationResults::elapsedTime() const{ return _elapsedTime.toString("hh.mm.ss"); }

void VerificationResults::setElapsedTime(QTime value){
    if(_elapsedTime != value){
        _elapsedTime = value;
        emit elapsedTimeChanged();
    }
}


FullStateSpaceSpecifications *VerificationResults::stateSpaceSpec() const{ return _stateSpaceSpec; }

FullStateSpaceFor *VerificationResults::stateSpaceFor() const{ return _stateSpaceFor; }

MemoryUsage *VerificationResults::memoryUsage() const{ return _memoryUsage; }

QString VerificationResults::version() const{ return _version; }

void VerificationResults::setVersion(QString value){
    if(_version != value){
        _version = value;
        emit versionChanged();
    }
}

QString VerificationResults::unreachedStates() const{ return _unreachedStates; }

void VerificationResults::setUnreachedStates(QString value){
    if(_unreachedStates != value){
        _unreachedStates = value;
        emit unreachedStatesChanged();
    }
}

VerificationResults::VerificationResults(QObject *parent, EventAggregator *msg)
    :QObjectBase (parent,msg)
    ,_stateSpaceFor(new FullStateSpaceFor(this,msg))
    ,_stateSpaceSpec(new FullStateSpaceSpecifications(this,msg))
    ,_memoryUsage(new MemoryUsage(this,msg))
    ,_errorCount(-1)
    ,_versionRegex(QRegularExpression("[0-9](\\.[0-9])*\\s*[-]{2}\\s[0-9]+\\s*[a-zA-Z]+\\s*[0-9]{4}"))
{

}

void VerificationResults::constructRegexPatterns(){

    _matches << new ResultMatchString(_versionRegex.pattern(),[this]( QString str){
                this->setVersion(str);
});
    _matches << new ResultMatchString("(unreached(.*[\\s\\r\\n]){3})+",[this](QString str){
                this->setUnreachedStates(str);
});
    _matches << new ResultMatchReal("(?<=errors:\\s)[0-9]+",[this](qreal val){
                this->setErrorCount(val);
});


    _matches << new ResultMatchBool("[+-](?=(\\s*Partial))",[this](bool val){
        this->stateSpaceFor()->setPartialOrderReduction(val);
    });
    //never claim
    _matches << new ResultMatchBool("(?<=(never claim[\\s]{10}))[-+]",[this](bool val){
        this->stateSpaceFor()->setNeverClaim(val);
    });
    // assertion violations
    _matches << new ResultMatchBool("(?<=(assertion\\sviolations[\\t\\s]))[-+]",[this](bool val){
        this->stateSpaceFor()->setAssertionViolations(val);
    });
    _matches << new ResultMatchBool("(?<=(acceptance\\scycles[\\t\\s]))[-+]",[this](bool val){
        this->stateSpaceFor()->setAcceptanceCycles(val);
    });
    _matches << new ResultMatchBool("(?<=(invalid\\send\\sstates\\s))[+-]",[this](bool val){
        this->stateSpaceFor()->setInvalidEndStates(val);
    });

    // statespace specifications
    // state vector
    _matches << new ResultMatchReal("[0-9]+(?=(\\s*byte,\\sdepth\\sreached))",[this](qreal val){
                this->stateSpaceSpec()->setStateSize(val);
});
    // depth reached
    _matches << new ResultMatchReal("[0-9]+(?=(,\\s*errors:))",[this](qreal val){
                this->stateSpaceSpec()->setDepthReached(val);
});
    // states stored
    _matches << new ResultMatchReal("[0-9]+(?=(\\s*states,\\s*stored))",[this](qreal val){
                this->stateSpaceSpec()->setStoredStates(val);
});
    // matched states
    _matches << new ResultMatchReal("[0-9]+(?=(\\s*states,\\s*matched))",[this](qreal val){
                this->stateSpaceSpec()->setMatchedStates(val);
});
    // transitions
    _matches << new ResultMatchReal("[0-9]+(?=(\\s*transitions))",[this](qreal val){
                this->stateSpaceSpec()->setTransitionTaken(val);
});
    // atomic steps
    _matches << new ResultMatchReal("[0-9]+(?=(\\s*atomic\\s*steps))",[this](qreal val){
                this->stateSpaceSpec()->setAtomicSteps(val);
});
    // hash conflict
    _matches << new ResultMatchReal("(?<=(hash\\sconflicts:\\s{9}))[0-9]+",[this](qreal val){
                this->stateSpaceSpec()->setHashConflicts(val);
});
    _matches << new ResultMatchReal("(?<=([-]w))[0-9]+",[this](qreal val){
                this->stateSpaceSpec()->setHashSize(val);
});

    // memory usage
    // forstates
    _matches << new ResultMatchReal("[0-9]+(\\.[0-9]+)?(?=(\\s*equivalent))",[this](qreal val){
                this->memoryUsage()->setForStates(val);
});
    // hash table
    _matches << new ResultMatchReal("[0-9]+(\\.[0-9]+)?(?=([a-zA-Z\\s]+table))",[this](qreal val){
                this->memoryUsage()->setForHashTable(val);
});
    _matches << new ResultMatchReal("[0-9]+(\\.[0-9]+)?(?=([a-zA-Z\\s]+stack))",[this](qreal val){
                this->memoryUsage()->setForSearchStack(val);
});
    _matches << new ResultMatchReal("[0-9]+(\\.[0-9]+)?(?=(\\s*total))",[this](qreal val){
                this->memoryUsage()->setInTotal(val);
});
}

void VerificationResults::clearRegexPatterns(){
    while (!_matches.isEmpty()) {
        auto i = _matches.takeLast();
        delete i;
    }
}
void VerificationResults::extractVerificationResults(const QString &results){

    _rawReport = results;
    for(auto m : _matches){
        m->isMatch(results);
    }

    // grouped variable
    int second=0, minute=0, hour=0;
    QRegularExpression timeRegex;

    timeRegex.setPattern("[0-9]+(\\.[0-9]+)?(?=(\\s*seconds))");
    auto m = timeRegex.match(results);
    if(m.hasMatch())
        second = m.captured().toInt();
    second = m.captured().toInt();

    timeRegex.setPattern("[0-9]+(\\.[0-9]+)?(?=(\\s*minutes))");
    m = timeRegex.match(results);
    if(m.hasMatch())
        minute = m.captured().toInt();

    timeRegex.setPattern("[0-9]+(\\.[0-9]+)?(?=(\\s*hours))");
    m = timeRegex.match(results);
    if(m.hasMatch())
        hour = m.captured().toInt();
    setElapsedTime(QTime(hour,minute,second));
}

bool VerificationResults::isFirstMatch(const QString& result){
    auto m = _versionRegex.match(result);
    return m.hasMatch();
}

void VerificationResults::read(QXmlStreamReader &xml)
{
    if(xml.name() == qs().nameof(this)){
        auto attr = xml.attributes();
        if(attr.hasAttribute("version")){
            setVersion(attr.value("version").toString());
        }
        if(attr.hasAttribute("errorCount")){
            bool valid = false;
            auto v = attr.value("errorCount").toDouble(&valid);
            if(valid)
                setErrorCount(v);
            else{
                qCritical("not an valid errorCount");
            }
        }
        while (xml.readNextStartElement()) {
            if(xml.name() == qs().nameof(_stateSpaceFor)){
                _stateSpaceFor->read(xml);
            }
            else if (xml.name() == qs().nameof(_stateSpaceSpec)) {
                _stateSpaceSpec->read(xml);
            }
            else if(xml.name() == qs().nameof(_memoryUsage)){
                _memoryUsage->read(xml);
            }
            else if(xml.name()=="UnreachedStates"){
                setUnreachedStates(xml.readElementText());
            }
            else if (xml.name()=="ElapsedTime") {


                setElapsedTime(QTime::fromString(xml.readElementText(),"hh.mm.ss"));
            }
            else if (xml.name()== "RawVerificationReport") {
                _rawReport = xml.readElementText();
            }
        }
    }
}

void VerificationResults::write(QXmlStreamWriter &xml)
{
    xml.writeStartElement(qs().nameof(this));
    xml.writeAttribute("version",version());
    xml.writeAttribute("errorCount",QString::number(errorCount()));
    xml.writeTextElement("ElapsedTime",elapsedTime());
    _stateSpaceFor->write(xml);
    _stateSpaceSpec->write(xml);
    _memoryUsage->write(xml);
    xml.writeTextElement("UnreachedStates",unreachedStates());
    xml.writeTextElement("RawVerificationReport",_rawReport);
    xml.writeEndElement();
}

QString VerificationResults::rawReport(){
    return  _rawReport;
}
bool FullStateSpaceFor::invalidEndStates() const{ return _invalidEndStates; }

void FullStateSpaceFor::setInvalidEndStates(bool value){
    if(_invalidEndStates != value){
        _invalidEndStates = value;
        emit invalidEndStatesChanged();
    }
}

bool FullStateSpaceFor::partialOrderReduction() const{ return _partialOrderReduction; }

void FullStateSpaceFor::setPartialOrderReduction(bool value){
    if(_partialOrderReduction != value){
        _partialOrderReduction = value;
        emit partialOrderReductionChanged();
    }
}

bool FullStateSpaceFor::neverClaim() const{ return _neverClaim; }

void FullStateSpaceFor::setNeverClaim(bool value){
    if(_neverClaim != value){
        _neverClaim = value;
        emit neverClaimChanged();
    }
}

bool FullStateSpaceFor::assertionViolations() const{ return _assertionViolations; }

void FullStateSpaceFor::setAssertionViolations(bool value){
    if(_assertionViolations != value){
        _assertionViolations = value;
        emit assertionViolationsChanged();
    }
}

bool FullStateSpaceFor::acceptanceCycles() const{ return _acceptanceCycles; }

void FullStateSpaceFor::setAcceptanceCycles(bool value){
    if(_acceptanceCycles != value){
        _acceptanceCycles = value;
        emit acceptanceCyclesChanged();
    }
}

FullStateSpaceFor::FullStateSpaceFor(QObject *parent, EventAggregator *msg)
    :QObjectBase (parent,msg)
    ,_partialOrderReduction(false)
    ,_neverClaim(false)
    ,_assertionViolations(false)
    ,_acceptanceCycles(false)
    ,_invalidEndStates(false)
{}



void FullStateSpaceFor::read(QXmlStreamReader &xml)
{
    if(xml.name() == qs().nameof(this)){
        xmlName n;
        auto attr = xml.attributes();
        readboolAttribute(this,attr,n.partialOrderReduction,[this](bool val){
            this->setPartialOrderReduction(val);
        });
        readboolAttribute(this,attr,n.neverClaim,[this](bool val){
            this->setNeverClaim(val);
        });
        readboolAttribute(this,attr,n.assertionViolations,[this](bool val){
            this->setAssertionViolations(val);
        });
        readboolAttribute(this,attr,n.acceptanceCycles,[this](bool val){
            this->setAcceptanceCycles(val);
        });
        readboolAttribute(this,attr,n.invalidEndStates,[this](bool val){
            this->setInvalidEndStates(val);
        });
        xml.skipCurrentElement();
    }
}

void FullStateSpaceFor::write(QXmlStreamWriter &xml)
{
    xml.writeStartElement(qs().nameof(this));
    xmlName n;
    xml.writeAttribute(n.partialOrderReduction,partialOrderReduction() ? "true" : "false");
    xml.writeAttribute(n.neverClaim,neverClaim() ? "true" : "false");
    xml.writeAttribute(n.assertionViolations,assertionViolations() ? "true" : "false");
    xml.writeAttribute(n.acceptanceCycles,acceptanceCycles() ? "true" : "false");
    xml.writeAttribute(n.invalidEndStates,invalidEndStates() ? "true" : "false");
    xml.writeEndElement();
}


qreal FullStateSpaceSpecifications::atomicSteps() const{ return _atomicSteps; }

void FullStateSpaceSpecifications::setAtomicSteps(qreal value){
    _atomicSteps = value;
    emit atomicStepsChanged();

}

qreal FullStateSpaceSpecifications::depthReached() const{ return _depthReached; }

void FullStateSpaceSpecifications::setDepthReached(qreal value){
    _depthReached = value;
    emit depthReachedChanged();

}

qreal FullStateSpaceSpecifications::storedStates() const{ return _storedStates; }

void FullStateSpaceSpecifications::setStoredStates(qreal value){
    _storedStates = value;
    emit storedStatesChanged();

}

qreal FullStateSpaceSpecifications::matchedStates() const{ return _matchedStates; }

void FullStateSpaceSpecifications::setMatchedStates(qreal value){
    _matchedStates = value;
    emit matchedStatesChanged();

}

qreal FullStateSpaceSpecifications::transitionTaken() const{ return _transitionTaken; }

void FullStateSpaceSpecifications::setTransitionTaken(qreal value){

    _transitionTaken = value;
    emit transitionTakenChanged();
}

qreal FullStateSpaceSpecifications::stateSize() const{ return _stateSize; }

void FullStateSpaceSpecifications::setStateSize(qreal value){
    _stateSize = value;
    emit stateSizeChanged();

}

qreal FullStateSpaceSpecifications::hashConflicts() const{ return _hashConflicts; }

void FullStateSpaceSpecifications::setHashConflicts(qreal value){
    _hashConflicts = value;
    emit hashConflictsChanged();

}

qreal FullStateSpaceSpecifications::hashSize() const{ return _hashSize; }

void FullStateSpaceSpecifications::setHashSize(qreal value){
    _hashSize = value;
    emit hashSizeChanged();

}



FullStateSpaceSpecifications::FullStateSpaceSpecifications(QObject *parent, EventAggregator *msg)
    :QObjectBase (parent,msg)
    ,_depthReached(-1)
    ,_storedStates(-1)
    ,_matchedStates(-1)
    ,_transitionTaken(-1)
    ,_atomicSteps(-1)
    ,_stateSize(-1)
    ,_hashConflicts(-1)
    ,_hashSize(-1)
{}

void FullStateSpaceSpecifications::read(QXmlStreamReader &xml)
{
    if(xml.name() == qs().nameof(this)){
        xmlName n;
        auto attr = xml.attributes();
        readAttribute(this,attr,n.depthReached,[this](qreal val){
            this->setDepthReached(val);
        });
        readAttribute(this,attr,n.storedStates,[this](qreal val){
            this->setStoredStates(val);
        });
        readAttribute(this,attr,n.matchedStates,[this](qreal val){
            this->setMatchedStates(val);
        });
        readAttribute(this,attr,n.transistionTaken,[this](qreal val){
            this->setTransitionTaken(val);
        });
        readAttribute(this,attr,n.atomicSteps,[this](qreal val){
            this->setAtomicSteps(val);
        });
        readAttribute(this,attr,n.stateSize,[this](qreal val){
            this->setStateSize(val);
        });
        readAttribute(this,attr,n.hashConflicts,[this](qreal val){
            this->setHashConflicts(val);
        });
        readAttribute(this,attr,n.hashSize,[this](qreal val){
            this->setHashSize(val);
        });
        xml.skipCurrentElement();
    }
}

void FullStateSpaceSpecifications::write(QXmlStreamWriter &xml)
{
    xml.writeStartElement(qs().nameof(this));
    xmlName n;
    xml.writeAttribute(n.depthReached,QString::number( depthReached()));
    xml.writeAttribute(n.storedStates,QString::number( storedStates()));
    xml.writeAttribute(n.matchedStates,QString::number( matchedStates()));
    xml.writeAttribute(n.transistionTaken,QString::number( transitionTaken()));
    xml.writeAttribute(n.atomicSteps,QString::number( atomicSteps()));
    xml.writeAttribute(n.stateSize,QString::number( stateSize()));
    xml.writeAttribute(n.hashConflicts,QString::number(hashConflicts()));
    xml.writeAttribute(n.hashSize,QString::number(hashSize()));

    xml.writeEndElement();
}

qreal MemoryUsage::forStates() const{ return _forStates; }

void MemoryUsage::setForStates(qreal value){
    _forStates = value;
    emit forStatesChanged();

}

qreal MemoryUsage::forHashTable() const{ return _forHashTable; }

void MemoryUsage::setForHashTable(qreal value){
    _forHashTable = value;
    emit forHashTableChanged();

}

qreal MemoryUsage::forSearchStack() const{ return _forSearchStack; }

void MemoryUsage::setForSearchStack(qreal value){
    _forSearchStack = value;
    emit forSearchStackChanged();
}

qreal MemoryUsage::inTotal() const{ return _inTotal; }

void MemoryUsage::setInTotal(qreal value){
    _inTotal = value;
    emit inTotalChanged();
}

MemoryUsage::MemoryUsage(QObject *parent, EventAggregator *msg)
    :QObjectBase (parent,msg)
    ,_forStates(-1)
    ,_forHashTable(-1)
    ,_forSearchStack(-1)
    ,_inTotal(-1)
{}




void MemoryUsage::read(QXmlStreamReader &xml)
{
    if(xml.name() == qs().nameof(this)){

        auto attr = xml.attributes();
        xmlName n;
        readAttribute(this,attr,n.forStates,[this](qreal val){
            this->setForStates(val);
        });
        readAttribute(this,attr,n.forHashTable,[this](qreal val){
            this->setForHashTable(val);
        });
        readAttribute(this,attr,n.forSearchStack,[this](qreal val){
            this->setForSearchStack(val);
        });
        readAttribute(this,attr,n.inTotal,[this](qreal val){
            this->setInTotal(val);
        });
        xml.skipCurrentElement();
    }
}
void MemoryUsage::write(QXmlStreamWriter &xml)
{
    xml.writeStartElement(qs().nameof(this));
    xmlName n;
    xml.writeAttribute(n.forStates,QString::number( forStates()));
    xml.writeAttribute(n.forHashTable,QString::number( forHashTable()));
    xml.writeAttribute(n.forSearchStack,QString::number( forSearchStack()));
    xml.writeAttribute(n.inTotal,QString::number( inTotal()));
    xml.writeEndElement();
}

bool ResultMatchReal::isMatch(const QString &result){
    if(!_isRead) return false;
    auto m = regex.match(result);
    if(m.hasMatch()){
        bool valid =false;
        auto v = m.captured().toDouble(&valid);
        if(!valid){
            QString err = QString ("invalid result matched %1, using pattern: %2")
                    .arg(m.capturedTexts().join(""))
                    .arg(regex.pattern());
        }
        else{

            _func(v);
            _isRead = true;
            return true;
        }
    }
    return  false;
}

bool ResultMatchBool::isMatch(const QString &result)
{
    if(!_isRead) return false;
    auto m = regex.match(result);
    if(m.hasMatch()){
        auto str = m.captured();
        if(str.contains("+")){
            _func(true);

        }
        else if(str.contains("-")){
            _func(false);
        }
        else{
            QString err = QString ("invalid result matched %1, using pattern: %2")
                    .arg(str)
                    .arg(regex.pattern());
            _func(false);
            qCritical(err.toLocal8Bit());
        }
        _isRead= true;
        return  true;
    }
    return false;
}

ResultMatchString::ResultMatchString(const QString &pattern, std::function<void (QString)> func)
    :ResultMatch (pattern)
    ,_func(func)
{}

bool ResultMatchString::isMatch(const QString &result){
    if(!_isRead) return false;
    auto m = regex.match(result);
    if(m.hasMatch()){
        auto str = m.captured();
        _func(str);
        _isRead = true;
        return  true;
    }
    return false;
}
