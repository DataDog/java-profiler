---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-21 06:49:18 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 351 |
| Sample Rate | 5.85/sec |
| Health Score | 366% |
| Threads | 9 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 12 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (2 unique values: 60-81 cores)</summary>

```
1792579499 81
1792579504 81
1792579509 81
1792579514 81
1792579519 81
1792579524 81
1792579529 81
1792579534 81
1792579539 81
1792579544 81
1792579549 81
1792579554 81
1792579559 60
1792579564 60
1792579569 60
1792579574 60
1792579579 60
1792579584 60
1792579589 60
1792579594 60
```
</details>

---

