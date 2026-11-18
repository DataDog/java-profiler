---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-18 13:48:37 EST

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
| CPU Cores (start) | 51 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 401 |
| Sample Rate | 6.68/sec |
| Health Score | 418% |
| Threads | 11 |
| Allocations | 195 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 12 |
| Allocations | 61 |

<details>
<summary>CPU Timeline (3 unique values: 51-64 cores)</summary>

```
1795027345 51
1795027350 51
1795027355 51
1795027360 51
1795027365 51
1795027370 51
1795027375 51
1795027380 64
1795027385 64
1795027390 64
1795027395 64
1795027400 64
1795027405 64
1795027410 59
1795027415 59
1795027420 59
1795027425 59
1795027430 59
1795027435 59
1795027440 59
```
</details>

---

