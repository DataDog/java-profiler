---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-12 05:48:01 EDT

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
| CPU Cores (start) | 23 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 652 |
| Sample Rate | 10.87/sec |
| Health Score | 679% |
| Threads | 11 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (5 unique values: 23-38 cores)</summary>

```
1786527797 23
1786527802 23
1786527807 23
1786527812 23
1786527817 23
1786527822 23
1786527827 23
1786527832 23
1786527837 23
1786527842 23
1786527847 23
1786527852 23
1786527857 25
1786527862 25
1786527867 28
1786527872 28
1786527877 26
1786527882 26
1786527887 26
1786527892 26
```
</details>

---

