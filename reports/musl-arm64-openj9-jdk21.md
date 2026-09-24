---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-24 08:42:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 13 |
| Sample Rate | 0.22/sec |
| Health Score | 14% |
| Threads | 5 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (2 unique values: 26-31 cores)</summary>

```
1790253442 31
1790253447 31
1790253452 31
1790253457 26
1790253462 26
1790253467 26
1790253472 26
1790253477 26
1790253482 26
1790253487 26
1790253492 26
1790253497 26
1790253502 31
1790253507 31
1790253512 31
1790253517 31
1790253522 31
1790253527 31
1790253532 31
1790253537 31
```
</details>

---

