using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using DG.Tweening;

public class SlideyController : MonoBehaviour
{
    [SerializeField] Desk3Interaction desk3Interaction;
    [SerializeField] SlideyTile[,] tiles;
    [SerializeField] List<Sprite> sprites;
    [SerializeField] List<Transform> positions;
    [SerializeField] SlideyTile prefab;
    [SerializeField] AudioSource CompleteSound;
    [SerializeField] AudioSource SwooshSound;
    // Start is called before the first frame update
    void Start()
    {
        tiles = new SlideyTile[3,3];
        int x, y;
        int index = 0;
        foreach(var s in sprites)
        {
            x = 0;
            y = 0;
            int newIndex = index;
            while(newIndex > 2)
            {
                newIndex -= 3;
                y++;
            }
            while(newIndex > 0)
            {
                newIndex--;
                x++;
            }

            Vector3 tilePos = positions[x + (3 * y)].position;

            tiles[x, y] = Instantiate(prefab, tilePos,Quaternion.identity,transform);
            tiles[x, y].initalize(s,index,this);
            index++;
            if(index == 2)
            {
                index++;
            }
        }

        for(int i = 0; i < 1000; i++)
        {
            click(tiles[Random.Range(0, 3), Random.Range(0, 3)],true);
        }
    }

    public void click(SlideyTile tile, bool start)
    {
        SwooshSound.Play();
        int posx = 0;
        int posy = 0;
        for (int x = 0; x < 3; x++)
        {
            for (int y = 0; y < 3; y++)
            {
                if (tile == tiles[x, y])
                {
                    posx = x;
                    posy = y;
                    y = 10;
                    x = 10;
                }
            }
        }

        if (posx < 2)
        {
            if (check(posx + 1, posy))
            {
                tiles[posx + 1, posy] = tile;
                tiles[posx, posy] = null;
                if (!start)
                {
                    tile.transform.DOMove(positions[posx + 1 + (3 * posy)].position, 0.3f);
                    checkWin();
                }
                else
                {
                    tile.transform.position = positions[posx + 1 + (3 * posy)].position;
                }
                
                return;
            }
        }
        if (posx > 0)
        {
            if (check(posx - 1, posy))
            {
                tiles[posx - 1, posy] = tile;
                tiles[posx, posy] = null;
                if (!start)
                {
                    tile.transform.DOMove(positions[posx - 1 + (3 * posy)].position, 0.3f);
                    checkWin();
                }
                else
                {
                    tile.transform.position = positions[posx - 1 + (3 * posy)].position;
                }
                return;
            }
        }

        if (posy < 2)
        {
            if (check(posx, posy + 1))
            {
                tiles[posx, posy + 1] = tile;
                tiles[posx, posy] = null;
                if (!start)
                {
                    tile.transform.DOMove(positions[posx + (3 * (posy + 1))].position, 0.3f);
                    checkWin();
                }
                else
                {
                    tile.transform.position = positions[posx + (3 * (posy + 1))].position;
                }
                return;
            }
        }
        if (posy > 0)
        {
            if (check(posx, posy - 1))
            {
                tiles[posx, posy - 1] = tile;
                tiles[posx, posy] = null;
                
                if (!start)
                {
                    tile.transform.DOMove(positions[posx + (3 * (posy - 1))].position, 0.3f);
                    checkWin();
                }
                else
                {
                    tile.transform.position = positions[posx + (3 * (posy - 1))].position;
                }
                return;
            }
        }
    }

    bool check(int x, int y)
    {
        if (x < 3 && x >= 0 && y < 3 && y >= 0)
        {
            if (tiles[x, y] == null)
            {
                return true;
            }
        }
        return false;
    }

    void checkWin()
    {
        int pos = 0;
        for (int y = 0; y < 3;y++)
        {
            for (int x = 0; x < 3; x++)
            {
                if (tiles[x, y] != null)
                {
                    print(pos);
                    if (!tiles[x, y].checkPosition(pos))
                    {
                        return;
                    }
                }
                pos++;
            }
        }
        print("QDGHSADFGSWDFGHWRTHWAEFGHSFDGHSFGHJWSRHJ");
        CompleteSound.Play();
        StartCoroutine(win());
    }

    IEnumerator win()
    {
        yield return new WaitForSeconds(0.7f);
        desk3Interaction.completePuzzle();
    }


}
