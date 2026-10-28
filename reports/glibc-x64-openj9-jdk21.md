---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-28 12:04:39 EDT

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
| CPU Cores (start) | 70 |
| CPU Cores (end) | 60 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 460 |
| Sample Rate | 7.67/sec |
| Health Score | 479% |
| Threads | 9 |
| Allocations | 348 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 602 |
| Sample Rate | 10.03/sec |
| Health Score | 627% |
| Threads | 11 |
| Allocations | 426 |

<details>
<summary>CPU Timeline (3 unique values: 60-70 cores)</summary>

```
1793203172 70
1793203177 70
1793203182 70
1793203187 70
1793203192 70
1793203197 68
1793203202 68
1793203207 68
1793203212 68
1793203217 68
1793203222 68
1793203227 68
1793203232 68
1793203237 68
1793203242 68
1793203247 68
1793203252 68
1793203257 68
1793203262 68
1793203267 68
```
</details>

---

