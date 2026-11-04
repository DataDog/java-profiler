---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-04 17:22:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 8 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 15 |
| Sample Rate | 0.25/sec |
| Health Score | 16% |
| Threads | 10 |
| Allocations | 6 |

<details>
<summary>CPU Timeline (3 unique values: 37-42 cores)</summary>

```
1793830721 38
1793830726 38
1793830731 38
1793830736 38
1793830741 38
1793830746 38
1793830751 38
1793830756 38
1793830761 38
1793830766 38
1793830771 42
1793830776 42
1793830781 42
1793830786 42
1793830791 42
1793830796 42
1793830801 42
1793830806 42
1793830811 37
1793830816 37
```
</details>

---

