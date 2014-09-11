/**
 *  ==============================================================================
 *
 *          \file   tieba/info_def.h
 *
 *        \author   chenghuige
 *
 *          \date   2014-09-02 11:09:23.064938
 *
 *  \Description:
 *  ==============================================================================
 */

#ifndef TIEBA_INFO_DEF_H_
#define TIEBA_INFO_DEF_H_

#include "../common_def.h"
#include "serialize_util.h"
#include "common_util.h"

namespace gezi {
	namespace tieba {

		//¥��¥��Ϣ PostInfoʹ��, ����CommentInfoҲ��¥��¥��Ϣ ��FullPost¥��Ϣ����ʹ��
		struct QuoteInfo
		{
			uint64 postId = 0; //ָ����¥��¥��Ӧ�Ļظ���pid
			uint userId = 0;
			string userName;
			uint64 ip = 0;
			string content; //¥��¥��Ӧ�ظ�������
			/*	'post_id' = > '57218429704',
				'uname' = > '��⽸�s',
				'uid' = > 672041209,
				'ip' = > 2365012337,
				'content' = > '[ͼƬ]  ����  ds��',
				'post_type' = > 1,*/
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(postId);
				ar & BOOST_SERIALIZATION_NVP(userId);
				ar & BOOST_SERIALIZATION_NVP(userName);
				ar & BOOST_SERIALIZATION_NVP(ip);
				ar & BOOST_SERIALIZATION_NVP(content);
			}
		};

		struct PostInfo
		{
			uint64 postId = 0;
			uint64 threadId = 0;
			uint userId = 0;
			uint forumId = 0;
			uint64 ip = 0;
			uint64 createTime = 0;
			string title;
			string content;
			string userName;
			string forumName;
			QuoteInfo quoteInfo;

			bool IsThread()
			{
				return !startswith(title, "�ظ���");
			}

			bool IsQuote()
			{
				return quoteInfo.postId != 0;
			}

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(postId);
				ar & BOOST_SERIALIZATION_NVP(threadId);
				ar & BOOST_SERIALIZATION_NVP(userId);
				ar & BOOST_SERIALIZATION_NVP(forumId);
				ar & BOOST_SERIALIZATION_NVP(ip);
				ar & BOOST_SERIALIZATION_NVP(createTime);
				ar & BOOST_SERIALIZATION_NVP(title);
				ar & BOOST_SERIALIZATION_NVP(content);
				ar & BOOST_SERIALIZATION_NVP(userName);
				ar & BOOST_SERIALIZATION_NVP(forumName);
				ar & BOOST_SERIALIZATION_NVP(quoteInfo);
			}
		};

		struct UrlInfo;
		struct ExtendedPostInfo : public PostInfo
		{
			map<string, UrlInfo> urlInfoMap; //url��Ϣ  url->UrlInfo
			vector<string> urls;
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(PostInfo);
				ar & BOOST_SERIALIZATION_NVP(urlInfoMap);
				ar & BOOST_SERIALIZATION_NVP(urls);
			}
		};

		//����������������Ϣ 
		struct PostsInfo
		{
			vector<uint64> pids;
			vector<uint64> tids; //�����¥ģ������ǿ� ����1 
			vector<uint> uids; //���������Ϊģ�� ����ǿջ���1
			vector<uint64> times; //@TODO uint
			vector<uint> fids;
			vector<string> fnames;
			vector<string> titles;
			vector<string> contents;
			vector<uint64> ips; //@TODO uint
			vector<bool> isThreads;
			size_t size()
			{
				return pids.size();
			}
		};

		struct UserPostsInfo
		{
			uint userId = 0;
			int numPosts = 0;
			vector<uint64> pids;
			vector<uint64> tids;
			vector<uint64> times;
			vector<uint> fids;
			vector<string> fnames;
			vector<string> titles;
			vector<string> contents;
			vector<uint64> ips;
			vector<bool> isThreads;
			vector<bool> isPostsDeleted;

			size_t size()
			{
				return pids.size();
			}

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(userId);
				ar & BOOST_SERIALIZATION_NVP(numPosts);
				ar & BOOST_SERIALIZATION_NVP(pids);
				ar & BOOST_SERIALIZATION_NVP(tids);
				ar & BOOST_SERIALIZATION_NVP(times);
				ar & BOOST_SERIALIZATION_NVP(fids);
				ar & BOOST_SERIALIZATION_NVP(fnames);
				ar & BOOST_SERIALIZATION_NVP(titles);
				ar & BOOST_SERIALIZATION_NVP(contents);
				ar & BOOST_SERIALIZATION_NVP(ips);
				ar & BOOST_SERIALIZATION_NVP(isThreads);
				ar & BOOST_SERIALIZATION_NVP(isPostsDeleted);
			}
		};

		struct CommentInfo
		{
			uint64 threadId = 0;
			uint64 postId = 0;    //¥��¥��Ӧ�ظ���pid
			uint64 commentId = 0; //¥��¥������pid
			string userName;
			uint64 userId = 0;
			uint64 ip = 0;
			uint64 createTime = 0;
			string content;
			/*'thread_id' = > '3286155511',
			'post_id' = > '57218429704',
			'comment_id' = > '57218499162',
			'username' = > 'Km��ʧ',
			'user_id' = > '157505881',
			'ip' = > 1330276779,
			'now_time' = > 1410312338,
			'content' = > '����Ҳ���Ե��Ű����ѵ��ǿ���һ���Ž�ȥ��',
			'ptype' = > 0,*/
			bool operator == (const CommentInfo& other)
			{ //for python wrapper Ӧ����boost.python������ vector<vector<CommentInfo> >��Ҫ
				return commentId == other.commentId;
			}
			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(threadId);
				ar & BOOST_SERIALIZATION_NVP(postId);
				ar & BOOST_SERIALIZATION_NVP(commentId);
				ar & BOOST_SERIALIZATION_NVP(userName);
				ar & BOOST_SERIALIZATION_NVP(userId);
				ar & BOOST_SERIALIZATION_NVP(ip);
				ar & BOOST_SERIALIZATION_NVP(createTime);
				ar & BOOST_SERIALIZATION_NVP(content);
			}
		};
		typedef vector<CommentInfo> Comments;

		struct FullPostsInfo
		{
			uint64 threadId = 0; //�����0��ʾû�л�ȡ����Ϣ FullPostInfo������Ч
			uint forumId = 0;
			string title;
			string forumName;
			bool isDeleted = false;
			int numPosts = 0;
			vector<uint64> pids;
			vector<uint> uids;
			vector<uint64> ips;
			vector<uint64> times;
			vector<string> unames;
			vector<string> contents;
			vector<Comments> commentsVec;
			size_t size()
			{
				return pids.size();
			}

			const Comments& GetComments(int idx) const
			{
				return commentsVec[idx];
			}

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(threadId);
				ar & BOOST_SERIALIZATION_NVP(forumId);
				ar & BOOST_SERIALIZATION_NVP(title);
				ar & BOOST_SERIALIZATION_NVP(forumName);
				ar & BOOST_SERIALIZATION_NVP(isDeleted);
				ar & BOOST_SERIALIZATION_NVP(numPosts);
				ar & BOOST_SERIALIZATION_NVP(pids);
				ar & BOOST_SERIALIZATION_NVP(uids);
				ar & BOOST_SERIALIZATION_NVP(ips);
				ar & BOOST_SERIALIZATION_NVP(times);
				ar & BOOST_SERIALIZATION_NVP(unames);
				ar & BOOST_SERIALIZATION_NVP(contents);
				ar & BOOST_SERIALIZATION_NVP(commentsVec);
			}
		};

		struct ReplyInfo
		{
			uint64 threadId;
			uint64 userId;
			uint64 postId;
			uint forumId;
			uint64 ip;
			uint64 createTime;
		};

		struct UserInfo
		{
			uint userId = 0;
			string userName;
			uint64 regTime = 0;
			int userSex = 0; //0 ûд, 1 male, 2 female
			int followCount = 0; //��ע��
			int followedCount = 0; //��˿��
			string email;
			string mobile;
			int birthYear = 0;
			int isGroupOwner = 0; //0,1,2
			int userType = 0; //0, 1 vip
			int userStatus = 0; //0, 1����������ע
			string userTag;
			string userDetail;

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(userId);
				ar & BOOST_SERIALIZATION_NVP(userName);
				ar & BOOST_SERIALIZATION_NVP(regTime);
				ar & BOOST_SERIALIZATION_NVP(userSex);
				ar & BOOST_SERIALIZATION_NVP(followCount);
				ar & BOOST_SERIALIZATION_NVP(followedCount);
				ar & BOOST_SERIALIZATION_NVP(email);
				ar & BOOST_SERIALIZATION_NVP(mobile);
				ar & BOOST_SERIALIZATION_NVP(birthYear);
				ar & BOOST_SERIALIZATION_NVP(isGroupOwner);
				ar & BOOST_SERIALIZATION_NVP(userType);
				ar & BOOST_SERIALIZATION_NVP(userStatus);
				ar & BOOST_SERIALIZATION_NVP(userTag);
				ar & BOOST_SERIALIZATION_NVP(userDetail);
			}
		};

		struct UserPostNumInfo
		{
			uint userId = 0;
			int numPosts = 0;
			int numThreads = 0;
			int numGoods = 0;
			int numPhotos = 0;

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(userId);
				ar & BOOST_SERIALIZATION_NVP(numPosts);
				ar & BOOST_SERIALIZATION_NVP(numThreads);
				ar & BOOST_SERIALIZATION_NVP(numGoods);
				ar & BOOST_SERIALIZATION_NVP(numPhotos);
			}
		};

		//�û���ע�ɵ���Ϣ �������õ�����
		//�û��ڵ�ǰ�ɵļ����û���ע����Ŀ���û���ע�����ȼ����û���ע�ɵȼ�֮��,�û���ǰ�ɼ�������ȼ��ɵȼ����
		struct UserLikeForumInfo
		{
			struct Node
			{
				string forumName;
				uint64 time;
				int level;
				int curScore;
				int leftScore;

				friend class boost::serialization::access;
				template<class Archive>
				void serialize(Archive &ar, const unsigned int version)
				{
					ar & BOOST_SERIALIZATION_NVP(forumName);
					ar & BOOST_SERIALIZATION_NVP(time);
					ar & BOOST_SERIALIZATION_NVP(level);
					ar & BOOST_SERIALIZATION_NVP(curScore);
					ar & BOOST_SERIALIZATION_NVP(leftScore);
				}
			};

			//��ȡ�ڵ�ǰ���µĵȼ�
			int GetLevel(uint forumId)
			{
				auto iter = infoMap.find(forumId);
				if (iter != infoMap.end())
				{
					return (iter->second).level;
				}
				return 0;
			}

			uint userId = 0;
			int maxLevel = 0;
			int numLikes = 0;
			int sumLevels = 0;
			map<uint, Node> infoMap;
			vector<string> forumNames;
			vector<int> levels;

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(userId);
				ar & BOOST_SERIALIZATION_NVP(maxLevel);
				ar & BOOST_SERIALIZATION_NVP(numLikes);
				ar & BOOST_SERIALIZATION_NVP(sumLevels);
				ar & BOOST_SERIALIZATION_NVP(infoMap);
				ar & BOOST_SERIALIZATION_NVP(forumNames);
				ar & BOOST_SERIALIZATION_NVP(levels);
			}
		};

		struct ThreadInfo
		{
			uint64 threadId = 0;
			uint64 userId;
			uint64 postId;
			uint forumId; //forum_id
			string forumName;
			uint64 createTime;
			uint64 ip;
			string address;
			string title;
			string content;
			bool isDeleted = false;
			bool hasMedia = false; //pic,vedio ע��Url����

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(threadId);
				ar & BOOST_SERIALIZATION_NVP(userId);
				ar & BOOST_SERIALIZATION_NVP(postId);
				ar & BOOST_SERIALIZATION_NVP(forumId);
				ar & BOOST_SERIALIZATION_NVP(forumName);
				ar & BOOST_SERIALIZATION_NVP(createTime);
				ar & BOOST_SERIALIZATION_NVP(ip);
				ar & BOOST_SERIALIZATION_NVP(address);
				ar & BOOST_SERIALIZATION_NVP(title);
				ar & BOOST_SERIALIZATION_NVP(content);
				ar & BOOST_SERIALIZATION_NVP(isDeleted);
				ar & BOOST_SERIALIZATION_NVP(hasMedia);
			}
		};

		struct DeleteInfo
		{
			uint64 tid = 0;
			uint64 pid = 0;
			string opUid;
			string monitorType; //17007�� ����ɾ����0
			uint64 opTime = 0;
			bool isDeleted = false;

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(tid);
				ar & BOOST_SERIALIZATION_NVP(pid);
				ar & BOOST_SERIALIZATION_NVP(opUid);
				ar & BOOST_SERIALIZATION_NVP(monitorType);
				ar & BOOST_SERIALIZATION_NVP(opTime);
				ar & BOOST_SERIALIZATION_NVP(isDeleted);
			}
		};

		//forum_dir      output{            //�������
		//	uint32_t  rank                //����Ŀ¼�ɰ��ȶ����� ��Ŀǰ�����£�
		//	string    level_1_name        //һ��Ŀ¼
		//	string    level_2_name        //����Ŀ¼
		//	uint32_t  hot_value           //�ȶ�ֵ ��Ŀǰ�����£�
		struct ForumInfo
		{
			uint fid = 0;
			uint rank;
			uint hotValue;
			string level1Name;
			string level2Name;

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(fid);
				ar & BOOST_SERIALIZATION_NVP(rank);
				ar & BOOST_SERIALIZATION_NVP(hotValue);
				ar & BOOST_SERIALIZATION_NVP(level1Name);
				ar & BOOST_SERIALIZATION_NVP(level2Name);
			}
		};

		struct UrlInfo
		{
			string url; //url��Ϊ�ձ����Ч
			float rank = 0.0;
			bool isJump = false;
			float jumRank = 0.0;
			string content;

			friend class boost::serialization::access;
			template<class Archive>
			void serialize(Archive &ar, const unsigned int version)
			{
				ar & BOOST_SERIALIZATION_NVP(url);
				ar & BOOST_SERIALIZATION_NVP(rank);
				ar & BOOST_SERIALIZATION_NVP(isJump);
				ar & BOOST_SERIALIZATION_NVP(jumRank);
				ar & BOOST_SERIALIZATION_NVP(content);
			}
		};

		static const int kMaxRequestCount = 100;

#ifdef GCCXML
		struct PyHack_Comments
		{ //hack for vector<Comments>  vector<vector ��Ȼû��vector<Comment> ������Use(vector<Comment> ? @TODO
			Comments comments;
		};
#include "python_util.h"
		UseMap(map<uint, UserLikeForumInfo::Node>);
		UseMap(map<string, UrlInfo>);
#endif

	}  //----end of namespace tieba
}  //----end of namespace gezi

#endif  //----end of TIEBA_INFO_DEF_H_