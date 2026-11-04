---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-04 17:02:41 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 54 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 10 |
| Allocations | 456 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 11 |
| Allocations | 502 |

<details>
<summary>CPU Timeline (2 unique values: 52-54 cores)</summary>

```
1793829473 52
1793829478 52
1793829483 52
1793829488 52
1793829493 52
1793829498 52
1793829503 52
1793829508 52
1793829513 52
1793829518 52
1793829523 52
1793829528 52
1793829533 52
1793829538 52
1793829543 52
1793829548 52
1793829553 52
1793829558 52
1793829563 52
1793829568 52
```
</details>

---

