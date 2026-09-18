---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-18 11:14:00 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 439 |
| Sample Rate | 7.32/sec |
| Health Score | 458% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 631 |
| Sample Rate | 10.52/sec |
| Health Score | 657% |
| Threads | 10 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (3 unique values: 33-43 cores)</summary>

```
1789743327 35
1789743332 35
1789743337 35
1789743342 35
1789743347 35
1789743352 35
1789743357 35
1789743362 35
1789743367 35
1789743372 35
1789743377 43
1789743382 43
1789743387 43
1789743392 43
1789743397 33
1789743402 33
1789743407 33
1789743412 33
1789743417 33
1789743422 33
```
</details>

---

