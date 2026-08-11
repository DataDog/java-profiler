---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-11 05:49:16 EDT

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
| CPU Cores (start) | 28 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 316 |
| Sample Rate | 5.27/sec |
| Health Score | 329% |
| Threads | 10 |
| Allocations | 214 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 40 |

<details>
<summary>CPU Timeline (3 unique values: 28-64 cores)</summary>

```
1786441485 28
1786441490 28
1786441495 28
1786441500 28
1786441505 28
1786441510 28
1786441515 28
1786441520 28
1786441525 28
1786441530 28
1786441535 28
1786441540 28
1786441545 28
1786441550 28
1786441555 28
1786441560 30
1786441565 30
1786441570 30
1786441575 30
1786441580 30
```
</details>

---

