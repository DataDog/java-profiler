---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-09 16:22:26 EST

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
| CPU Cores (start) | 68 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 8 |
| Allocations | 370 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 705 |
| Sample Rate | 11.75/sec |
| Health Score | 734% |
| Threads | 10 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (6 unique values: 50-71 cores)</summary>

```
1794259101 68
1794259106 68
1794259111 62
1794259116 62
1794259121 62
1794259126 62
1794259131 62
1794259136 62
1794259141 64
1794259146 64
1794259151 64
1794259156 64
1794259161 64
1794259166 64
1794259171 64
1794259176 64
1794259181 64
1794259186 64
1794259191 64
1794259196 66
```
</details>

---

