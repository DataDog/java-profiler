---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 09:47:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 92 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 709 |
| Sample Rate | 11.82/sec |
| Health Score | 739% |
| Threads | 9 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (5 unique values: 87-93 cores)</summary>

```
1795099225 92
1795099230 92
1795099235 92
1795099240 92
1795099245 89
1795099250 89
1795099255 91
1795099260 91
1795099265 91
1795099270 91
1795099275 91
1795099280 93
1795099285 93
1795099290 91
1795099295 91
1795099300 91
1795099305 91
1795099310 91
1795099315 91
1795099320 89
```
</details>

---

