---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-11 14:07:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 10 |
| Allocations | 380 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 827 |
| Sample Rate | 13.78/sec |
| Health Score | 861% |
| Threads | 13 |
| Allocations | 453 |

<details>
<summary>CPU Timeline (3 unique values: 81-86 cores)</summary>

```
1773252148 82
1773252153 82
1773252158 82
1773252163 82
1773252168 82
1773252173 82
1773252178 86
1773252183 86
1773252188 86
1773252193 86
1773252198 86
1773252203 86
1773252208 86
1773252213 86
1773252218 86
1773252223 86
1773252228 86
1773252233 86
1773252238 86
1773252243 86
```
</details>

---

