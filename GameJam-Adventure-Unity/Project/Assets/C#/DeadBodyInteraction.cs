using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class DeadBodyInteraction : MonoBehaviour
{

    [SerializeField] GameObject interactionButton;
    private bool ontop;
    public bool hasCross;
    ShrineDontDestroy dontDestroy;

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.CompareTag("Player"))
        {
            if(!hasCross)
            {
                ontop = true;
                interactionButton.SetActive(true);
            }
        }
    }
    private void OnTriggerExit2D(Collider2D collision)
    {
        if (collision.CompareTag("Player"))
        {
            ontop = false;
            interactionButton.SetActive(false);
        }
    }

    void Start()
    {
        ontop = false;
        dontDestroy = FindObjectOfType<ShrineDontDestroy>();
        hasCross = false;
    }

    void Update()
    {
        if(ontop)
        {
            if(Input.GetKeyDown(KeyCode.E))
            {
                dontDestroy.collected = true;
                hasCross = true;
                interactionButton.SetActive(false);
            }
        }
    }
}
