---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-22 15:41:01 EST

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
| CPU Cores (start) | 24 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 321 |
| Sample Rate | 5.35/sec |
| Health Score | 334% |
| Threads | 9 |
| Allocations | 168 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 10 |
| Allocations | 38 |

<details>
<summary>CPU Timeline (2 unique values: 24-29 cores)</summary>

```
1795379774 24
1795379779 24
1795379784 24
1795379789 24
1795379794 24
1795379799 24
1795379804 24
1795379809 24
1795379814 24
1795379819 24
1795379824 24
1795379829 24
1795379834 24
1795379839 24
1795379844 24
1795379849 29
1795379854 29
1795379859 29
1795379864 29
1795379869 29
```
</details>

---

