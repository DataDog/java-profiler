---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-25 08:42:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 50 |
| Sample Rate | 0.83/sec |
| Health Score | 52% |
| Threads | 10 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 209 |
| Sample Rate | 3.48/sec |
| Health Score | 217% |
| Threads | 14 |
| Allocations | 110 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787661424 48
1787661429 48
1787661434 48
1787661439 48
1787661444 48
1787661449 48
1787661454 48
1787661459 48
1787661464 48
1787661469 48
1787661474 48
1787661479 48
1787661484 48
1787661489 48
1787661494 48
1787661499 48
1787661504 48
1787661509 48
1787661514 48
1787661519 48
```
</details>

---

