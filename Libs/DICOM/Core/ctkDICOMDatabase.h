/*=========================================================================

  Library:   CTK

  Copyright (c) 2010

  Licensed under the Apache License, Version 2.0 (the "License");
  you may not use this file except in compliance with the License.
  You may obtain a copy of the License at

      http://www.commontk.org/LICENSE

  Unless required by applicable law or agreed to in writing, software
  distributed under the License is distributed on an "AS IS" BASIS,
  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  See the License for the specific language governing permissions and
  limitations under the License.

=========================================================================*/

#ifndef __ctkDICOMDatabase_h
#define __ctkDICOMDatabase_h

// Qt includes 
#include <QObject>
#include <QStringList>
#include <QSqlDatabase>

#include "ctkDICOMCoreExport.h"

class ctkDICOMDatabasePrivate;
class DcmDataset;

class CTK_DICOM_CORE_EXPORT ctkDICOMDatabase : public QObject
{
  Q_OBJECT
public:
  explicit ctkDICOMDatabase(QObject *parent = 0);
  explicit ctkDICOMDatabase(QString databaseFile);
  virtual ~ctkDICOMDatabase();

  const QSqlDatabase& database() const;
  const QString lastError() const;
  const QString databaseFilename() const;
  const QString databaseDirectory() const;
  bool isInMemory() const;

  ///
  /// open the SQLite database in @param databaseFile . If the file does not
  /// exist, a new database is created and initialized with the
  /// default schema
  ///
  /// @param databaseFile TODO
  /// @param connectionName TODO
  Q_INVOKABLE virtual void openDatabase(const QString databaseFile, const QString& connectionName = "DICOM-DB" );

  ///
  /// close the database. It must not be used afterwards.
  Q_INVOKABLE void closeDatabase();
  ///
  /// delete all data and reinitialize the database.
  Q_INVOKABLE bool initializeDatabase(const char* schemaFile = ":/dicom/dicom-schema.sql");

  ///
  /// \brief database accessors
  Q_INVOKABLE QStringList studiesForPatient (QString patientUID);
  Q_INVOKABLE QStringList seriesForStudy (QString studyUID);
  Q_INVOKABLE QStringList filesForSeries (QString seriesUID);

  ///
  /// \brief load the header from a file and allow access to elements
  Q_INVOKABLE void loadInstanceHeader (QString sopInstanceUID);
  Q_INVOKABLE void loadFileHeader (QString fileName);
  Q_INVOKABLE QStringList headerKeys ();
  Q_INVOKABLE QString headerValue (QString key);

  /**
   * Will create an entry in the appropriate tables for this dataset.
   */
  // void insert ( DcmDataset* dataset, QString filename );
  /**
   * Insert into the database if not already exsting.
   */
  void insert ( DcmDataset *dataset, bool storeFile = true, bool createThumbnail = true );
  /***
    * Helper method: get the path that should be used to store this  image.
    */
  QString pathForDataset( DcmDataset *dataset);

signals:
  void databaseChanged();

protected:
  QScopedPointer<ctkDICOMDatabasePrivate> d_ptr;



private:
  Q_DECLARE_PRIVATE(ctkDICOMDatabase);
  Q_DISABLE_COPY(ctkDICOMDatabase);
};

#endif
