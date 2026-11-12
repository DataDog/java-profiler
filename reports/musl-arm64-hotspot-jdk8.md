---
layout: default
title: musl-arm64-hotspot-jdk8
---

## musl-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-12 10:09:38 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 161 |
| Sample Rate | 2.68/sec |
| Health Score | 168% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 124 |
| Sample Rate | 2.07/sec |
| Health Score | 129% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1794495901 48
1794495906 48
1794495911 48
1794495916 48
1794495921 48
1794495926 48
1794495931 48
1794495936 48
1794495941 48
1794495946 48
1794495951 48
1794495956 48
1794495961 48
1794495966 48
1794495971 48
1794495976 43
1794495981 43
1794495986 43
1794495991 43
1794495996 43
```
</details>

---

