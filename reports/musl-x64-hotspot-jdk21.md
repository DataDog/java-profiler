---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-27 11:01:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 596 |
| Sample Rate | 9.93/sec |
| Health Score | 621% |
| Threads | 8 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 656 |
| Sample Rate | 10.93/sec |
| Health Score | 683% |
| Threads | 8 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (2 unique values: 27-29 cores)</summary>

```
1793112874 29
1793112879 29
1793112884 29
1793112889 29
1793112894 29
1793112899 29
1793112904 27
1793112909 27
1793112914 27
1793112919 27
1793112924 27
1793112929 27
1793112934 27
1793112939 27
1793112944 27
1793112949 27
1793112954 27
1793112959 27
1793112964 27
1793112969 27
```
</details>

---

