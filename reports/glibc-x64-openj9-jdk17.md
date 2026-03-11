---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-03-11 14:07:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 65 |
| CPU Cores (end) | 69 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 603 |
| Sample Rate | 10.05/sec |
| Health Score | 628% |
| Threads | 9 |
| Allocations | 360 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 921 |
| Sample Rate | 15.35/sec |
| Health Score | 959% |
| Threads | 12 |
| Allocations | 462 |

<details>
<summary>CPU Timeline (4 unique values: 64-69 cores)</summary>

```
1773252219 65
1773252224 65
1773252229 65
1773252234 67
1773252239 67
1773252244 67
1773252249 67
1773252254 64
1773252259 64
1773252264 64
1773252269 64
1773252274 64
1773252279 64
1773252284 64
1773252289 64
1773252294 64
1773252299 64
1773252305 64
1773252310 64
1773252315 64
```
</details>

---

