---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 11:14:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 85 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 427 |
| Sample Rate | 7.12/sec |
| Health Score | 445% |
| Threads | 9 |
| Allocations | 390 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 11 |
| Allocations | 459 |

<details>
<summary>CPU Timeline (4 unique values: 60-96 cores)</summary>

```
1789743312 85
1789743317 85
1789743322 87
1789743327 87
1789743332 87
1789743337 96
1789743342 96
1789743347 96
1789743352 96
1789743357 96
1789743362 96
1789743367 96
1789743372 96
1789743377 96
1789743382 96
1789743387 96
1789743392 96
1789743397 60
1789743402 60
1789743407 60
```
</details>

---

