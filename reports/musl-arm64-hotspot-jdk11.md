---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 07:54:10 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1036 |
| Sample Rate | 17.27/sec |
| Health Score | 1079% |
| Threads | 10 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795610938 64
1795610943 64
1795610948 64
1795610953 64
1795610958 64
1795610963 64
1795610968 64
1795610973 64
1795610978 64
1795610983 64
1795610988 64
1795610993 64
1795610998 64
1795611003 64
1795611008 64
1795611013 64
1795611018 64
1795611023 64
1795611028 64
1795611033 64
```
</details>

---

