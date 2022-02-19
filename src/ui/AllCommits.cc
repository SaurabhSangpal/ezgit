#include "AllCommits.h"

#include <git2.h>
#include <qlabel.h>

#include <future>
#include <thread>

#include "../git_wrapper/Commit.h"
#include "../git_wrapper/Repository.h"
#include "Commit.h"
#include "ui_AllCommits.h"

inline std::string GetTime(const git_time* inTime, const char* prefix);

AllCommits::AllCommits(git::Repository& repo, QWidget* parent)
    : QWidget(parent), ui(new Ui::AllCommits), repo(repo) {
	ui->setupUi(this);

	auto* layout = new QVBoxLayout;
	layout->setAlignment(Qt::AlignmentFlag::AlignTop);
	ui->commitsScrollAreaContent->setLayout(layout);
	ui->commitsScrollArea->setWidget(ui->commitsScrollAreaContent);

	Fetch();
}

AllCommits::~AllCommits() { delete ui; }

void AllCommits::Fetch() noexcept {
	auto log = std::async(std::launch::async, &AllCommits::FetchLog, this);
	DisplayAllCommits(log.get());
}

void AllCommits::AddCommit(const git::Commit& commit) noexcept {
	auto uiCommit = std::make_shared<Commit>(ui->commitsScrollAreaContent);
	uiCommit->Setup(commit);
	ui->commitsScrollAreaContent->layout()->addWidget(uiCommit.get());

	commits.push_back(uiCommit);
}

std::vector<git::Commit> AllCommits::FetchLog() noexcept {
	int		 parents;
	git_diff_options diffOptions = GIT_DIFF_OPTIONS_INIT;
	git_oid		 oid;
	git_commit*	 commit = nullptr;
	git_pathspec*	 ps	= nullptr;
	git_revwalk*	 revwalk;

	if (git_revwalk_new(&revwalk, repo.GetRepository()) != 0) {
		// TODO: Decide what happens here.
		return {};
	}
	if (git_revwalk_sorting(revwalk, GIT_SORT_TIME) != 0) {
		return {};
	}
	git_revwalk_push_head(revwalk);

	std::vector<git::Commit> out;

	for (; git_revwalk_next(&oid, revwalk) == 0; git_commit_free(commit)) {
		if (git_commit_lookup(&commit, repo.GetRepository(), &oid) != 0) {
			// NOTE: Is this correct? Will we free commit twice?
			continue;
		}

		auto* author  = git_commit_author(commit);
		auto* message = git_commit_message(commit);
		auto* body    = git_commit_body(commit);
		if (body == nullptr || body == NULL) {
			body = "";
		}
		char buf[7 + 1];
		git_oid_tostr(buf, sizeof(buf), git_commit_id(commit));
		auto time = GetTime(&author->when, "");

		git::Commit gc{};
		gc.Setup(message, author->name, buf, time, body);
		out.push_back(gc);
	}

	git_revwalk_free(revwalk);
	git_pathspec_free(ps);

	return out;
}

void AllCommits::DisplayAllCommits(const std::vector<git::Commit>& commitsVec) noexcept {
	for (auto& i : commitsVec) {
		AddCommit(i);
	}
}

inline std::string GetTime(const git_time* inTime, const char* prefix) {
	char	   sign, out[32];
	struct tm* intm;
	int	   offset, hours, minutes;
	time_t	   t;

	offset = inTime->offset;
	if (offset < 0) {
		sign   = '-';
		offset = -offset;
	} else {
		sign = '+';
	}

	hours	= offset / 60;
	minutes = offset % 60;

	t = (time_t)inTime->time + (inTime->offset * 60);

	intm = gmtime(&t);
	strftime(out, sizeof(out), "%a %b %e %T %Y", intm);

	char buffer[64] = {0};

	sprintf(buffer, "%s%s\n", prefix, out);
	return buffer;
}
