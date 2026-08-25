---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-25 11:03:31 EDT

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 313 |
| Sample Rate | 5.22/sec |
| Health Score | 326% |
| Threads | 12 |
| Allocations | 181 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 14 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1787669861 29
1787669866 29
1787669871 29
1787669877 29
1787669882 29
1787669887 29
1787669892 34
1787669897 34
1787669902 29
1787669907 29
1787669912 29
1787669917 29
1787669922 29
1787669927 29
1787669932 29
1787669937 29
1787669942 29
1787669947 29
1787669952 29
1787669957 29
```
</details>

---

