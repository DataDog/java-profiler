---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-24 11:29:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 9 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 347 |
| Sample Rate | 5.78/sec |
| Health Score | 361% |
| Threads | 11 |
| Allocations | 162 |

<details>
<summary>CPU Timeline (2 unique values: 22-34 cores)</summary>

```
1795537545 22
1795537550 22
1795537555 22
1795537560 22
1795537565 22
1795537570 22
1795537575 22
1795537580 22
1795537585 22
1795537590 22
1795537595 22
1795537600 22
1795537605 22
1795537610 22
1795537615 34
1795537620 34
1795537625 34
1795537630 34
1795537635 34
1795537640 34
```
</details>

---

