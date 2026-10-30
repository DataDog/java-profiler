---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-30 13:48:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 202 |
| Sample Rate | 3.37/sec |
| Health Score | 211% |
| Threads | 11 |
| Allocations | 137 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 11 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1793382273 43
1793382278 43
1793382283 43
1793382288 43
1793382293 43
1793382298 43
1793382303 43
1793382308 43
1793382313 43
1793382318 43
1793382323 43
1793382328 43
1793382333 48
1793382338 48
1793382343 48
1793382348 48
1793382353 48
1793382358 48
1793382363 48
1793382368 48
```
</details>

---

