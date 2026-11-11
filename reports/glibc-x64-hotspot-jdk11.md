---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-11 10:44:46 EST

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 511 |
| Sample Rate | 8.52/sec |
| Health Score | 532% |
| Threads | 8 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 773 |
| Sample Rate | 12.88/sec |
| Health Score | 805% |
| Threads | 9 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (3 unique values: 70-73 cores)</summary>

```
1794411566 70
1794411571 72
1794411576 72
1794411581 72
1794411586 72
1794411591 73
1794411596 73
1794411601 73
1794411606 73
1794411611 73
1794411616 73
1794411621 73
1794411626 73
1794411631 73
1794411636 73
1794411641 73
1794411647 73
1794411652 73
1794411657 73
1794411662 73
```
</details>

---

