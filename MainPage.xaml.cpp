//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
// new addons
// ensure these are all added
// must update to windows 11 and get newest version for windows debugger tools
#include <ppltasks.h>
#include <string>
#include <memory>


using namespace Windows::Storage;
using namespace Windows::Storage::Streams;
using namespace Windows::Storage::Pickers;
using namespace Platform::Collections;
using namespace concurrency;
using namespace std;
using namespace BlankAppUniversalWindowsApplication;
//end new addonns
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

String^ str;

//public ref class FileOpenPicker sealed;

// The Blank Page item template is documented at https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409

MainPage::MainPage()
{
	InitializeComponent();
}


void BlankAppUniversalWindowsApplication::MainPage::Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{

    // Clear previous returned file name, if it exists, between iterations of this scenario
    OutputTextBlock->Text = "Loading?...";

    //creates the file picker object as a pointer 
    FileOpenPicker^ openPicker = ref new FileOpenPicker();
    openPicker->ViewMode = PickerViewMode::Thumbnail;
    // chooses the start location in the file explorer. options are documents downloads pictures etc. default file locations
    openPicker->SuggestedStartLocation = PickerLocationId::DocumentsLibrary;
    // filters for .txt files. for csv use ".csv" 
    openPicker->FileTypeFilter->Append(".txt");


    create_task(openPicker->PickSingleFileAsync()).then([this](StorageFile^ file)
        {
            if (file)
            {
                create_task(file->OpenAsync(FileAccessMode::Read)).then([file](IRandomAccessStream^ stream) //takes the info as a IRandomAcess Stream 
                    {
                        UINT64 size = stream->Size;
                        IInputStream^ inputStream = stream->GetInputStreamAt(0);
                        auto dataReader = ref new DataReader(inputStream);
                        
                        create_task(dataReader->LoadAsync(size)).then([file, dataReader](unsigned int numBytesLoaded) // changes the datareader variable to a string
                            {
                                
                                String^ streamText = dataReader->ReadString(numBytesLoaded);
                                str = streamText;
                                
                            });

                    });
                
            }
            else
            {
                OutputTextBlock->Text = "Operation cancelled.";
            }
        });

	
}


void BlankAppUniversalWindowsApplication::MainPage::updatebutton2(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
    OutputTextBlock->Text = str->ToString();
}
