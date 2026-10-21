---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-21 06:29:48 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 544 |
| Sample Rate | 9.07/sec |
| Health Score | 567% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 807 |
| Sample Rate | 13.45/sec |
| Health Score | 841% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (5 unique values: 81-85 cores)</summary>

```
1792578324 85
1792578329 82
1792578334 82
1792578339 82
1792578344 82
1792578349 82
1792578354 82
1792578359 82
1792578364 82
1792578369 84
1792578374 84
1792578379 84
1792578384 81
1792578389 81
1792578394 81
1792578399 81
1792578404 81
1792578409 81
1792578414 81
1792578419 81
```
</details>

---

