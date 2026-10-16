---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-16 10:46:17 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 11 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 8 |
| Allocations | 5 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1792161620 64
1792161625 64
1792161630 64
1792161635 64
1792161640 64
1792161645 64
1792161650 64
1792161655 64
1792161660 64
1792161665 64
1792161670 64
1792161675 64
1792161680 64
1792161685 64
1792161690 64
1792161695 64
1792161700 64
1792161705 64
1792161710 64
1792161715 64
```
</details>

---

