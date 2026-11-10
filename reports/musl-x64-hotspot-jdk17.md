---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 15:22:40 EST

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
| CPU Cores (start) | 85 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 785 |
| Sample Rate | 13.08/sec |
| Health Score | 817% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (5 unique values: 85-93 cores)</summary>

```
1794341761 85
1794341766 87
1794341771 87
1794341776 87
1794341781 87
1794341786 87
1794341791 87
1794341796 89
1794341801 89
1794341806 89
1794341811 89
1794341816 89
1794341821 89
1794341826 89
1794341831 89
1794341836 89
1794341841 89
1794341846 89
1794341851 91
1794341856 91
```
</details>

---

