---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-24 05:38:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 585 |
| Sample Rate | 9.75/sec |
| Health Score | 609% |
| Threads | 9 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 812 |
| Sample Rate | 13.53/sec |
| Health Score | 846% |
| Threads | 10 |
| Allocations | 533 |

<details>
<summary>CPU Timeline (3 unique values: 63-96 cores)</summary>

```
1792834341 63
1792834346 63
1792834351 63
1792834356 96
1792834361 96
1792834366 96
1792834371 96
1792834376 96
1792834381 96
1792834386 96
1792834391 83
1792834396 83
1792834401 83
1792834406 83
1792834411 83
1792834416 83
1792834421 83
1792834426 83
1792834431 83
1792834436 83
```
</details>

---

