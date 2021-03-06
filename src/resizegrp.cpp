#include "resizegrp.h"
#include <QtGui>

ResizeGrp::ResizeGrp(QWidget *parent)
  : QWidget(parent)
{
  resize = new QGroupBox(tr("Resize"));
  QVBoxLayout* layout = new QVBoxLayout(this);
  setLayout(layout);
  layout->addWidget(resize);
  widthEdit = new QSpinBox();
  widthEdit->setRange(1, 100);
  widthEdit->setValue(100);
  widthEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);
  
  heightEdit = new QSpinBox();
  heightEdit->setRange(1, 100);
  heightEdit->setValue(100);
  heightEdit->setButtonSymbols(QAbstractSpinBox::NoButtons);

  xOffset = new QSpinBox();
  xOffset->setValue(0);
  
  yOffset = new QSpinBox();
  yOffset->setValue(0);

  percent = new QCheckBox(tr("Interpret Percent"));
  fixedProportion = new QCheckBox(tr("Keep Ratio"));
  onlySmaller = new QCheckBox(tr("Resize smaller img only"));
  onlyGreater = new QCheckBox(tr("Resize greater img only"));

  connect(percent, SIGNAL(stateChanged(int)), this,
          SLOT(isPercent(int)));
  percent->setCheckState(Qt::Checked);

  connect(fixedProportion, SIGNAL(stateChanged(int)), this,
          SLOT(fixedPropo(int)));
  fixedProportion->setCheckState(Qt::Checked);

  connect(widthEdit, SIGNAL(valueChanged(int)), this,
          SLOT(keepRatio(int)));
  connect(heightEdit, SIGNAL(valueChanged(int)), this,
          SLOT(keepRatio(int)));
  
  filterType << "Auto" << "Lanczos" << "Mitchell";
  filterBox = new QComboBox;
  filterBox->addItems(filterType);
  filterBox->setSizeAdjustPolicy(QComboBox::AdjustToContents);
  filterBox->setCurrentIndex(0);
 
  QFormLayout *lineLayout = new QFormLayout;
  lineLayout->insertRow(0, tr("Width"), widthEdit);
  lineLayout->insertRow(1, tr("Height"), heightEdit);
  lineLayout->insertRow(2, tr("X offset"), xOffset);
  lineLayout->insertRow(3, tr("Y offset"), yOffset);
  lineLayout->insertRow(4, tr("Resize Filter"), filterBox);
  resizeGrid = new QGridLayout;

  resizeGrid->addLayout(lineLayout, 0, 0, 5, 2);
  resizeGrid->addWidget(percent, 0, 2, 1, 1);
  resizeGrid->addWidget(fixedProportion, 1, 2, 1, 1);
  resizeGrid->addWidget(onlySmaller, 2, 2, 1, 1);
  resizeGrid->addWidget(onlyGreater, 3, 2, 1, 1);
  

  resize->setLayout(resizeGrid);
  resize->adjustSize();
}

// Fixme: dirty code?
void ResizeGrp::isPercent(int checked)
{
  if (checked == Qt::Unchecked) {
    widthEdit->setRange(1, 100000);
    heightEdit->setRange(1, 100000);
    widthEdit->setValue(1000);
    heightEdit->setValue(1000);
    onlySmaller->setEnabled(true);
    onlyGreater->setEnabled(true);
  } else if (checked == Qt::Checked) {
    widthEdit->setRange(1, 100);
    heightEdit->setRange(1, 100);
    widthEdit->setValue(100);
    heightEdit->setValue(100);
    onlySmaller->setDisabled(true);
    onlyGreater->setDisabled(true);
  }
}

void ResizeGrp::fixedPropo(int checked)
{
  if (checked == Qt::Checked && percent->isChecked() ) {
    if (widthEdit->value() > heightEdit->value())
      heightEdit->setValue(widthEdit->value());
    else
      widthEdit->setValue(heightEdit->value());
  }
}

void ResizeGrp::keepRatio(int size)
{
  if (fixedProportion->isChecked() && percent->isChecked()) {
  if (widthEdit->value() != size)
    widthEdit->setValue(size);
  else
    heightEdit->setValue(size);
  }
}

void ResizeGrp::resizeOption(void)
{
  QString curWidth, curHeight, curXOff, curYOff;
  curWidth = QString::number(widthEdit->value());
  curHeight = QString::number(heightEdit->value());
  
  if (xOffset->value() >= 0)
    curXOff = QString("+");
  if (yOffset->value() >= 0)
    curYOff = QString("+");
  curXOff += QString::number(xOffset->value());
  curYOff += QString::number(yOffset->value());

  
    QString geometry = QString("%1x%2%3%4").arg(curWidth).arg(curHeight).arg(curXOff).arg(curYOff);
    
  if (percent->isChecked()) 
    geometry += '%';
  if (!fixedProportion->isChecked())
    geometry += '!';
  if (onlySmaller->isChecked() && onlySmaller->isEnabled())
    geometry += '<';
  if (onlyGreater->isChecked() && onlyGreater->isEnabled())
    geometry += '>';

  QApplication::setOrganizationName("Sd44 Soft");
  QApplication::setOrganizationDomain("sd44.is-programmer.com");
  QApplication::setApplicationName("Super Img Batcher");
  QSettings settings;

  if (geometry != "100x100+0+0%")
    settings.setValue("resize/geometry", geometry);
  if (filterBox->currentIndex() != 0)
    settings.setValue("resize/filterBox", filterBox->currentIndex());
}
  
