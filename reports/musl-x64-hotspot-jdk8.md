---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-04 17:22:59 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 189 |
| Sample Rate | 3.15/sec |
| Health Score | 197% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 234 |
| Sample Rate | 3.90/sec |
| Health Score | 244% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 48-52 cores)</summary>

```
1793830720 50
1793830725 48
1793830730 48
1793830735 48
1793830741 48
1793830746 48
1793830751 48
1793830756 48
1793830761 48
1793830766 48
1793830771 48
1793830776 48
1793830781 48
1793830786 50
1793830791 50
1793830796 50
1793830801 50
1793830806 50
1793830811 50
1793830816 52
```
</details>

---

