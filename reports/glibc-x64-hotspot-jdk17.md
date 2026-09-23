---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-23 12:10:42 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 63 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 582 |
| Sample Rate | 9.70/sec |
| Health Score | 606% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 559 |
| Sample Rate | 9.32/sec |
| Health Score | 582% |
| Threads | 11 |
| Allocations | 454 |

<details>
<summary>CPU Timeline (6 unique values: 59-71 cores)</summary>

```
1790179469 63
1790179474 63
1790179479 63
1790179484 63
1790179489 63
1790179494 63
1790179499 63
1790179504 63
1790179509 61
1790179514 61
1790179519 61
1790179524 61
1790179529 59
1790179534 59
1790179539 59
1790179544 59
1790179549 65
1790179554 65
1790179559 65
1790179564 69
```
</details>

---

