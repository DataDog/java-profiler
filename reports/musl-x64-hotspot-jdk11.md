---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-14 04:46:46 EDT

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 581 |
| Sample Rate | 9.68/sec |
| Health Score | 605% |
| Threads | 8 |
| Allocations | 394 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 730 |
| Sample Rate | 12.17/sec |
| Health Score | 761% |
| Threads | 9 |
| Allocations | 540 |

<details>
<summary>CPU Timeline (5 unique values: 39-44 cores)</summary>

```
1776156095 41
1776156100 41
1776156105 41
1776156110 39
1776156115 39
1776156120 39
1776156125 39
1776156130 39
1776156135 39
1776156140 39
1776156145 39
1776156150 44
1776156155 44
1776156160 42
1776156165 42
1776156170 42
1776156175 42
1776156180 42
1776156185 42
1776156190 42
```
</details>

---

