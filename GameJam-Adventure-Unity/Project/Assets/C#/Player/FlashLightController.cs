using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class FlashLightController : MonoBehaviour
{

    [SerializeField] GameObject torch;
    [SerializeField] List<Sprite> sprites;
    [SerializeField] Image sprite;
    bool active = false;
    private float timer = 10f;
    private float cooldown = 1f;


    void Update()
    {
        if(active)
        {
            timer -= Time.deltaTime;
        }
        else
        {
            if (cooldown > 1f)
            {
                timer += Time.deltaTime;
            }
            else
            {
                cooldown += Time.deltaTime;
            }
        }


        if (Input.GetKeyDown(KeyCode.F))
        {
            if (torch.activeSelf)
            {
                turnOff();
            }
            else
            {
                if(timer>0.2)
                turnOn();
            }
        }

        if(timer >= 7f)
        {
            sprite.sprite = sprites[0];
        }
        else if(timer >= 3f)
        {
            sprite.sprite = sprites[1];
        }
        else if(timer > 0.5f)
        {
            sprite.sprite = sprites[2];
        }
        else
        {
            sprite.sprite = sprites[3];
        }



        if (timer <= 0f)
        {
            turnOff();
            cooldown = 0f;
            timer = 0.1f;
        }
    }

    private void turnOff()
    {
        active = false;
        torch.SetActive(false);
    }

    private void turnOn()
    {
        active = true;
        torch.SetActive(true);
    }
}
