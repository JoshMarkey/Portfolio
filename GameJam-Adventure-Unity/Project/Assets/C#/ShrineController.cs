using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class ShrineController : MonoBehaviour
{
    [SerializeField] GameObject cross;
    [SerializeField] Animation anim;
    [SerializeField] GameObject pressE;
    [SerializeField] AudioSource portalSound;
    [SerializeField] GameObject light;
    [SerializeField] GameObject note;
    ShrineDontDestroy dontDestroy;
    bool animationCheck = false;
    bool animationfinished = false;
    bool placed = false;
    bool canPlace = false;
    bool lightBool = false;
    bool noteBool = false;
    bool openNote = false;
    void Start()
    {
        cross.SetActive(false);
        dontDestroy = FindObjectOfType<ShrineDontDestroy>();
    }

    // Update is called once per frame
    void Update()
    {
        if(canPlace && placed == false && Input.GetKeyDown(KeyCode.E))
        {
            cross.SetActive(true);
            pressE.SetActive(false);
            noteBool = false;
            note.SetActive(false);
            canPlace = false;
            animationCheck = true;
            placed = true;
        }

        if(dontDestroy.collected)
        {
            if (!lightBool)
            {
                lightBool = true;
                light.SetActive(true);
                noteBool = false;
                note.SetActive(false);
            }
        }
        else 
        {
            if (openNote)
            {
                if (Input.GetKeyDown(KeyCode.E))
                {
                    if (noteBool)
                    {
                        noteBool = false;
                        note.SetActive(false);
                        pressE.SetActive(true);
                    }
                    else
                    {
                        noteBool = true;
                        note.SetActive(true);
                        pressE.SetActive(false);
                    }
                }
            }
        }

        if(animationCheck == true && animationfinished == false)
        {
            animationfinished = true;
            light.SetActive(false);
            anim.Play();
            portalSound.Play();
            StartCoroutine(changescene());
        }
    }

    private IEnumerator changescene()
    {
        yield return new WaitForSeconds(3f);
        SceneManager.LoadScene("Credits");
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.CompareTag("Player") && placed == false && dontDestroy.collected)
        {
            pressE.SetActive(true);
            canPlace = true;
        }
        else if (collision.CompareTag("Player"))
        {
            pressE.SetActive(true);
            openNote = true;
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.CompareTag("Player"))
        {
            pressE.SetActive(false);
            canPlace = false;
            openNote = false;
            noteBool = false;
            note.SetActive(false);
        }
    }
}
