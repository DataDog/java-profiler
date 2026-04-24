---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-24 17:03:59 EDT

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
| CPU Cores (start) | 72 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 539 |
| Sample Rate | 8.98/sec |
| Health Score | 561% |
| Threads | 8 |
| Allocations | 362 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 720 |
| Sample Rate | 12.00/sec |
| Health Score | 750% |
| Threads | 10 |
| Allocations | 501 |

<details>
<summary>CPU Timeline (4 unique values: 72-81 cores)</summary>

```
1777064276 72
1777064281 72
1777064286 72
1777064291 72
1777064296 72
1777064301 72
1777064306 72
1777064311 72
1777064316 72
1777064321 72
1777064326 72
1777064331 72
1777064336 77
1777064341 77
1777064346 81
1777064351 81
1777064356 79
1777064361 79
1777064366 81
1777064371 81
```
</details>

---

