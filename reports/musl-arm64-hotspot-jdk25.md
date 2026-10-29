---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-29 13:49:36 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 12 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 13 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (2 unique values: 47-48 cores)</summary>

```
1793295792 48
1793295797 48
1793295802 48
1793295807 48
1793295812 48
1793295817 48
1793295822 48
1793295827 48
1793295832 48
1793295837 48
1793295842 48
1793295847 48
1793295852 48
1793295857 48
1793295862 48
1793295867 48
1793295872 48
1793295877 48
1793295882 48
1793295887 47
```
</details>

---

