#include<iostream>
#include<string>
#include<queue>
#include<set>
#include<stack>
using namespace std;

class Node
{
public:
	Node* parent;
	int state;
	int action;
	int pathCost;

	Node(Node* parent = NULL, int state = -1, int action = -1, int pathCost = 0)
	{
		this->parent = parent;
		this->state = state;
		this->action = action;
		this->pathCost = pathCost;
	}
};

bool findInSet(set<Node*>& explored, Node* node)
{
	bool find = false;
	set <Node*> ::iterator itr;

	for (itr = explored.begin(); itr != explored.end(); ++itr)
	{
		if ((*itr)->state == node->state)
		{
			find = true;
			break;
		}
	}
	return find;
}

bool findInQueue(queue<Node*>& frontier, Node* node)
{
	bool find = false;
	queue<Node*> temp;
	while (!frontier.empty())
	{
		if ((*frontier.front()).state == (*node).state)
		{
			find = true;
		}
		temp.push(frontier.front());
		frontier.pop();
	}

	while (!temp.empty())
	{
		frontier.push(temp.front());
		temp.pop();
	}
	return find;
}

int main()
{
	//opening file to take input
	freopen("input.txt", "r", stdin);
	
	int m, n, t;
	string* states, *actions;
	string testCase;
	string start;
	string end;
	int** transitionTable;

	//Taking No of States, No of Actions, No of test cases from the file directly
	cin >> m >> n >> t;

	//Initialize the Resources
	states = new string[m];
	actions = new string[n];
	transitionTable = new int*[m];

	for (int i = 0; i < m; i++)
		transitionTable[i] = new int[n];

	getchar();

	//Getting the description of the states
	for (int i = 0; i < m; i++)
	{
		if (i == 0)
			cin.ignore();
		getline(cin, states[i]);
	}

	getchar();

	//Getting Description of Actions
	for (int i = 0; i < n; i++)
		getline(cin, actions[i]);

	getchar();

	//Getting data about next actions at a given state
	for (int i = 0; i < m; i++)
		cin >> transitionTable[i][0] >> transitionTable[i][1] >> transitionTable[i][2];

	getchar();
	getchar();

	for (int i = 0; i < t; i++)
	{
		set<Node*>explored;
		bool flag = false;
		getline(cin, testCase);

		start = testCase.substr(0, (testCase.find("\t")));

		end = testCase.substr((testCase.find("\t")) + 1);

		int startStateInt = 0;

		int endStateInt = 0;
		//comparing the states with the starting state
		for (int j = 0; j < m; j++)
		{
			if (!start.compare(states[j]))
				break;
			startStateInt++;
		}
		//comparing states with ending state
		for (int j = 0; j < m; j++)
		{
			if (!end.compare(states[j]))
				break;
			endStateInt++;
		}

		Node* startNode = new Node(NULL, startStateInt, -1, 0);

		queue<Node*> frontier;

		frontier.push(startNode);

		Node* node = NULL;
		//Program starts
		while (!frontier.empty())
		{
			node = frontier.front();
			frontier.pop();

			if ((*node).state == endStateInt)
			{
				flag = true;
				stack<int> outputActions;

				while (node->action != -1)
				{
					outputActions.push(node->action);
					node = node->parent;
				}

				while (!outputActions.empty())
				{
					switch (outputActions.top())
					{
					case 0:
						cout << "Clean";
						break;
					case 1:
						cout << "MoveToRoom1";
						break;
					case 2:
						cout << "MoveToRoom2";
						break;
					default:
						break;
					}
					outputActions.pop();
					if (!outputActions.empty())
						cout << "->";
					else
						cout << endl;
				}

				break;
			}
			else
			{
				explored.insert(node);

				for (int i = 0; i < n; i++)
				{
					Node* tempNode = new Node(node, transitionTable[(*node).state][i], i, ((*node).pathCost) + 1);

					if (!findInSet(explored, tempNode))
					{
						if (!findInQueue(frontier, tempNode))
						{
							frontier.push(tempNode);
						}
					}

				}
			}
		}
		if (!flag)
			cout << "No path exists!" << endl;
	}
	return 0;
}