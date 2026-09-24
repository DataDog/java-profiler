---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 08:42:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 9 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 362 |
| Sample Rate | 6.03/sec |
| Health Score | 377% |
| Threads | 13 |
| Allocations | 129 |

<details>
<summary>CPU Timeline (2 unique values: 45-50 cores)</summary>

```
1790253467 50
1790253472 50
1790253477 50
1790253482 50
1790253487 50
1790253492 50
1790253497 50
1790253502 50
1790253507 50
1790253512 50
1790253517 50
1790253522 50
1790253527 50
1790253532 50
1790253537 50
1790253542 50
1790253547 50
1790253552 50
1790253557 50
1790253562 50
```
</details>

---

