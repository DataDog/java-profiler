---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-10 14:54:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 11 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 787 |
| Sample Rate | 13.12/sec |
| Health Score | 820% |
| Threads | 11 |
| Allocations | 464 |

<details>
<summary>CPU Timeline (2 unique values: 31-48 cores)</summary>

```
1794340242 48
1794340247 48
1794340252 48
1794340257 48
1794340262 48
1794340267 48
1794340272 48
1794340277 48
1794340282 48
1794340287 48
1794340292 48
1794340297 48
1794340302 48
1794340307 48
1794340312 48
1794340317 48
1794340322 48
1794340327 48
1794340332 31
1794340337 31
```
</details>

---

