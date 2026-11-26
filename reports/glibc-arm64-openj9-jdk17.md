---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-26 10:28:34 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 47 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 65 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 8 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (2 unique values: 47-64 cores)</summary>

```
1795706649 47
1795706654 47
1795706660 47
1795706665 47
1795706670 47
1795706675 47
1795706680 47
1795706685 47
1795706690 47
1795706695 47
1795706700 47
1795706705 47
1795706710 64
1795706715 64
1795706720 64
1795706725 64
1795706730 47
1795706735 47
1795706740 47
1795706745 47
```
</details>

---

