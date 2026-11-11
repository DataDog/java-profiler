---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 19:36:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 797 |
| Sample Rate | 13.28/sec |
| Health Score | 830% |
| Threads | 10 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (3 unique values: 39-86 cores)</summary>

```
1794357143 39
1794357148 39
1794357153 39
1794357158 39
1794357163 39
1794357168 86
1794357173 86
1794357178 73
1794357183 73
1794357188 73
1794357193 73
1794357198 73
1794357203 73
1794357208 73
1794357213 73
1794357218 73
1794357223 73
1794357228 73
1794357233 73
1794357238 73
```
</details>

---

