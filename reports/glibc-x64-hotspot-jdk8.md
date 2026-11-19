---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-19 09:29:51 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 186 |
| Sample Rate | 3.10/sec |
| Health Score | 194% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 327 |
| Sample Rate | 5.45/sec |
| Health Score | 341% |
| Threads | 10 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 71-77 cores)</summary>

```
1795098315 71
1795098320 71
1795098325 75
1795098330 75
1795098335 75
1795098340 75
1795098345 75
1795098350 75
1795098355 75
1795098360 77
1795098365 77
1795098370 75
1795098375 75
1795098380 75
1795098385 75
1795098390 75
1795098395 75
1795098400 75
1795098405 75
1795098410 75
```
</details>

---

