---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-28 07:43:22 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 204 |
| Sample Rate | 3.40/sec |
| Health Score | 212% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 68-80 cores)</summary>

```
1793187434 78
1793187439 80
1793187444 80
1793187449 72
1793187454 72
1793187459 72
1793187464 72
1793187469 72
1793187474 72
1793187479 72
1793187484 72
1793187489 72
1793187494 72
1793187499 72
1793187504 72
1793187509 72
1793187514 72
1793187519 72
1793187524 72
1793187529 72
```
</details>

---

