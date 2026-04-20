---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-04-20 09:29:36 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 661 |
| Sample Rate | 11.02/sec |
| Health Score | 689% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 9 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (2 unique values: 31-32 cores)</summary>

```
1776691523 32
1776691528 32
1776691533 32
1776691538 32
1776691543 32
1776691548 32
1776691554 32
1776691559 32
1776691564 32
1776691569 32
1776691574 32
1776691579 31
1776691584 31
1776691589 31
1776691594 31
1776691599 31
1776691604 31
1776691609 32
1776691614 32
1776691619 32
```
</details>

---

