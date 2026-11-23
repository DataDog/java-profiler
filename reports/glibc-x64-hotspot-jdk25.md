---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-23 04:42:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 372 |
| Sample Rate | 6.20/sec |
| Health Score | 388% |
| Threads | 8 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 467 |
| Sample Rate | 7.78/sec |
| Health Score | 486% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (4 unique values: 37-63 cores)</summary>

```
1795426682 37
1795426687 37
1795426692 37
1795426697 37
1795426702 37
1795426707 37
1795426712 37
1795426717 37
1795426722 37
1795426727 37
1795426732 37
1795426737 56
1795426742 56
1795426747 56
1795426752 56
1795426757 56
1795426762 56
1795426767 58
1795426772 58
1795426777 58
```
</details>

---

