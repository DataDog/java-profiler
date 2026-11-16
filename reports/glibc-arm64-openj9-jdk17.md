---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 07:37:16 EST

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
| CPU Cores (start) | 41 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 372 |
| Sample Rate | 6.20/sec |
| Health Score | 388% |
| Threads | 8 |
| Allocations | 361 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 205 |
| Sample Rate | 3.42/sec |
| Health Score | 214% |
| Threads | 10 |
| Allocations | 87 |

<details>
<summary>CPU Timeline (4 unique values: 36-43 cores)</summary>

```
1794832310 41
1794832315 41
1794832320 41
1794832325 41
1794832330 41
1794832335 41
1794832340 41
1794832345 41
1794832350 41
1794832355 41
1794832360 41
1794832365 41
1794832370 41
1794832375 41
1794832380 36
1794832385 36
1794832390 36
1794832395 36
1794832400 36
1794832405 36
```
</details>

---

