using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;
using TMPro;
using Unity.VisualScripting;

public class SearchController : MonoBehaviour
{
    [SerializeField] Desk2Interaction desk2Interaction;
    [SerializeField] List<TextMeshProUGUI> textList;
    [SerializeField] List<TextMeshProUGUI> correctList;
    [SerializeField] List<int> intList;
    [SerializeField] List<Image> topImgs;
    [SerializeField] AudioSource CompleteSound;
    [SerializeField] AudioSource FaileSound;
    [SerializeField] AudioSource ClickSound;
    private List<int> indexList;

    private int nextNumberIndex;
    private int nextCorrectIndex = 0;

    [SerializeField] Sprite correctSprite;
    [SerializeField] Sprite nextSprite;

    private void Start()
    {
        startGame();
    }
    void startGame()
    {
        nextCorrectIndex = 0;
        foreach (var item in topImgs)
        {
            item.sprite = nextSprite;
        }

        indexList = new List<int>();
        //find correct index list
        for (int i = 0; i < 4; i++)
        {
            int x;
            do
            {
                x = Random.Range(0, 44);
            } while (indexList.Contains(x));
            indexList.Add(x);
        }
        nextNumberIndex = indexList[0];
        int index = 0;
        intList = new List<int>();
        foreach (var item in textList)
        {
            //find number
            int number;
            do
            {
                number = Random.Range(0, 99);
            } while (intList.Contains(number));

            intList.Add(number);

            //form string
            string str = number.ToString();
            if (number < 10)
            {
                str = "0" + str;
            }

            //check if number is correct
            if (indexList.Contains(index))
            {
                correctList[indexList.IndexOf(index)].text = str;
            }

            item.text = str;

            item.transform.parent.GetComponent<NumberClick>().index = index;

            index++;
        }
    }
    public void numberClick(int index)
    {
        ClickSound.Play();
        if (nextNumberIndex == index)
        {
            topImgs[nextCorrectIndex].sprite = correctSprite;
            nextCorrectIndex++;
            if (nextCorrectIndex > 3)
            {
                CompleteSound.Play();
                StartCoroutine(win());
            }
            else
            {
                nextNumberIndex = indexList[nextCorrectIndex];
            }
        }
        else
        {
            FaileSound.Play();
            startGame();
        }
    }

    IEnumerator win()
    {
        yield return new WaitForSeconds(0.7f);
        desk2Interaction.completePuzzle();
    }

}
