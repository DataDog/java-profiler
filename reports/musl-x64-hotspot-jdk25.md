---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-15 16:13:28 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 492 |
| Sample Rate | 8.20/sec |
| Health Score | 512% |
| Threads | 9 |
| Allocations | 373 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 610 |
| Sample Rate | 10.17/sec |
| Health Score | 636% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (3 unique values: 37-52 cores)</summary>

```
1794776893 37
1794776898 37
1794776903 37
1794776908 37
1794776913 37
1794776918 37
1794776923 37
1794776928 43
1794776933 43
1794776938 43
1794776943 43
1794776948 43
1794776953 43
1794776958 43
1794776963 43
1794776968 43
1794776973 43
1794776978 43
1794776983 43
1794776988 43
```
</details>

---

