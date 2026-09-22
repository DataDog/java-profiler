---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-22 11:30:20 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 516 |
| Sample Rate | 8.60/sec |
| Health Score | 537% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 575 |
| Sample Rate | 9.58/sec |
| Health Score | 599% |
| Threads | 10 |
| Allocations | 514 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1790090636 32
1790090641 32
1790090646 32
1790090651 32
1790090656 32
1790090661 32
1790090666 32
1790090671 32
1790090676 32
1790090681 32
1790090686 32
1790090691 32
1790090696 32
1790090701 30
1790090706 30
1790090711 30
1790090716 30
1790090721 30
1790090726 30
1790090731 30
```
</details>

---

