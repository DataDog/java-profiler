---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-30 11:36:49 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 8 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 9 |
| Allocations | 50 |

<details>
<summary>CPU Timeline (2 unique values: 39-48 cores)</summary>

```
1790782341 39
1790782346 39
1790782351 39
1790782356 39
1790782361 39
1790782366 39
1790782371 39
1790782376 39
1790782381 39
1790782386 39
1790782391 39
1790782396 39
1790782401 48
1790782406 48
1790782411 48
1790782416 39
1790782421 39
1790782426 39
1790782431 39
1790782436 39
```
</details>

---

