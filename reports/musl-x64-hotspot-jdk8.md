---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-03-13 07:10:03 EDT

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
| CPU Cores (start) | 17 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 393 |
| Sample Rate | 6.55/sec |
| Health Score | 409% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 17-38 cores)</summary>

```
1773399911 17
1773399916 19
1773399921 19
1773399926 28
1773399931 28
1773399936 33
1773399941 33
1773399946 38
1773399951 38
1773399956 36
1773399961 36
1773399966 36
1773399971 36
1773399976 36
1773399981 36
1773399986 36
1773399991 36
1773399996 36
1773400001 38
1773400006 38
```
</details>

---

