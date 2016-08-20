/** *************************************************************************
                          kstarslite.h  -  K Desktop Planetarium
                             -------------------
    begin                : 30/04/2016
    copyright            : (C) 2016 by Artem Fedoskin
    email                : afedoskin3@gmail.com
 ***************************************************************************/
/** *************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#ifndef KSTARSLITE_H_
#define KSTARSLITE_H_

#include <config-kstars.h>
#include <QString>
#include <QtQml/QQmlApplicationEngine>
#include <QPalette>

//Needed for Projection enum
#include "projections/projector.h"

// forward declaration is enough. We only need pointers
class KStarsData;
class SkyMapLite;
class SkyPoint;
class GeoLocation;
class ImageProvider;

class FindDialogLite;
class DetailDialogLite;

#ifdef INDI_FOUND
class ClientManagerLite;
#endif

class QQuickItem;

/**
 *@class KStarsLite
 *@short This class loads QML files and connects SkyMapLite and KStarsData
 *Unlike KStars class it is not a main Window but a root object that contains the program clock and holds pointers on SkyMapLite and KStarsData objects.
 *KStarsLite is a singleton, use KStarsLite::createInstance() to create an instance and KStarsLite::Instance() to get a pointer to the instance
 *@author Artem Fedoskin
 *@version 1.0
 */

class KStarsLite : public QObject
{
    Q_OBJECT
private:
    /**
     * @short Constructor.
     * @param doSplash should the splash panel be displayed during
     * initialization.
     * @param startClockRunning should the clock be running on startup?
     * @param startDateString date (in string representation) to start running from.
     */
    explicit KStarsLite( bool doSplash, bool startClockRunning = true, const QString &startDateString = QString() );
    
    static KStarsLite *pinstance; // Pointer to an instance of KStarsLite
    
public:
    /**
     * @short Create an instance of this class. Destroy any previous instance
     * @param doSplash
     * @param clockrunning
     * @param startDateString
     * @note See KStarsLite::KStarsLite for details on parameters
     * @return a pointer to the instance
     */
    static KStarsLite *createInstance( bool doSplash, bool clockrunning = true, const QString &startDateString = QString() );
    
    /** @return a pointer to the instance of this class */
    inline static KStarsLite *Instance() { return pinstance; }
    
    /** Destructor. Does nothing yet*/
    virtual ~KStarsLite();
    
    /** @return pointer to SkyMapLite object which draws SkyMap. */
    inline SkyMapLite* map() const { return m_SkyMapLite; }
    
    /** @return pointer to KStarsData object which contains application data. */
    inline KStarsData* data() const { return m_KStarsData; }
    
    inline ImageProvider *imageProvider() const { return m_imgProvider; }
    
    inline QQmlApplicationEngine *qmlEngine() { return &m_Engine; }
    
    /** @short used from QML to update positions of sky objects and update SkyMapLite */
    Q_INVOKABLE void fullUpdate();

    void applyConfig( bool doApplyFocus = true );
    
#ifdef INDI_FOUND
    /** @return pointer to KStarsData object which handles connection to INDI server. */
    inline ClientManagerLite *clientManagerLite() const { return m_clientManager; }
#endif

    /** @defgroup kconfigwrappers QML wrappers around KConfig
     *  @{
     */

    enum ObjectsToToggle { Stars,
                           DeepSky,
                           Planets,
                           CLines,
                           CBounds,
                           ConstellationArt,
                           MilkyWay,
                           CNames,
                           EquatorialGrid,
                           HorizontalGrid,
                           Ground,
                           Flags,
                           Satellites,
                           Supernovae
                         };
    Q_ENUMS(ObjectsToToggle)
    /**
     * @short setProjection calls Options::setProjection(proj) and updates SkyMapLite
     */
    //Having projection as uint is not good but it will go away once KConfig is fixed
    Q_INVOKABLE void setProjection(uint proj);

    Q_INVOKABLE QColor getColor(QString schemeColor);

    Q_INVOKABLE void toggleObjects(ObjectsToToggle toToggle, bool toggle);

    Q_INVOKABLE bool isToggled(ObjectsToToggle toToggle);

    /** @} */ // end of kconfigwrappers group

signals:
    /** Sent when KStarsData finishes loading data */
    void dataLoadFinished();
    
    /** Makes splash (Splash.qml) visible on startup */
    void showSplash();
    
    /** Emitted whenever TimeSpinBox in QML changes the scale **/
    void scaleChanged(float);
    
public Q_SLOTS:
    /**
     * Update time-dependent data and (possibly) repaint the sky map.
     * @param automaticDSTchange change DST status automatically?
     */
    void updateTime( const bool automaticDSTchange = true );
    
    /** Write current settings to config file. Used to save config file upon exit
     */
    void writeConfig();
    
    /** Load a color scheme.
     * @param name the name of the color scheme to load (e.g., "Moonless Night")
     */
    void loadColorScheme( const QString &name );
    
    /** action slot: open a dialog for setting the time and date */
    void slotSetTime();
    
    /** action slot: toggle whether kstars clock is running or not */
    void slotToggleTimer();
    
    /** action slot: advance one step forward in time */
    void slotStepForward();
    
    /** action slot: advance one step backward in time */
    void slotStepBackward();
    
    void slotTrack();
    
private slots:
    /** finish setting up after the KStarsData has finished
     */
    void datainitFinished();
    
    /** Save data to config file before exiting.*/
    void slotAboutToQuit();
    
private:
    /** Initialize focus position */
    void initFocus();
    
    
    QQmlApplicationEngine m_Engine;
    SkyMapLite *m_SkyMapLite;
    QPalette OriginalPalette, DarkPalette;
    
    QObject *m_RootObject;
    //QQuickItem *m_SkyMapLiteWrapper;
    bool StartClockRunning;
    
    KStarsData *m_KStarsData;
    ImageProvider *m_imgProvider;
    
    //Dialogs
    FindDialogLite *m_findDialogLite;
    DetailDialogLite *m_detailDialogLite;
    
#ifdef INDI_FOUND
    ClientManagerLite *m_clientManager;
#endif
};

#endif
