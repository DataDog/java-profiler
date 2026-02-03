---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-03 11:18:49 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 780 |
| Sample Rate | 13.00/sec |
| Health Score | 812% |
| Threads | 9 |
| Allocations | 516 |

<details>
<summary>CPU Timeline (3 unique values: 24-32 cores)</summary>

```
1770135208 28
1770135213 28
1770135218 28
1770135223 28
1770135228 24
1770135233 24
1770135238 24
1770135243 24
1770135248 24
1770135253 24
1770135258 24
1770135263 32
1770135268 32
1770135273 32
1770135278 32
1770135283 32
1770135288 32
1770135293 32
1770135298 32
1770135303 32
```
</details>

---

