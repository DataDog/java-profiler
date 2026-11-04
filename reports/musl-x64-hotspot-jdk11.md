---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-04 17:02:41 EST

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
| CPU Cores (start) | 62 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 8.62/sec |
| Health Score | 539% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 672 |
| Sample Rate | 11.20/sec |
| Health Score | 700% |
| Threads | 9 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1793829473 62
1793829478 62
1793829483 62
1793829488 62
1793829493 62
1793829498 62
1793829503 62
1793829508 62
1793829513 62
1793829518 62
1793829523 62
1793829528 62
1793829533 62
1793829538 62
1793829543 62
1793829548 62
1793829553 62
1793829558 62
1793829563 62
1793829568 62
```
</details>

---

