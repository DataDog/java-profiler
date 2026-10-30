---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-30 09:45:21 EDT

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
| CPU Cores (start) | 44 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 13 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (3 unique values: 39-44 cores)</summary>

```
1793367635 44
1793367640 44
1793367645 39
1793367650 39
1793367655 39
1793367660 39
1793367665 39
1793367670 39
1793367675 39
1793367680 39
1793367685 39
1793367690 39
1793367695 39
1793367700 39
1793367705 39
1793367710 39
1793367715 42
1793367720 42
1793367725 42
1793367730 42
```
</details>

---

