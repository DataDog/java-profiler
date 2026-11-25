---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-25 08:34:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 68 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 537 |
| Sample Rate | 8.95/sec |
| Health Score | 559% |
| Threads | 9 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 11 |
| Allocations | 486 |

<details>
<summary>CPU Timeline (3 unique values: 68-87 cores)</summary>

```
1795613409 68
1795613414 68
1795613419 68
1795613424 87
1795613429 87
1795613434 85
1795613439 85
1795613444 85
1795613449 85
1795613454 85
1795613459 85
1795613464 85
1795613469 85
1795613474 85
1795613479 85
1795613484 85
1795613489 85
1795613494 85
1795613499 85
1795613504 85
```
</details>

---

