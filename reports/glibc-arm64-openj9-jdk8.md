---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-04 17:22:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 274 |
| Sample Rate | 4.57/sec |
| Health Score | 286% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 38 |
| Sample Rate | 0.63/sec |
| Health Score | 39% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 34-47 cores)</summary>

```
1793830750 36
1793830755 36
1793830760 36
1793830765 36
1793830770 41
1793830775 41
1793830780 36
1793830785 36
1793830790 47
1793830795 47
1793830800 47
1793830805 47
1793830810 34
1793830815 34
1793830820 34
1793830825 34
1793830830 34
1793830835 34
1793830840 34
1793830845 34
```
</details>

---

