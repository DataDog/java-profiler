---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-22 10:36:59 EDT

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 96 |
| Sample Rate | 1.60/sec |
| Health Score | 100% |
| Threads | 14 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 11 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 40-48 cores)</summary>

```
1790087470 40
1790087475 40
1790087480 40
1790087485 40
1790087490 40
1790087495 40
1790087500 40
1790087505 40
1790087510 40
1790087515 40
1790087520 40
1790087525 40
1790087530 40
1790087535 40
1790087540 40
1790087545 40
1790087550 40
1790087555 40
1790087560 40
1790087565 40
```
</details>

---

