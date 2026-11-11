---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 19:36:46 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 23 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 420 |
| Sample Rate | 7.00/sec |
| Health Score | 438% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 601 |
| Sample Rate | 10.02/sec |
| Health Score | 626% |
| Threads | 10 |
| Allocations | 479 |

<details>
<summary>CPU Timeline (6 unique values: 18-29 cores)</summary>

```
1794357153 27
1794357158 27
1794357163 27
1794357168 27
1794357173 29
1794357178 29
1794357183 20
1794357188 20
1794357193 20
1794357198 20
1794357203 20
1794357208 20
1794357213 18
1794357218 18
1794357223 20
1794357228 20
1794357233 21
1794357238 21
1794357243 21
1794357248 23
```
</details>

---

