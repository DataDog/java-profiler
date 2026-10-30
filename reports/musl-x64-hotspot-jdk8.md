---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-30 13:48:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 190 |
| Sample Rate | 3.17/sec |
| Health Score | 198% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 184 |
| Sample Rate | 3.07/sec |
| Health Score | 192% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 41-44 cores)</summary>

```
1793382243 43
1793382248 43
1793382253 43
1793382258 41
1793382263 41
1793382268 41
1793382273 41
1793382278 41
1793382283 41
1793382288 41
1793382293 41
1793382298 41
1793382303 41
1793382308 41
1793382313 41
1793382318 41
1793382323 41
1793382328 41
1793382333 41
1793382338 41
```
</details>

---

