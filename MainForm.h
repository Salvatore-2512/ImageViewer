#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Collections::Generic;

public ref class MainForm : public Form {

public:
    MainForm() {
        InitializeComponent();
        LoadImages("C:/Users/gunja/source/repos/ImageViewer/images");  // Change this path as needed
        if (imagePaths->Count > 0)
            ShowImage();
    }

private:
    PictureBox^ pictureBox;
    Button^ nextButton;
    Button^ prevButton;

    List<String^>^ imagePaths = gcnew List<String^>();
    int currentIndex = 0;

    void InitializeComponent() {
        this->Text = "Image Viewer";
        this->Width = 800;
        this->Height = 600;

        // Create panel for buttons at the bottom
        Panel^ buttonPanel = gcnew Panel();
        buttonPanel->Height = 50;
        buttonPanel->Dock = DockStyle::Bottom;
        buttonPanel->BackColor = System::Drawing::Color::LightGray;
        this->Controls->Add(buttonPanel);

        // Create PictureBox
        pictureBox = gcnew PictureBox();
        pictureBox->Dock = DockStyle::Fill;
        pictureBox->SizeMode = PictureBoxSizeMode::Zoom;
        this->Controls->Add(pictureBox); 

        // Create Previous Button
        prevButton = gcnew Button();
        prevButton->Text = "Previous";
        prevButton->Width = 100;
        prevButton->Height = 30;
        prevButton->Left = 10;
        prevButton->Top = 10;
        prevButton->Click += gcnew EventHandler(this, &MainForm::PrevImage);
        buttonPanel->Controls->Add(prevButton);

        // Create Next Button
        nextButton = gcnew Button();
        nextButton->Text = "Next";
        nextButton->Width = 100;
        nextButton->Height = 30;
        nextButton->Left = 120;
        nextButton->Top = 10;
        nextButton->Click += gcnew EventHandler(this, &MainForm::NextImage);
        buttonPanel->Controls->Add(nextButton);
    }

    void LoadImages(String^ folderPath) {
        if (!Directory::Exists(folderPath)) {
            MessageBox::Show("Image folder not found: " + folderPath);
            return;
        }

        array<String^>^ files = Directory::GetFiles(folderPath);
        for each (String ^ file in files) {
            String^ ext = Path::GetExtension(file)->ToLower();
            if (ext == ".jpg" || ext == ".png" || ext == ".bmp")
                imagePaths->Add(file);
        }
    }

    void ShowImage() {
        if (imagePaths->Count == 0) return;
        pictureBox->Image = Image::FromFile(imagePaths[currentIndex]);
    }

    void NextImage(Object^ sender, EventArgs^ e) {
        if (imagePaths->Count == 0) return;
        currentIndex = (currentIndex + 1) % imagePaths->Count;
        ShowImage();
    }

    void PrevImage(Object^ sender, EventArgs^ e) {
        if (imagePaths->Count == 0) return;
        currentIndex = (currentIndex - 1 + imagePaths->Count) % imagePaths->Count;
        ShowImage();
    }
};