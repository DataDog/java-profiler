---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-03-11 14:07:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 226 |
| Sample Rate | 3.77/sec |
| Health Score | 236% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 56-68 cores)</summary>

```
1773252138 56
1773252143 68
1773252148 68
1773252153 68
1773252158 68
1773252163 68
1773252168 65
1773252173 65
1773252178 65
1773252183 65
1773252188 65
1773252193 65
1773252198 65
1773252203 65
1773252208 65
1773252213 65
1773252218 65
1773252223 65
1773252228 65
1773252233 65
```
</details>

---

