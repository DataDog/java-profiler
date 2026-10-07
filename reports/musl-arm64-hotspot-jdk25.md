---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-07 10:29:47 EDT

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
| CPU Cores (start) | 43 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 8 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 9 |
| Sample Rate | 0.15/sec |
| Health Score | 9% |
| Threads | 7 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (4 unique values: 37-43 cores)</summary>

```
1791382904 43
1791382909 43
1791382914 43
1791382919 43
1791382924 37
1791382929 37
1791382934 37
1791382939 37
1791382944 37
1791382949 37
1791382954 37
1791382959 37
1791382964 37
1791382969 37
1791382974 37
1791382979 37
1791382984 42
1791382989 42
1791382994 43
1791382999 43
```
</details>

---

