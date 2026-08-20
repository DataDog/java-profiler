---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-20 13:25:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 94 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 591 |
| Sample Rate | 9.85/sec |
| Health Score | 616% |
| Threads | 9 |
| Allocations | 379 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 644 |
| Sample Rate | 10.73/sec |
| Health Score | 671% |
| Threads | 10 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 92-94 cores)</summary>

```
1787246438 94
1787246443 94
1787246448 94
1787246453 92
1787246458 92
1787246463 92
1787246468 92
1787246473 92
1787246478 94
1787246483 94
1787246488 94
1787246493 94
1787246498 94
1787246503 94
1787246508 94
1787246513 94
1787246518 94
1787246523 94
1787246528 94
1787246533 94
```
</details>

---

