---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-24 05:24:30 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 74 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 453 |
| Sample Rate | 7.55/sec |
| Health Score | 472% |
| Threads | 9 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 642 |
| Sample Rate | 10.70/sec |
| Health Score | 669% |
| Threads | 11 |
| Allocations | 485 |

<details>
<summary>CPU Timeline (2 unique values: 74-84 cores)</summary>

```
1790241587 84
1790241592 84
1790241597 84
1790241602 84
1790241607 84
1790241612 84
1790241617 84
1790241622 74
1790241627 74
1790241632 74
1790241637 74
1790241642 74
1790241647 74
1790241652 74
1790241657 74
1790241662 74
1790241667 74
1790241672 74
1790241677 74
1790241682 74
```
</details>

---

