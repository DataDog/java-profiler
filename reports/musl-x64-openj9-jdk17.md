---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-06 06:33:11 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 77 |
| CPU Cores (end) | 77 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 9 |
| Allocations | 364 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 971 |
| Sample Rate | 16.18/sec |
| Health Score | 1011% |
| Threads | 12 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (4 unique values: 75-79 cores)</summary>

```
1770377267 77
1770377272 77
1770377277 77
1770377282 77
1770377287 77
1770377292 77
1770377297 77
1770377302 79
1770377307 79
1770377312 79
1770377317 78
1770377322 78
1770377327 78
1770377332 78
1770377337 78
1770377342 78
1770377347 75
1770377352 75
1770377357 75
1770377362 77
```
</details>

---

