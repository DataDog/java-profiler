---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-10-29 13:49:39 EDT

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
| CPU Cores (start) | 92 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 480 |
| Sample Rate | 8.00/sec |
| Health Score | 500% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 88-94 cores)</summary>

```
1793295792 92
1793295797 92
1793295802 92
1793295807 92
1793295812 92
1793295817 92
1793295822 92
1793295827 94
1793295832 94
1793295837 92
1793295842 92
1793295847 90
1793295852 90
1793295857 90
1793295862 90
1793295867 90
1793295872 90
1793295877 90
1793295882 90
1793295887 90
```
</details>

---

