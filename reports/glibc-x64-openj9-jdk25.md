---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 12:06:59 EST

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
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 387 |
| Sample Rate | 6.45/sec |
| Health Score | 403% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 479 |
| Sample Rate | 7.98/sec |
| Health Score | 499% |
| Threads | 10 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (3 unique values: 52-88 cores)</summary>

```
1794848465 52
1794848470 52
1794848475 71
1794848480 71
1794848485 71
1794848490 71
1794848495 71
1794848500 71
1794848505 71
1794848510 71
1794848515 71
1794848520 71
1794848525 71
1794848530 71
1794848535 71
1794848540 71
1794848545 71
1794848550 71
1794848555 71
1794848560 71
```
</details>

---

