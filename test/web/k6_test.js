import grpc from 'k6/net/grpc';
import {check, sleep} from 'k6';

const client = new grpc.Client();
client.load(['/home/fumedesk/projects/cpp/anezkasearch/protos'], 'AnezkaSearch.proto');

export default () => {
    client.connect('0.0.0.0:50051', {
        plaintext: true,
        reflect: false,
        timeout: 2000
    });

    const data_1 = {
        "indexes": [{"s_ind": "book_1"}, {"s_ind": "book_2"}, {"s_ind": "book_3"}], "key": "worda"
    };

    const response_1 = client.invoke('anezkasearch.IndexStorageService/InsertIndex', data_1);
    check(response_1, {
        'status is OK 1': (r) => r && r.status === grpc.StatusOK,
    });
    console.log(response_1.message);

    const data_2 = {"key": "worda"};
    const response_2 = client.invoke('anezkasearch.IndexStorageService/GetIndexes', data_2);
    check(response_2, {
        'status is OK 2': (r) => r && r.status === grpc.StatusOK,
        'answer is correct 2':
            response_2.message['indexes'][0]["sInd"] === "book_1"
            && response_2.message['indexes'][1]["sInd"] === "book_2"
            && response_2.message['indexes'][2]["sInd"] === "book_3",
    });
    console.log(response_2.message);

    const data_3 = {
        "indexes": [{"s_ind": "book_2"}, {"s_ind": "book_3"}], "key": "wordb"
    };

    const response_3 = client.invoke('anezkasearch.IndexStorageService/InsertIndex', data_3);
    check(response_3, {
        'status is OK 3': (r) => r && r.status === grpc.StatusOK,
    });
    console.log(response_3.message);

    const response_4 = client.invoke('anezkasearch.SearchService/SearchIndex', {"text": "worda wordb"});
    check(response_4, {
        'status is OK 4': (r) => r && r.status === grpc.StatusOK,
        'answer is correct 4': response_4.message['indexes'][0]["sInd"] === "book_2"
            && response_4.message['indexes'][1]["sInd"] === "book_3",
    });
    console.log(response_4.message);
};








