---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-18 11:14:00 EDT

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
| CPU Cores (start) | 75 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 209 |
| Sample Rate | 3.48/sec |
| Health Score | 217% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 241 |
| Sample Rate | 4.02/sec |
| Health Score | 251% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 44-75 cores)</summary>

```
1789743362 75
1789743367 75
1789743372 75
1789743377 75
1789743382 75
1789743387 75
1789743392 75
1789743397 75
1789743402 75
1789743407 75
1789743412 75
1789743417 44
1789743422 44
1789743427 44
1789743432 44
1789743437 44
1789743442 44
1789743447 44
1789743452 44
1789743457 44
```
</details>

---

