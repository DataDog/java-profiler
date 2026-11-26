---
layout: default
title: musl-arm64-hotspot-jdk25
---

## musl-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-26 09:26:39 EST

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 13 |
| Allocations | 67 |

<details>
<summary>CPU Timeline (2 unique values: 42-47 cores)</summary>

```
1795702911 42
1795702916 47
1795702921 47
1795702926 42
1795702931 42
1795702936 42
1795702941 42
1795702946 42
1795702951 42
1795702956 42
1795702961 42
1795702966 42
1795702971 42
1795702976 42
1795702981 42
1795702986 42
1795702991 47
1795702996 47
1795703001 47
1795703006 47
```
</details>

---

