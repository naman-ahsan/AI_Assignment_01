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
	freopen("input.txt", "r", stdin);
	//freopen("output.txt", "w", stdout);
	//All Resources
	int m, n, t;
	string* states, * actions;
	string startAndEndState;
	string startState;
	string endState;
	int** tt;

	//Taking No of States, No of Actions, No of test cases
	cin >> m >> n >> t;

	//Initialize the Resources
	states = new string[m];
	actions = new string[n];
	tt = new int* [m];

	for (int i = 0; i < m; i++)
		tt[i] = new int[n];

	getchar();

	//Collect Description of States
	for (int i = 0; i < m; i++)
	{
		if (i == 0)
			cin.ignore();
		getline(cin, states[i]);
	}

	getchar();

	//Taking Description of Actions
	for (int i = 0; i < n; i++)
		getline(cin, actions[i]);

	getchar();

	//Taking data about next actions at a given state
	for (int i = 0; i < m; i++)
		cin >> tt[i][0] >> tt[i][1] >> tt[i][2];

	getchar();
	getchar();

	for (int i = 0; i < t; i++)
	{
		set<Node*>explored;
		bool flag = false;
		getline(cin, startAndEndState);

		startState = startAndEndState.substr(0, (startAndEndState.find("\t")));

		endState = startAndEndState.substr((startAndEndState.find("\t")) + 1);

		int startStateInt = 0;

		int endStateInt = 0;

		for (int j = 0; j < m; j++)
		{
			if (!startState.compare(states[j]))
				break;
			startStateInt++;
		}

		for (int j = 0; j < m; j++)
		{
			if (!endState.compare(states[j]))
				break;
			endStateInt++;
		}

		Node* startNode = new Node(NULL, startStateInt, -1, 0);

		queue<Node*> frontier;

		frontier.push(startNode);

		Node* node = NULL;

		while (!frontier.empty())
		{
			node = frontier.front();
			frontier.pop();

			if ((*node).state == endStateInt)
			{
				flag = true;
				stack<int> recordAction;

				while (node->action!=-1)
				{
					recordAction.push(node->action);
					node = node->parent;
				}

				while (!recordAction.empty())
				{
					switch (recordAction.top())
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
					recordAction.pop();
					if (!recordAction.empty())
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
					Node* tempNode = new Node(node, tt[(*node).state][i], i, ((*node).pathCost) + 1);

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
