---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-13 05:53:08 EDT

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
| CPU Cores (start) | 27 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 554 |
| Sample Rate | 9.23/sec |
| Health Score | 577% |
| Threads | 8 |
| Allocations | 381 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 680 |
| Sample Rate | 11.33/sec |
| Health Score | 708% |
| Threads | 7 |
| Allocations | 524 |

<details>
<summary>CPU Timeline (3 unique values: 26-29 cores)</summary>

```
1791884895 27
1791884900 27
1791884905 27
1791884910 27
1791884915 29
1791884920 29
1791884925 26
1791884930 26
1791884935 26
1791884940 26
1791884945 26
1791884950 26
1791884955 26
1791884960 26
1791884965 26
1791884970 26
1791884975 26
1791884980 26
1791884985 26
1791884990 26
```
</details>

---

