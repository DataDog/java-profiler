---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-05-05 08:22:42 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 388 |
| Sample Rate | 6.47/sec |
| Health Score | 404% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 11 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 52-62 cores)</summary>

```
1777983474 52
1777983479 52
1777983484 52
1777983489 57
1777983494 57
1777983499 57
1777983504 57
1777983509 57
1777983514 57
1777983519 62
1777983524 62
1777983529 62
1777983534 62
1777983539 62
1777983544 62
1777983549 62
1777983554 62
1777983559 62
1777983564 62
1777983569 62
```
</details>

---

