---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-07 05:50:47 EDT

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
| CPU Cores (start) | 55 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 210 |
| Sample Rate | 3.50/sec |
| Health Score | 219% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 336 |
| Sample Rate | 5.60/sec |
| Health Score | 350% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 55-88 cores)</summary>

```
1786095963 55
1786095968 55
1786095973 55
1786095978 55
1786095983 55
1786095988 55
1786095993 55
1786095998 55
1786096003 55
1786096008 55
1786096013 55
1786096018 55
1786096023 55
1786096028 55
1786096034 55
1786096039 55
1786096044 88
1786096049 88
1786096054 68
1786096059 68
```
</details>

---

