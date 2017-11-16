# ffm-weight-server

## A better way looking into detail of libffm weights

When running ffm, many have issues weighting how samples influence their model. A better approach is to look into detail of weights.
This Project is to print libffm weight through json format. You can get json through http post request.

## Install

1. install httpcpp refer to https://github.com/panuph/httpcpp
2. make 
3. run ./weight-server port


## Specification 

1. Prepare libffm model, and put your trained to Directory:  data/training.model
2. Send post request (e.g. curl http://serverip:port -d "0 0:15:1 1:47:1 2:2:1 2:2104:1 2:2105:1 2:2115:1 3:132570:1 3:132571:1 3:70143:1 4:485:1 5:9:1 5:2110:1 5:66463:1 5:132501:1 6:576776:1 6:576777:1 7:143123:1")
3. You are suppose to get the json answer. For example:

```json
{
     "vivj_info":    [{
             "i_idx":    15,
             "i_field":  0,
             "i_val":    1,
             "j_idx":    47,
             "j_field":  1,
             "j_val":    1,
             "weight":   -1.003816
         }, {
             "i_idx":    15,
             "i_field":  0,
             "i_val":    1,
             "j_idx":    2,
             "j_field":  2,
             "j_val":    1,
             "weight":   -1.064474
         }, {
             "i_idx":    15,
             "i_field":  0,
             "i_val":    1,
             "j_idx":    2104,
             "j_field":  2,
             "j_val":    1,
             "weight":   -1.136909
         }, {
             "i_idx":    15,
             "i_field":  0,
             "i_val":    1,
		...  ...
```


# import DETAIL

1. import source libffm code from https://github/guestwalk/libffm
2. import server code from https://github.com/panuph/httpcpp
3. import cJson parser from Dave Gamble
