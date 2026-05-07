---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-05-07 09:00:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 13 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (2 unique values: 47-59 cores)</summary>

```
1778158379 59
1778158384 59
1778158389 59
1778158394 59
1778158399 59
1778158404 59
1778158409 47
1778158414 47
1778158419 47
1778158424 47
1778158429 47
1778158434 47
1778158439 47
1778158444 47
1778158449 47
1778158454 47
1778158459 47
1778158464 47
1778158469 47
1778158474 47
```
</details>

---

