#include "enciph.hpp"
#include "../command.hpp"

namespace dla
{
    void enciph::verify(command* cmd)
    {
        iflag ix; if (ix.doesFail(cmd)) return;
        oflag ox; if (ox.doesFail(cmd)) return;
        kflag kx; if (kx.doesFail(cmd)) return;
        mflag mx; if (mx.doesFail(cmd)) return;
    }

    void enciph::exec(command* cmd)
    {
        std::string mode = cmd->getFlag("-m");
        char type = mode.at(0);
        int iterations = std::stoi(mode.substr(1,mode.size()-1));

        boost::filesystem::path kfile(cmd->getFlag("-k"));
        boost::filesystem::ifstream kfs{kfile};
        std::string rawkey;
        std::getline(kfs, rawkey);
        int partition = rawkey.find(":");
        std::string keymeta = rawkey.substr(0, partition - 1);
        std::string b64keydata = rawkey.substr(partition + 2);
        std::string binkeydata = boost::beast::detail::base64_decode(b64keydata);
        std::vector<uint8_t> keydata(binkeydata.begin(), binkeydata.end());

        std::string keymode = keymeta.substr(keymeta.find("/") + 1);
        keymode = keymode.substr(0, keymeta.find("/"));
        char group = keymode.at(0);
        int size = std::stoi(keymode.substr(1,keymode.size()-1));

        boost::filesystem::path ifile(cmd->getFlag("-i"));
        boost::filesystem::ifstream ifs{ifile};
        std::stringstream rawmats;
        rawmats << ifs.rdbuf();
        std::string rawmat = rawmats.str();
        std::vector<uint8_t> matdata(rawmat.begin(), rawmat.end());

        vmatrix key = matrix<item_a>(0, 0);
        vmatrix mat = matrix<item_a>(0, 0);

        switch (group)
        {
            case 'A':
                key = importMatrixOfSize<item_a, set_a1, set_a2, set_a3, set_a4>(size, keydata);
                mat = buildMatrixOfSize<item_a, set_a1, set_a2, set_a3, set_a4>(size, matdata);
                break;
            case 'B':
                key = importMatrixOfSize<item_b, set_b1, set_b2, set_b3, set_b4>(size, keydata);
                mat = buildMatrixOfSize<item_b, set_b1, set_b2, set_b3, set_b4>(size, matdata);
                break;
            case 'C':
                key = importMatrixOfSize<item_c, set_c1, set_c2, set_c3, set_c4>(size, keydata);
                mat = buildMatrixOfSize<item_c, set_c1, set_c2, set_c3, set_c4>(size, matdata);
                break;
            case 'D':
                key = importMatrixOfSize<item_d, set_d1, set_d2, set_d3, set_d4>(size, keydata);
                mat = buildMatrixOfSize<item_d, set_d1, set_d2, set_d3, set_d4>(size, matdata);
                break;
            default:
                cmd->fail("Group '" + std::string(1, group) + "' is not valid");
                return;
        }

        salt(mat);

        switch (type)
        {
            case 'q':
            case 'Q':
                for (int i = 0; i < iterations; i++)
                {
                    mat = mat / key;
                }
            case 'p':
            case 'P':
                for (int i = 0; i < iterations; i++)
                {
                    mat = mat * key;
                }
        }

        std::vector<uint8_t> ctext = getdata(mat);        
        
        boost::filesystem::path ofile(cmd->getFlag("-o"));
        boost::filesystem::ofstream ofs{ofile};

        ofs << std::string(ctext.begin(), ctext.end());

        return;
    }
}