---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-29 09:55:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 505 |
| Sample Rate | 8.42/sec |
| Health Score | 526% |
| Threads | 8 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 772 |
| Sample Rate | 12.87/sec |
| Health Score | 804% |
| Threads | 9 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (4 unique values: 23-52 cores)</summary>

```
1793281798 52
1793281803 52
1793281808 52
1793281813 52
1793281818 52
1793281823 52
1793281828 52
1793281833 52
1793281838 52
1793281843 52
1793281848 52
1793281853 50
1793281858 50
1793281863 50
1793281868 50
1793281873 50
1793281878 50
1793281883 50
1793281888 50
1793281893 49
```
</details>

---

