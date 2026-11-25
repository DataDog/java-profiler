---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-25 13:50:50 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 10 |
| Allocations | 74 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 363 |
| Sample Rate | 6.05/sec |
| Health Score | 378% |
| Threads | 13 |
| Allocations | 117 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795632432 64
1795632437 64
1795632442 64
1795632447 64
1795632452 64
1795632457 64
1795632462 64
1795632467 64
1795632472 64
1795632477 64
1795632482 64
1795632487 64
1795632492 64
1795632497 64
1795632502 64
1795632507 64
1795632512 64
1795632517 64
1795632523 64
1795632528 64
```
</details>

---

