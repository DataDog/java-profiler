---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-24 05:38:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 62 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 435 |
| Sample Rate | 7.25/sec |
| Health Score | 453% |
| Threads | 9 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 639 |
| Sample Rate | 10.65/sec |
| Health Score | 666% |
| Threads | 11 |
| Allocations | 427 |

<details>
<summary>CPU Timeline (3 unique values: 24-62 cores)</summary>

```
1792834370 62
1792834375 62
1792834381 62
1792834386 62
1792834391 62
1792834396 62
1792834401 62
1792834406 29
1792834411 29
1792834416 24
1792834421 24
1792834426 24
1792834431 24
1792834436 24
1792834441 24
1792834446 24
1792834451 24
1792834456 24
1792834461 24
1792834466 24
```
</details>

---

