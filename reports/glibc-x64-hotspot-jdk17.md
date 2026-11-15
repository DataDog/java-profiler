---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-15 18:02:45 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 20 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 536 |
| Sample Rate | 8.93/sec |
| Health Score | 558% |
| Threads | 10 |
| Allocations | 507 |

<details>
<summary>CPU Timeline (4 unique values: 20-42 cores)</summary>

```
1794783578 20
1794783583 20
1794783588 20
1794783593 20
1794783598 20
1794783603 20
1794783608 20
1794783613 25
1794783618 25
1794783623 25
1794783628 25
1794783633 25
1794783638 25
1794783643 23
1794783648 23
1794783653 23
1794783658 23
1794783663 23
1794783668 23
1794783673 23
```
</details>

---

