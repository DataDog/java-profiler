---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 12:58:06 EST

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 88 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 379 |
| Sample Rate | 6.32/sec |
| Health Score | 395% |
| Threads | 9 |
| Allocations | 402 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 9 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (4 unique values: 75-96 cores)</summary>

```
1795542771 75
1795542776 75
1795542781 75
1795542786 75
1795542791 75
1795542796 75
1795542801 75
1795542806 75
1795542811 75
1795542816 75
1795542821 75
1795542826 75
1795542831 75
1795542836 75
1795542841 75
1795542846 75
1795542851 75
1795542856 77
1795542861 77
1795542866 96
```
</details>

---

