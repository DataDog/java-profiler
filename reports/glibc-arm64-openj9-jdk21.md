---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-20 21:23:20 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 541 |
| Sample Rate | 9.02/sec |
| Health Score | 564% |
| Threads | 9 |
| Allocations | 327 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 244 |
| Sample Rate | 4.07/sec |
| Health Score | 254% |
| Threads | 11 |
| Allocations | 133 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789953518 48
1789953523 48
1789953528 48
1789953533 48
1789953538 48
1789953543 48
1789953549 48
1789953554 48
1789953559 48
1789953564 48
1789953569 48
1789953574 48
1789953579 48
1789953584 48
1789953589 48
1789953594 48
1789953599 48
1789953604 48
1789953609 43
1789953614 43
```
</details>

---

