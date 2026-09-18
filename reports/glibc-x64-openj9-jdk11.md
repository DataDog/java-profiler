---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-18 03:33:36 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 8 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 790 |
| Sample Rate | 13.17/sec |
| Health Score | 823% |
| Threads | 11 |
| Allocations | 526 |

<details>
<summary>CPU Timeline (3 unique values: 75-79 cores)</summary>

```
1789716412 79
1789716417 79
1789716422 79
1789716427 79
1789716432 79
1789716437 79
1789716442 79
1789716447 75
1789716452 75
1789716457 75
1789716462 75
1789716467 75
1789716472 75
1789716477 75
1789716482 75
1789716487 75
1789716492 75
1789716497 75
1789716502 75
1789716507 75
```
</details>

---

