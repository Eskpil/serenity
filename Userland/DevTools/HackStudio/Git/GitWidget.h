/*
 * Copyright (c) 2020, Itamar S. <itamar8910@gmail.com>
 *
 * SPDX-License-Identifier: BSD-2-Clause
 */

#pragma once

#include "GitFilesView.h"
#include "GitRepo.h"
#include <AK/Function.h>
#include <LibGUI/Forward.h>
#include <LibGUI/Widget.h>

namespace HackStudio {

using ViewDiffCallback = Function<void(DeprecatedString const& original_content, DeprecatedString const& diff)>;

class GitWidget final : public GUI::Widget {
    C_OBJECT(GitWidget)
public:
    virtual ~GitWidget() override { }

    void refresh();
    void set_view_diff_callback(ViewDiffCallback callback);
    bool initialized() const { return !m_git_repo.is_null(); }
    void change_repo(DeprecatedString const& repo_root);

private:
    explicit GitWidget();

    bool initialize();
    bool initialize_if_needed();
    void stage_file(DeprecatedString const&);
    void unstage_file(DeprecatedString const&);
    void commit();
    void show_diff(DeprecatedString const&);

    DeprecatedString m_repo_root;
    RefPtr<GitFilesView> m_unstaged_files;
    RefPtr<GitFilesView> m_staged_files;
    RefPtr<GitRepo> m_git_repo;
    ViewDiffCallback m_view_diff_callback;
};

}
