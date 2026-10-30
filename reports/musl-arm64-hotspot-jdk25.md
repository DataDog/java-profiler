---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-30 13:48:58 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 587 |
| Sample Rate | 9.78/sec |
| Health Score | 611% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 794 |
| Sample Rate | 13.23/sec |
| Health Score | 827% |
| Threads | 12 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793382263 48
1793382268 48
1793382273 48
1793382278 48
1793382283 48
1793382288 48
1793382293 43
1793382298 43
1793382303 43
1793382308 43
1793382313 43
1793382318 43
1793382323 43
1793382328 43
1793382333 43
1793382338 43
1793382343 43
1793382348 43
1793382354 43
1793382359 43
```
</details>

---

