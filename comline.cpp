#include <iostream>
#include <string>
#include <vector>
#include <ctype.h>
using namespace std;

/*
 * 练习 7.15
 * 增加选项 `-t` （打开计时器）以及选项 `-b` （提供 bufsize 实参）的处理，并且也要确保同时更改 `usage()`，例如：
 *      `prog -t -b 512 data0`
 */

const char *const program_name = "comline";
const char *const program_version = "version 0.02 (24/Aug/23)";
const char *const compile_date = __DATE__;

inline void usage( int exit_value = 0 )
{
    // 输出一个格式化的用法信息
    // 并用 exit_value 退出...
    cout << "usage:\n"
        << program_name << " "
        // 新增 `-t`。
        << "[-d] [-t] [-h] [-v]\n\t"
        // 新增 `-t` 结束。
        // 新增 `-b`。
        << "[-o output_file] [-l limit] [-b bufsize]\n\t"
        // 新增 `-b` 结束。
        << "file_name\n\t[file_name [file_name [ ... ]]]\n\n"
        << "where [] indicates optional option: \n\n\t"
        << "-h: help.\n\t\t"
        << "generates this message and exits\n\n\t"
        << "-v: version.\n\t\t"
        << "prints version information and exits\n\n\t"
        << "-d: debug.\n\t\tturns debugging on\n\n\t"
        // 新增计时器的描述。
        << "-t: timer.\n\t\tturns timer on.\n\n\t"
        // 新增计时器的描述结束。
        << "-l limit\n\t\t"
        << "limit must be a non-negative integer\n\n\t"
        // 新增 bufsize 的描述。
        << "-b bufsize\n\t\t"
        << "buffer size must be a non-negative integer\n\n\t"
        // 新增 bufsize 的描述结束。
        << "-o ofile\n\t\t"
        << "file within which to write out results\n\t\t"
        << "by default, results written to standard output \n\n"
        << "file_name\n\t\t"
        << "the name of the actual file to process\n\t\t"
        << "at least one file_name is required --\n\t\t"
        << "any number may be specified\n\n"
        << "examples:\n\t\t"
        << "$ command chapter7.doc\n\t\t"
        << "$ command -d -l 1024 -o test_7_8 "
        << "chapter7.doc chapter8.doc\n\n";

    // 新增程序正常退出情况反馈。
    if (exit_value == 0) {
        cout << endl << "The program exits successfully by exit()." << endl;
        exit( exit_value );
    }
    // 新增程序正常退出情况反馈结束。

    // 新增程序非正常退出情况反馈。
    cout << endl << "The program exits with returned value " << exit_value << " by exit()." << endl;
    // 新增程序非正常退出情况反馈结束。
    exit( exit_value );
}
int main( int argc, char* argv[] )
{
    bool debug_on = false;
    bool ofile_on = false;
    bool limit_on = false;
    // 新增计时器开关。
    bool timer_on = false;
    // 新增计时器开关结束。
    // 新增 bufsize 开关。
    bool bufsize_on = false;
    // 新增 bufsize 开关结束。
    
    int limit = -1;
    // 新增 bufsize 变量。
    int bufsize = -1;
    // 新增 bufsize 变量结束。

    string ofile;
    vector<string> file_names;
    cout << "illustration of handling command line arguments:\n"
        << "argc: " << argc << endl;
    for ( int ix = 1; ix < argc; ++ix )
    {
        cout << "argv[ " << ix << " ]: "
        << argv[ ix ] << endl;
        char *pchar = argv[ ix ];
        switch ( pchar[ 0 ] )
        {
        case '-':
            {
                cout << "case \'-\' found\n";
                switch( pchar[ 1 ] )
                {
                case 'd':
                    cout << "-d found: "
                        << "debugging turned on\n";
                    debug_on = true;
                    break;
                // 新增计时器开关处理。
                case 't':
                    cout << "-t found: "
                        << "timer turned on.\n";
                    timer_on = true;
                    break;
                // 新增计时器开关处理结束。
                case 'v':
                    cout << "-v found: "
                        << "version info displayed\n";
                    cout << program_name
                        << " :: "
                        << program_version
                        << " compiled on "
                        << compile_date
                        // 新增程序正常退出情况反馈。
                        << endl << endl
                        << "The program exits successfully by -v option."
                        // 新增程序正常退出情况反馈结束。
                        << endl
                        ;
                    return 0;
                case 'h':
                    cout << "-h found: "
                        << "help information\n";

                    // 这里没必要用 break 了, usage() 可以退出
                    usage();
                case 'o':
                    cout << "-o found: output file\n";
                    ofile_on = true;
                    break;
                case 'l':
                    cout << "-l found: "
                        << "resource limit\n";
                    limit_on = true;
                    break;
                // 新增 bufsize 开关处理。
                case 'b':
                    cout << "-b found: "
                        << "buffer size limit\n";
                    bufsize_on = true;
                    break;
                // 新增 bufsize 开关处理结束。
                default:    // 或文件名
                    cout << program_name
                        << " : error : "
                        << "unrecognized option: - "
                        << pchar << "\n\n";
                    // 这里没必要用 break 了, usage() 可以退出
                    // 错误的选项值，返回 -1 退出。
                    usage( -1 );
                }
                break;
            }
        default: // 或文件名
            cout << "default nonhyphen argument: "
                << pchar << endl;
            if ( ofile_on ) {
                ofile_on = false;
                ofile = pchar;
            }
            else if ( limit_on ) {
                limit_on = false;
                limit = atoi( pchar );
                if ( limit < 0 ) {
                    cout << program_name
                        << " : error : "
                        << "negative value for limit.\n\n";
                    // 限制值为负，返回 -2 退出。
                    usage( -2 );
                }
            // 新增 bufsize 处理。
            } else if( bufsize_on ) {
                bufsize_on = false;
                bufsize = atoi( pchar );
                if ( bufsize < 0 ) {
                    cout << program_name
                        << " : error : "
                        << "negative value for buffer size.\n\n";
                    // bufsize 为负，返回 -3 退出。
                    usage( -3 );
                }
                
            }
            // 新增 bufsize 处理结束。
            else
                file_names.push_back( string( pchar ));
            break;
        }
    }
    if ( file_names.empty() ) {
        cout << program_name
            << " : error : "
            << "no file specified for processing.\n\n";
        // 未指定文件名，返回 -4 退出。
        usage( -4 );
    }
    if ( limit != -1 )
        cout << "User-specified limit: "
            << limit << endl;
    // 新增 bufsize 值显示。
    if ( bufsize != -1 ) {
        cout << "User-specified buffer size: "
            << bufsize << endl;
    }
    
    // 新增 bufsize 值显示结束。
    if ( ! ofile.empty() )
        cout << "User-specified output file: "
            << ofile << endl;
    
    cout << (file_names.size() == 1 ? "File " : "Files ")
        << "to be processed are the following:\n";
    for ( int inx = 0; inx < file_names.size(); ++inx )
        cout << "\t" << file_names[ inx ] << endl;

    // 新增程序正常退出情况反馈。
    cout << endl << "The program exits successfully." << endl;
    return 0;
    // 新增程序正常退出情况反馈结束。
}
