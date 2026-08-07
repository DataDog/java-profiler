---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-08-07 05:50:45 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 329 |
| Sample Rate | 5.48/sec |
| Health Score | 342% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 10-30 cores)</summary>

```
1786095969 14
1786095974 14
1786095979 14
1786095984 10
1786095989 10
1786095994 30
1786095999 30
1786096004 26
1786096009 26
1786096014 26
1786096019 26
1786096024 26
1786096029 26
1786096034 26
1786096039 26
1786096044 26
1786096049 26
1786096054 26
1786096059 26
1786096064 26
```
</details>

---

