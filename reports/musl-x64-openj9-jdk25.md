---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-04 10:12:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 566 |
| Sample Rate | 9.43/sec |
| Health Score | 589% |
| Threads | 10 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1788530833 79
1788530838 79
1788530843 79
1788530848 79
1788530853 79
1788530858 79
1788530863 79
1788530868 79
1788530873 81
1788530878 81
1788530883 81
1788530888 81
1788530893 81
1788530898 81
1788530903 81
1788530908 81
1788530913 81
1788530918 81
1788530923 81
1788530928 81
```
</details>

---

