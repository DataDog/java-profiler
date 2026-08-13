---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-13 15:42:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 53 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 8 |
| Allocations | 48 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 13 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (4 unique values: 50-59 cores)</summary>

```
1786649895 59
1786649900 50
1786649905 50
1786649910 50
1786649915 50
1786649920 54
1786649925 54
1786649930 54
1786649935 54
1786649940 54
1786649945 54
1786649950 54
1786649955 54
1786649960 54
1786649965 54
1786649970 54
1786649975 54
1786649980 54
1786649985 54
1786649990 54
```
</details>

---

