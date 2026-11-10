---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-10 11:01:18 EST

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
| CPU Cores (start) | 60 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 498 |
| Sample Rate | 8.30/sec |
| Health Score | 519% |
| Threads | 9 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 640 |
| Sample Rate | 10.67/sec |
| Health Score | 667% |
| Threads | 11 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (5 unique values: 52-74 cores)</summary>

```
1794326095 60
1794326100 60
1794326105 71
1794326110 71
1794326115 54
1794326120 54
1794326125 54
1794326130 54
1794326136 54
1794326141 54
1794326146 54
1794326151 54
1794326156 54
1794326161 54
1794326166 54
1794326171 54
1794326176 52
1794326181 52
1794326186 52
1794326191 52
```
</details>

---

