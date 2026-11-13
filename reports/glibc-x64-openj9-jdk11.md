---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 16:23:58 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 527 |
| Sample Rate | 8.78/sec |
| Health Score | 549% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 9 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (4 unique values: 31-38 cores)</summary>

```
1794604852 36
1794604857 36
1794604862 34
1794604867 34
1794604872 34
1794604877 34
1794604882 34
1794604887 34
1794604892 34
1794604897 34
1794604902 34
1794604907 34
1794604912 34
1794604917 34
1794604922 36
1794604927 36
1794604932 36
1794604937 36
1794604942 36
1794604947 36
```
</details>

---

