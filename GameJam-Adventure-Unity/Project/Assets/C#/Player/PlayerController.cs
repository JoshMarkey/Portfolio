using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerController : MonoBehaviour
{
    [Header("Movement")]
    public float movementSpeed = 5f;
    private Rigidbody2D rb;
    private Vector2 movement;
    public int dir = 1;
    [SerializeField] Animator animation;
    [Space]
    [Header("Clue")]
    [SerializeField] Clue clueCanvas;
    [SerializeField] GameObject pressE;
    bool inRange = false;
    public bool canMove = true;
    int currentClue = 0;
    [Space]
    [Header("Colliders")]
    [SerializeField] BoxCollider2D hitboxUp;
    [SerializeField] BoxCollider2D hitboxDown;
    [SerializeField] BoxCollider2D hitboxSide;
    [Header("FootSteps")]
    [SerializeField] AudioSource dirtFootSteps;
    [SerializeField] AudioSource woodenFootSteps;
    [SerializeField] AudioSource stoneFootSteps;
    AudioSource currentSound;
    float timer = 0;

    void Start()
    {
        rb = GetComponent<Rigidbody2D>();
        animation = GetComponent<Animator>();
    }

    private void Update()
    {
        timer -= Time.deltaTime;
        movement.x = Input.GetAxisRaw("Horizontal");
        movement.y = Input.GetAxisRaw("Vertical");

        if(inRange)
        {
            if(Input.GetKeyDown(KeyCode.E))
            {
                if (!clueCanvas.open)
                {
                    clueCanvas.openClue(currentClue);
                    pressE.SetActive(false);
                }
            }
        }
    }

    void FixedUpdate()
    {
        bool hasMoved = false;
        
        if (canMove)
        {
            rb.MovePosition(rb.position + movement * movementSpeed * Time.fixedDeltaTime);


            animation.ResetTrigger("Idle");
            if (movement.x == 0 && movement.y == 0)
            {
                animation.SetTrigger("Idle");
            }


            if (movement.x > 0 && dir == 0)
            {
                transform.localScale = new Vector2(transform.localScale.x*-1, transform.localScale.y);
                dir = 1;
            }
            else if (movement.x < 0 && dir == 1)
            {
                transform.localScale = new Vector2(transform.localScale.x * -1, transform.localScale.y);
                dir = 0;
            }

            if (movement.x != 0)
            {
                hasMoved = true;
                hitboxSide.enabled = true;
                hitboxUp.enabled = false;
                hitboxDown.enabled = false;
                animation.SetTrigger("Side");
            }
            else if (movement.y > 0)
            {
                hasMoved = true;
                hitboxSide.enabled = false;
                hitboxUp.enabled = true;
                hitboxDown.enabled = false;
                animation.SetTrigger("Up");
            }
            else if (movement.y < 0)
            {
                hasMoved = true;
                hitboxSide.enabled = false;
                hitboxUp.enabled = false;
                hitboxDown.enabled = true;
                animation.SetTrigger("Down");
            }
            if (timer <= 0 && hasMoved)
            {
                timer = 0.4f;
                currentSound.Play();
            }

            StartCoroutine(resetTriggers());

        }
    }

    IEnumerator resetTriggers()
    {
        yield return new WaitForSeconds(0.05f);
        animation.ResetTrigger("Side");
        animation.ResetTrigger("Up");
        animation.ResetTrigger("Down");
    }



    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.CompareTag("Clue1"))
        {
            currentClue = 1;
            pressE.gameObject.SetActive(true);
            inRange = true;
        }
        if (collision.CompareTag("Clue2"))
        {
            currentClue = 2;
            pressE.gameObject.SetActive(true);
            inRange = true;
        }
        if (collision.CompareTag("Clue3"))
        {
            currentClue = 3;
            pressE.gameObject.SetActive(true);
            inRange = true;
        }
    }

    private void OnTriggerStay2D(Collider2D collision)
    {

        if (collision.CompareTag("Dirt"))
        {
            currentSound = dirtFootSteps;
        }
        else if (collision.CompareTag("Wood"))
        {
            currentSound = woodenFootSteps;
        }
        else if (collision.CompareTag("Stone"))
        {
            currentSound = stoneFootSteps;
        }
    }

    private void OnTriggerExit2D(Collider2D collision)
    {
        inRange= false;
        pressE.gameObject.SetActive(false);
    }
}
