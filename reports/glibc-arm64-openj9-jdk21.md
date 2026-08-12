---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-12 00:57:47 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 18 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 261 |
| Sample Rate | 4.35/sec |
| Health Score | 272% |
| Threads | 11 |
| Allocations | 173 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 128 |
| Sample Rate | 2.13/sec |
| Health Score | 133% |
| Threads | 11 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 16-18 cores)</summary>

```
1786510433 18
1786510438 18
1786510443 18
1786510448 18
1786510453 18
1786510458 18
1786510463 18
1786510468 16
1786510473 16
1786510478 16
1786510483 16
1786510488 16
1786510493 16
1786510498 16
1786510503 16
1786510508 16
1786510513 16
1786510518 18
1786510523 18
1786510528 18
```
</details>

---

