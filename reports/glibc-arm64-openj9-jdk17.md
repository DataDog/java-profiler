---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-20 12:12:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 14 |
| Allocations | 28 |

<details>
<summary>CPU Timeline (4 unique values: 32-38 cores)</summary>

```
1795194412 32
1795194417 32
1795194422 32
1795194427 32
1795194432 32
1795194437 32
1795194442 32
1795194447 32
1795194452 35
1795194457 35
1795194462 35
1795194467 35
1795194472 38
1795194477 38
1795194482 33
1795194487 33
1795194492 33
1795194497 33
1795194502 35
1795194507 35
```
</details>

---

