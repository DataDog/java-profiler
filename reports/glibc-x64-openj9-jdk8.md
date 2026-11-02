---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-02 07:22:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 339 |
| Sample Rate | 5.65/sec |
| Health Score | 353% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 366 |
| Sample Rate | 6.10/sec |
| Health Score | 381% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 68-91 cores)</summary>

```
1793621923 68
1793621928 68
1793621933 68
1793621938 68
1793621943 68
1793621948 68
1793621953 68
1793621958 68
1793621963 70
1793621968 70
1793621973 91
1793621978 91
1793621983 91
1793621988 91
1793621993 91
1793621998 91
1793622003 91
1793622008 91
1793622013 91
1793622018 91
```
</details>

---

