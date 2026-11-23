---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-23 05:28:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 9 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 274 |
| Sample Rate | 4.57/sec |
| Health Score | 286% |
| Threads | 12 |
| Allocations | 132 |

<details>
<summary>CPU Timeline (3 unique values: 29-34 cores)</summary>

```
1795429480 29
1795429485 29
1795429490 29
1795429495 29
1795429500 29
1795429505 29
1795429510 29
1795429515 29
1795429520 29
1795429525 29
1795429530 34
1795429535 34
1795429540 30
1795429545 30
1795429550 30
1795429555 30
1795429560 30
1795429565 30
1795429570 30
1795429575 30
```
</details>

---

