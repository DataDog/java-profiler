---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-30 13:02:40 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 323 |
| Sample Rate | 5.38/sec |
| Health Score | 336% |
| Threads | 11 |
| Allocations | 135 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 335 |
| Sample Rate | 5.58/sec |
| Health Score | 349% |
| Threads | 13 |
| Allocations | 136 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1790787398 43
1790787403 43
1790787408 43
1790787413 43
1790787418 43
1790787423 43
1790787428 43
1790787433 43
1790787438 43
1790787443 48
1790787448 48
1790787453 48
1790787458 48
1790787463 48
1790787468 48
1790787473 48
1790787478 48
1790787483 48
1790787488 48
1790787493 48
```
</details>

---

