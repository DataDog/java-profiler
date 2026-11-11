---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-11 15:22:21 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 12 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 10 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794428195 48
1794428200 48
1794428205 48
1794428210 48
1794428215 48
1794428220 43
1794428225 43
1794428230 43
1794428235 43
1794428240 43
1794428245 43
1794428250 43
1794428255 43
1794428260 43
1794428265 43
1794428270 43
1794428275 43
1794428280 43
1794428285 43
1794428290 43
```
</details>

---

