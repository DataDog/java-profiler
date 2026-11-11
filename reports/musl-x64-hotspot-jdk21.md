---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-11 05:28:43 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 78 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 485 |
| Sample Rate | 8.08/sec |
| Health Score | 505% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 704 |
| Sample Rate | 11.73/sec |
| Health Score | 733% |
| Threads | 10 |
| Allocations | 434 |

<details>
<summary>CPU Timeline (4 unique values: 63-80 cores)</summary>

```
1794392558 78
1794392563 78
1794392568 78
1794392573 78
1794392579 78
1794392584 80
1794392589 80
1794392594 80
1794392599 80
1794392604 80
1794392609 80
1794392614 80
1794392619 80
1794392624 80
1794392629 80
1794392634 80
1794392639 80
1794392644 63
1794392649 63
1794392654 63
```
</details>

---

