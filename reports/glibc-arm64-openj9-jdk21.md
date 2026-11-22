---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-22 15:36:11 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 9 |
| Allocations | 53 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 11 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795379520 34
1795379525 34
1795379530 34
1795379535 34
1795379540 29
1795379545 29
1795379550 29
1795379555 29
1795379560 29
1795379565 29
1795379570 29
1795379575 29
1795379580 29
1795379585 29
1795379590 34
1795379595 34
1795379600 29
1795379605 29
1795379610 29
1795379615 29
```
</details>

---

