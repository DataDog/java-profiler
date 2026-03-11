---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-03-11 14:07:38 EDT

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
| CPU Cores (start) | 42 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 8 |
| Allocations | 378 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 11 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (3 unique values: 41-44 cores)</summary>

```
1773252172 42
1773252177 42
1773252182 44
1773252187 44
1773252192 44
1773252197 44
1773252202 44
1773252207 44
1773252212 44
1773252217 44
1773252223 44
1773252228 44
1773252233 44
1773252238 44
1773252243 41
1773252248 41
1773252253 44
1773252258 44
1773252263 44
1773252268 44
```
</details>

---

