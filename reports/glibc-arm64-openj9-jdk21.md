---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-01-30 05:41:41 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 5 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 71 |
| Sample Rate | 1.18/sec |
| Health Score | 74% |
| Threads | 8 |
| Allocations | 34 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769769473 24
1769769478 24
1769769483 24
1769769488 24
1769769493 24
1769769498 24
1769769503 24
1769769508 24
1769769513 24
1769769518 24
1769769523 24
1769769528 24
1769769533 24
1769769538 24
1769769543 24
1769769548 24
1769769553 24
1769769558 24
1769769563 24
1769769568 24
```
</details>

---

