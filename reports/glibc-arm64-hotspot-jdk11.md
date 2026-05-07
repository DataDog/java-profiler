---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-05-07 09:00:13 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 56 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 9 |
| Allocations | 86 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 91 |
| Sample Rate | 1.52/sec |
| Health Score | 95% |
| Threads | 12 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (3 unique values: 40-56 cores)</summary>

```
1778158395 56
1778158400 56
1778158405 56
1778158411 56
1778158416 40
1778158421 40
1778158426 40
1778158431 40
1778158436 40
1778158441 40
1778158446 40
1778158451 40
1778158456 40
1778158461 40
1778158466 40
1778158471 40
1778158476 40
1778158481 40
1778158486 40
1778158491 40
```
</details>

---

