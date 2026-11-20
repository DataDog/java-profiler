---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-20 08:52:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 9 |
| Allocations | 416 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (3 unique values: 45-50 cores)</summary>

```
1795182424 46
1795182429 46
1795182434 46
1795182439 46
1795182444 50
1795182449 50
1795182454 50
1795182459 50
1795182464 50
1795182469 50
1795182474 50
1795182479 50
1795182484 50
1795182489 50
1795182494 50
1795182499 50
1795182504 50
1795182509 50
1795182514 45
1795182519 45
```
</details>

---

