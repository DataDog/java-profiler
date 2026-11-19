---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-19 11:31:11 EST

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 357 |
| Sample Rate | 5.95/sec |
| Health Score | 372% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 187 |
| Sample Rate | 3.12/sec |
| Health Score | 195% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 58-63 cores)</summary>

```
1795105578 63
1795105583 63
1795105588 63
1795105593 63
1795105598 63
1795105603 63
1795105608 63
1795105613 63
1795105618 63
1795105623 63
1795105628 63
1795105633 63
1795105638 63
1795105643 63
1795105648 63
1795105653 63
1795105658 63
1795105663 58
1795105668 58
1795105673 58
```
</details>

---

