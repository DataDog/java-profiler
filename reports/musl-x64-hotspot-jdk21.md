---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-30 13:48:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 93 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 556 |
| Sample Rate | 9.27/sec |
| Health Score | 579% |
| Threads | 9 |
| Allocations | 356 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 687 |
| Sample Rate | 11.45/sec |
| Health Score | 716% |
| Threads | 11 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (2 unique values: 73-93 cores)</summary>

```
1793382248 93
1793382253 93
1793382258 93
1793382263 93
1793382268 93
1793382273 93
1793382278 73
1793382283 73
1793382288 73
1793382293 73
1793382298 73
1793382303 73
1793382308 73
1793382313 73
1793382318 73
1793382323 73
1793382328 73
1793382333 73
1793382338 73
1793382343 73
```
</details>

---

