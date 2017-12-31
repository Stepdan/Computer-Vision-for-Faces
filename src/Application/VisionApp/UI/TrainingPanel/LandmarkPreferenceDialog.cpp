#include "LandmarkPreferenceDialog.h"
#include "ui_LandmarkPreferenceDialog.h"

#include <QAbstractButton>
#include <QFileDialog>

#include "SettingsManager.h"

namespace
{
const QString TRAINING_LAST_FOLDER_PATH = "TRAINING_LAST_FOLDER_PATH";
const QString TRAINING_LAST_XML_PATH    = "TRAINING_LAST_XML_PATH";
const QString TRAINING_LAST_FILENAME    = "TRAINING_LAST_FILENAME";
}

LandmarkPreferenceDialog::LandmarkPreferenceDialog(const SharedPtr<LandmarkFileSettings> & landmarkFileSettings, QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::LandmarkPreferenceDialog)
	, m_landmarkFileSettings(landmarkFileSettings)
{
	ui->setupUi(this);

	connect(ui->folderBrowseButton, &QAbstractButton::clicked, this, &LandmarkPreferenceDialog::OnFolderBrowseClicked);
	connect(ui->xmlBrowseButton, &QAbstractButton::clicked, this, &LandmarkPreferenceDialog::OnXMLBrowseClicked);
	connect(ui->filenameTextEdit, &QTextEdit::textChanged, this, &LandmarkPreferenceDialog::OnFilenameChanged);

	ui->folderTextEdit  ->setText(VisionApp::SettingsManager::Instance().value(TRAINING_LAST_FOLDER_PATH, "").toString());
	ui->xmlFileEdit     ->setText(VisionApp::SettingsManager::Instance().value(TRAINING_LAST_XML_PATH, "").toString());
	ui->filenameTextEdit->setText(VisionApp::SettingsManager::Instance().value(TRAINING_LAST_FILENAME, "").toString());
}

LandmarkPreferenceDialog::~LandmarkPreferenceDialog()
{
	delete ui;
}

void LandmarkPreferenceDialog::OnFolderBrowseClicked()
{
	m_landmarkFileSettings->m_folderPath = QFileDialog::getExistingDirectory(this);
	ui->folderTextEdit->setText(m_landmarkFileSettings->m_folderPath);
	VisionApp::SettingsManager::Instance().setValue(TRAINING_LAST_FOLDER_PATH, m_landmarkFileSettings->m_folderPath);
}

void LandmarkPreferenceDialog::OnXMLBrowseClicked()
{
	m_landmarkFileSettings->m_xmlPath = QFileDialog::getOpenFileName(this);
	ui->xmlFileEdit->setText(m_landmarkFileSettings->m_xmlPath);
	VisionApp::SettingsManager::Instance().setValue(TRAINING_LAST_XML_PATH, m_landmarkFileSettings->m_xmlPath);
}

void LandmarkPreferenceDialog::OnFilenameChanged()
{
	m_landmarkFileSettings->m_filename = ui->filenameTextEdit->toPlainText();
	VisionApp::SettingsManager::Instance().setValue(TRAINING_LAST_FILENAME, m_landmarkFileSettings->m_filename);
}
