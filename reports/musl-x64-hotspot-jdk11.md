---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-02 10:55:37 EST

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 653 |
| Sample Rate | 10.88/sec |
| Health Score | 680% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 874 |
| Sample Rate | 14.57/sec |
| Health Score | 911% |
| Threads | 9 |
| Allocations | 565 |

<details>
<summary>CPU Timeline (3 unique values: 31-52 cores)</summary>

```
1793634652 52
1793634657 52
1793634662 52
1793634667 52
1793634672 52
1793634677 52
1793634682 52
1793634687 52
1793634692 52
1793634697 52
1793634702 52
1793634707 52
1793634712 52
1793634717 52
1793634722 31
1793634727 31
1793634732 31
1793634737 31
1793634742 48
1793634747 48
```
</details>

---

