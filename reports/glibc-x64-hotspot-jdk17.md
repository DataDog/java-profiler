---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-04 10:12:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 74 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 622 |
| Sample Rate | 10.37/sec |
| Health Score | 648% |
| Threads | 10 |
| Allocations | 443 |

<details>
<summary>CPU Timeline (3 unique values: 72-76 cores)</summary>

```
1788530863 74
1788530868 74
1788530873 74
1788530878 74
1788530883 72
1788530888 72
1788530893 72
1788530898 72
1788530903 72
1788530908 72
1788530913 72
1788530918 72
1788530923 72
1788530928 72
1788530933 74
1788530938 74
1788530943 74
1788530948 74
1788530953 74
1788530958 74
```
</details>

---

