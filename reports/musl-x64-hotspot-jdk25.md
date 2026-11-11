---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 19:36:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 423 |
| Sample Rate | 7.05/sec |
| Health Score | 441% |
| Threads | 8 |
| Allocations | 452 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 573 |
| Sample Rate | 9.55/sec |
| Health Score | 597% |
| Threads | 10 |
| Allocations | 561 |

<details>
<summary>CPU Timeline (3 unique values: 29-32 cores)</summary>

```
1794357128 30
1794357133 30
1794357138 30
1794357143 30
1794357148 30
1794357153 32
1794357158 32
1794357163 29
1794357168 29
1794357173 29
1794357178 29
1794357183 29
1794357188 29
1794357193 29
1794357198 29
1794357203 29
1794357208 29
1794357213 29
1794357218 29
1794357223 29
```
</details>

---

