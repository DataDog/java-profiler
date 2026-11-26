---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-26 10:18:50 EST

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
| CPU Cores (start) | 33 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 9 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 33 |
| Sample Rate | 0.55/sec |
| Health Score | 34% |
| Threads | 9 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (2 unique values: 33-64 cores)</summary>

```
1795705988 33
1795705993 33
1795705998 33
1795706003 33
1795706008 33
1795706013 64
1795706018 64
1795706023 64
1795706028 64
1795706033 33
1795706038 33
1795706043 33
1795706048 33
1795706053 33
1795706058 33
1795706063 33
1795706068 33
1795706073 33
1795706078 33
1795706083 33
```
</details>

---

