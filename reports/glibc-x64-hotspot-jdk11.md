---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-11 05:49:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 8 |
| CPU Cores (end) | 8 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 486 |
| Sample Rate | 8.10/sec |
| Health Score | 506% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 624 |
| Sample Rate | 10.40/sec |
| Health Score | 650% |
| Threads | 10 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (2 unique values: 6-8 cores)</summary>

```
1786441491 8
1786441496 8
1786441501 8
1786441506 8
1786441511 8
1786441516 6
1786441521 6
1786441526 6
1786441531 6
1786441536 6
1786441541 6
1786441546 6
1786441551 6
1786441556 6
1786441561 6
1786441566 6
1786441571 6
1786441576 8
1786441581 8
1786441586 8
```
</details>

---

