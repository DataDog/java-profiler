---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-15 16:13:29 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 321 |
| Sample Rate | 5.35/sec |
| Health Score | 334% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 166 |
| Sample Rate | 2.77/sec |
| Health Score | 173% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 50-72 cores)</summary>

```
1794776967 50
1794776972 50
1794776977 50
1794776982 50
1794776987 50
1794776992 50
1794776997 50
1794777002 50
1794777007 70
1794777012 70
1794777017 70
1794777022 70
1794777027 70
1794777032 70
1794777037 70
1794777042 70
1794777047 70
1794777052 70
1794777057 70
1794777062 70
```
</details>

---

