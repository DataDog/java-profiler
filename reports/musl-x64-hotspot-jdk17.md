---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 12:18:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 518 |
| Sample Rate | 8.63/sec |
| Health Score | 539% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 698 |
| Sample Rate | 11.63/sec |
| Health Score | 727% |
| Threads | 10 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (4 unique values: 68-81 cores)</summary>

```
1795626746 81
1795626751 81
1795626756 81
1795626761 81
1795626766 81
1795626771 81
1795626776 72
1795626781 72
1795626786 72
1795626791 72
1795626796 72
1795626801 70
1795626806 70
1795626811 68
1795626816 68
1795626822 68
1795626827 68
1795626832 68
1795626837 68
1795626842 68
```
</details>

---

