---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-06 11:13:22 EST

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 91 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 10 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 671 |
| Sample Rate | 11.18/sec |
| Health Score | 699% |
| Threads | 13 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 91-96 cores)</summary>

```
1772813280 96
1772813285 96
1772813290 96
1772813295 96
1772813300 96
1772813305 96
1772813310 96
1772813315 96
1772813320 96
1772813325 96
1772813330 96
1772813335 96
1772813340 96
1772813345 96
1772813350 96
1772813355 96
1772813360 91
1772813365 91
1772813370 91
1772813375 91
```
</details>

---

