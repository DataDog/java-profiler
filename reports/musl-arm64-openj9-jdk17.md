---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-08-07 05:50:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 251 |
| Sample Rate | 4.18/sec |
| Health Score | 261% |
| Threads | 9 |
| Allocations | 153 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 711 |
| Sample Rate | 11.85/sec |
| Health Score | 741% |
| Threads | 11 |
| Allocations | 457 |

<details>
<summary>CPU Timeline (2 unique values: 31-32 cores)</summary>

```
1786095974 32
1786095979 32
1786095984 32
1786095989 32
1786095994 32
1786095999 32
1786096004 32
1786096009 32
1786096014 32
1786096019 31
1786096024 31
1786096029 31
1786096034 31
1786096039 31
1786096044 31
1786096049 31
1786096054 31
1786096059 31
1786096064 31
1786096069 31
```
</details>

---

