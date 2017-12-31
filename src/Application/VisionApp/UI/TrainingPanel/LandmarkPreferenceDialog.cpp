#include "LandmarkPreferenceDialog.h"
#include "ui_LandmarkPreferenceDialog.h"

#include <QAbstractButton>
#include <QFileDialog>

#include "SettingsManager.h"

namespace
{
const QString TRAINING_LAST_FOLDER_PATH = "TRAINING_LAST_FOLDER_PATH";
const QString TRAINING_LAST_XML_PATH    = "TRAINING_LAST_XML_PATH";
const QString TRAINING_LAST_IMAGES_PATH = "TRAINING_LAST_IMAGES_PATH";
}

LandmarkPreferenceDialog::LandmarkPreferenceDialog(const SharedPtr<LandmarkFileSettings> & landmarkFileSettings, QWidget *parent)
	: QDialog(parent)
	, ui(new Ui::LandmarkPreferenceDialog)
	, m_landmarkFileSettings(landmarkFileSettings)
{
	ui->setupUi(this);

	connect(ui->folderBrowseButton, &QAbstractButton::clicked, this, &LandmarkPreferenceDialog::OnFolderBrowseClicked);
	connect(ui->xmlBrowseButton, &QAbstractButton::clicked, this, &LandmarkPreferenceDialog::OnXMLBrowseClicked);
	connect(ui->imagesPathFileBrowseButton, &QAbstractButton::clicked, this, &LandmarkPreferenceDialog::OnImagesPathClicked);
	connect(ui->xmlFileEdit, &QTextEdit::textChanged, this, &LandmarkPreferenceDialog::OnXMLPathChanged);
	connect(ui->imagesPathFileTextEdit, &QTextEdit::textChanged, this, &LandmarkPreferenceDialog::OnImagesPathChanged);
	connect(ui->folderTextEdit, &QTextEdit::textChanged, this, &LandmarkPreferenceDialog::OnFolderPathChanged);
	connect(ui->okButton, &QAbstractButton::clicked, this, &QDialog::close);

	m_landmarkFileSettings->m_folderPath = VisionApp::SettingsManager::Instance().value(TRAINING_LAST_FOLDER_PATH, "").toString();
	m_landmarkFileSettings->m_xmlPath = VisionApp::SettingsManager::Instance().value(TRAINING_LAST_XML_PATH, "").toString();
	m_landmarkFileSettings->m_imagesPath = VisionApp::SettingsManager::Instance().value(TRAINING_LAST_IMAGES_PATH, "").toString();

	ui->folderTextEdit        ->setText(m_landmarkFileSettings->m_folderPath);
	ui->xmlFileEdit           ->setText(m_landmarkFileSettings->m_xmlPath);
	ui->imagesPathFileTextEdit->setText(m_landmarkFileSettings->m_imagesPath);
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

void LandmarkPreferenceDialog::OnImagesPathClicked()
{
	m_landmarkFileSettings->m_imagesPath = QFileDialog::getOpenFileName(this);
	ui->imagesPathFileTextEdit->setText(m_landmarkFileSettings->m_imagesPath);
	VisionApp::SettingsManager::Instance().setValue(TRAINING_LAST_IMAGES_PATH, m_landmarkFileSettings->m_imagesPath);
}

void LandmarkPreferenceDialog::OnFolderPathChanged()
{
	m_landmarkFileSettings->m_folderPath = ui->folderTextEdit->toPlainText();
	VisionApp::SettingsManager::Instance().setValue(TRAINING_LAST_FOLDER_PATH, m_landmarkFileSettings->m_folderPath);
}

void LandmarkPreferenceDialog::OnXMLPathChanged()
{
	m_landmarkFileSettings->m_xmlPath = ui->xmlFileEdit->toPlainText();
	VisionApp::SettingsManager::Instance().setValue(TRAINING_LAST_XML_PATH, m_landmarkFileSettings->m_xmlPath);
}

void LandmarkPreferenceDialog::OnImagesPathChanged()
{
	m_landmarkFileSettings->m_imagesPath = ui->imagesPathFileTextEdit->toPlainText();
	VisionApp::SettingsManager::Instance().setValue(TRAINING_LAST_IMAGES_PATH, m_landmarkFileSettings->m_imagesPath);
}
