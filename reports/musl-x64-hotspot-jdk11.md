---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 09:14:34 EST

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 82 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 533 |
| Sample Rate | 8.88/sec |
| Health Score | 555% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 749 |
| Sample Rate | 12.48/sec |
| Health Score | 780% |
| Threads | 9 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (3 unique values: 80-84 cores)</summary>

```
1795529332 80
1795529337 80
1795529342 80
1795529347 80
1795529352 82
1795529357 82
1795529362 84
1795529367 84
1795529372 84
1795529377 84
1795529382 84
1795529387 84
1795529392 84
1795529397 84
1795529402 84
1795529407 84
1795529412 84
1795529417 84
1795529422 82
1795529427 82
```
</details>

---

