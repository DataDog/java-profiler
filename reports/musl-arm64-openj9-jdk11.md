---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-04 05:47:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
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
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 11 |
| Allocations | 67 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 14 |
| Allocations | 47 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1791107041 64
1791107046 64
1791107051 64
1791107056 64
1791107061 64
1791107066 64
1791107071 64
1791107076 64
1791107081 64
1791107086 64
1791107091 64
1791107096 64
1791107101 64
1791107106 64
1791107111 64
1791107116 64
1791107121 64
1791107126 64
1791107131 64
1791107136 64
```
</details>

---

