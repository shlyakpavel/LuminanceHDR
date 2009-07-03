/**
 * This file is a part of Qtpfsgui package.
 * ----------------------------------------------------------------------
 * Copyright (C) 2006,2007 Giuseppe Rota
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * ----------------------------------------------------------------------
 *
 * Original Work
 * @author Giuseppe Rota <grota@users.sourceforge.net>
 * Improvements, bugfixing
 * @author Franco Comida <fcomida@users.sourceforge.net>
 *
 */

#ifndef TONEMAPPINGWIDGET_H
#define TONEMAPPINGWIDGET_H

#include <QProgressBar>
#include "threadManager.h"
#include "../generated_uic/ui_tonemappingoptions.h"
#include "../Common/gang.h"
#include "../Common/global.h"
#include "../Common/options.h"
#include "../Libpfs/pfs.h"

class QStatusBar;
class MyProgressBar : public QProgressBar {
Q_OBJECT
public:
	MyProgressBar(QWidget * parent = 0 );
	~MyProgressBar();
public slots:
	void advanceCurrentProgress(int);
protected:
	void mousePressEvent(QMouseEvent *event);
signals:
	void leftMouseButtonClicked();
};

class TMWidget : public QWidget, public Ui::ToneMappingOptions
{
Q_OBJECT
public:
	TMWidget(QWidget *parent, pfs::Frame *pfsFrame, ThreadManager *threadManager);
	~TMWidget();
signals:
	void newResult(const QImage&,tonemapping_options*);
private:
	QVector<int> sizes;
	pfs::Frame *pfsFrame;
	Gang    *contrastfactorGang, //mantiuk06
		*saturationfactorGang, 
		*detailfactorGang, 
		// mantiuk08
		*colorSaturationGang,
		*contrastEnhancementGang,
		*luminanceLevelGang,
		// fattal02
		*alphaGang, 
		*betaGang, 
		*saturation2Gang, 
		*noiseGang, 
		*oldFattalGang, 
		// ashikhmin02
		*contrastGang, 
		*simpleGang,
		*eq2Gang,
		// drago03
		*biasGang, 
		// durand02
		*spatialGang, 
		*rangeGang, 
		*baseGang, 
		// pattanaik00
		*multiplierGang, 
		*coneGang, 
		*rodGang, 
		*autoYGang,
		*pattalocalGang,
		// reinhard02
		*keyGang, 
		*phiGang, 
		*range2Gang, 
		*lowerGang, 
		*upperGang, 
		*usescalesGang,
		// reinhard05
		*brightnessGang, 
		*chromaticGang, 
		*lightGang, 
		//
		*pregammagang;

	tonemapping_options ToneMappingOptions;
	void fillToneMappingOptions();
	void setupUndo();
	void fromGui2Txt(QString destination); //i.e. WRITE tmo settings to text file
	QString RecentPathLoadSaveTmoSettings, TMOSettingsFilename, cachepath;
	int out_ldr_cs;
	QStatusBar *statusbar;
	float HeightWidthRatio;
	bool adding_custom_size;
	ThreadManager *threadManager;
private slots:
	void on_pregammadefault_clicked();
	//void on_ashikhmin02Default_clicked();
	//void on_drago03Default_clicked();
	//void on_durand02Default_clicked();
	//void on_fattal02Default_clicked();
	//void on_pattanaik00Default_clicked();
	//void on_reinhard02Default_clicked();
	//void on_reinhard05Default_clicked();
	//void on_MantiukDefault_clicked();
	void on_defaultButton_clicked();
	void on_applyButton_clicked();
	void on_undoButton_clicked();
	void on_redoButton_clicked();
	void on_savesettingsbutton_clicked();
	void on_loadsettingsbutton_clicked();
	//APPLY tmo settings from text file
	void fromTxt2Gui();
	//user wants a custom size.
	void on_addCustomSizeButton_clicked();
	void fillCustomSizeComboBox();
	void updateUndoState(int);
	void showErrorMessage(const char *);
};

#endif
