---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-01 00:59:50 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 9 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 495 |
| Sample Rate | 8.25/sec |
| Health Score | 516% |
| Threads | 10 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 660 |
| Sample Rate | 11.00/sec |
| Health Score | 688% |
| Threads | 10 |
| Allocations | 491 |

<details>
<summary>CPU Timeline (3 unique values: 9-81 cores)</summary>

```
1790830461 9
1790830466 9
1790830471 9
1790830476 9
1790830481 9
1790830486 9
1790830491 9
1790830496 9
1790830501 9
1790830506 9
1790830511 9
1790830516 42
1790830521 42
1790830526 42
1790830531 42
1790830536 42
1790830541 42
1790830546 42
1790830551 42
1790830556 42
```
</details>

---

