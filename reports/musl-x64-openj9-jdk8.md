---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-24 09:14:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 72 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 149 |
| Sample Rate | 2.48/sec |
| Health Score | 155% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 214 |
| Sample Rate | 3.57/sec |
| Health Score | 223% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (5 unique values: 72-92 cores)</summary>

```
1795529327 72
1795529332 72
1795529337 72
1795529342 72
1795529347 75
1795529352 75
1795529357 75
1795529362 75
1795529367 75
1795529372 75
1795529377 73
1795529382 73
1795529387 73
1795529392 73
1795529397 90
1795529402 90
1795529407 90
1795529412 90
1795529417 90
1795529422 90
```
</details>

---

