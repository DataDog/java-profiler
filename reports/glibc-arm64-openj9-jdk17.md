---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-13 07:45:55 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 10 |
| Allocations | 423 |

<details>
<summary>CPU Timeline (2 unique values: 45-48 cores)</summary>

```
1794573566 48
1794573571 48
1794573577 48
1794573582 48
1794573587 48
1794573592 48
1794573597 48
1794573602 48
1794573607 45
1794573612 45
1794573617 45
1794573622 45
1794573627 45
1794573632 45
1794573637 45
1794573642 45
1794573647 45
1794573652 45
1794573657 45
1794573662 45
```
</details>

---

