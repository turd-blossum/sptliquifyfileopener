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
#include <vector>




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
                std::wstring ws1(str->Data()); //casts string platform to wstring for find and substring
                basic_string <char>::size_type indexPGA;
                indexPGA = ws1.find(L"PGA ground motion: ");
                basic_string <char>::size_type indexEPS;
                indexEPS = ws1.find(L"ε=[2.5,∞)");
                basic_string <char>::size_type indexEPSend;
                indexEPSend = ws1.find(L"Principal Sources");
                std::wstring wsPGA(ws1.substr(indexPGA + 19, 10));
                double PGA;
                vector <double> rRup;
                vector <double> cdistance;
                vector <double> Mag;
                vector <double> EAll;
                vector <double> E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11;


                PGA = std::stod(wsPGA);
                //std::wstring wsrRup(ws1.substr(indexEPS + 14, 3));
               /* rRup.push_back(std::stod(wsrRup));
                int rupindex=indexEPS+14+86;
          */
          // std::string::size_type found = wsrRup.find(L"\t");

                basic_string <char>::size_type writebegin;
                writebegin = indexEPS + 10;
                basic_string <char>::size_type writeend;

                //std::wstring substr1 = ws1.substr(writebegin,10);
                while (writebegin < indexEPSend) {
                    writeend = ws1.find(L"\t", writebegin);
                    std::wstring wsrdist(ws1.substr(writebegin, writeend - writebegin));
                    cdistance.push_back(std::stod(wsrdist));
                    writebegin = writeend + 1;
                    writeend = ws1.find(L"\t", writebegin);
                    std::wstring wsrRup(ws1.substr(writebegin, writeend - writebegin));
                    rRup.push_back(std::stod(wsrRup));
                    writebegin = writeend + 1;
                    writeend = ws1.find(L"\t", writebegin);
                    std::wstring wsrMag(ws1.substr(writebegin, writeend - writebegin));
                    Mag.push_back(std::stod(wsrMag));
                    writebegin = writeend + 1;
                    writeend = ws1.find(L"\t", writebegin);
                    std::wstring wsrEAll(ws1.substr(writebegin, writeend - writebegin));
                    EAll.push_back(std::stod(wsrEAll));
                    writebegin = writeend + 1;
                    writeend = ws1.find(L"\t", writebegin);
                    std::wstring wsrE1(ws1.substr(writebegin, writeend - writebegin));
                    E1.push_back(std::stod(wsrE1));
                    writebegin = writeend + 1;
                    writeend = ws1.find(L"\t", writebegin);
                    std::wstring wsrE2(ws1.substr(writebegin, writeend - writebegin));
                    E2.push_back(std::stod(wsrE2));
                    writebegin = writeend + 1;
                    writeend = ws1.find(L"\t", writebegin);
                    std::wstring wsrE3(ws1.substr(writebegin, writeend - writebegin));
                    E3.push_back(std::stod(wsrE3));
                    writebegin = writeend + 1;
                    writeend = ws1.find(L"\t", writebegin);
                    std::wstring wsrE4(ws1.substr(writebegin, writeend - writebegin));
                    E4.push_back(std::stod(wsrE4));
                    writebegin = writeend + 1;
                    writeend = ws1.find(L"\t", writebegin);
                    std::wstring wsrE5(ws1.substr(writebegin, writeend - writebegin));
                    E5.push_back(std::stod(wsrE5));
                    writebegin = writeend + 1;
                    writeend = ws1.find(L"\t", writebegin);
                    std::wstring wsrE6(ws1.substr(writebegin, writeend - writebegin));
                    E6.push_back(std::stod(wsrE6));
                    writebegin = writeend + 1;
                    writeend = ws1.find(L"\t", writebegin);
                    std::wstring wsrE7(ws1.substr(writebegin, writeend - writebegin));
                    E7.push_back(std::stod(wsrE7));
                    writebegin = writeend + 1;
                    writeend = ws1.find(L"\t", writebegin);
                    std::wstring wsrE8(ws1.substr(writebegin, writeend - writebegin));
                    E8.push_back(std::stod(wsrE8));
                    writebegin = writeend + 1;
                    writeend = ws1.find(L"\t", writebegin);
                    std::wstring wsrE9(ws1.substr(writebegin, writeend - writebegin));
                    E9.push_back(std::stod(wsrE9));
                    writebegin = writeend + 1;
                    writeend = ws1.find(L"\t", writebegin);
                    std::wstring wsrE10(ws1.substr(writebegin, writeend - writebegin));
                    E10.push_back(std::stod(wsrE10));
                    writebegin = writeend + 1;
                    writeend = ws1.find(L"\t", writebegin);
                    std::wstring wsrE11(ws1.substr(writebegin, writeend - writebegin));
                    E11.push_back(std::stod(wsrE11));
                    writeend = ws1.find(L"\n", writebegin);
                    writebegin = writeend + 1;

                }



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
