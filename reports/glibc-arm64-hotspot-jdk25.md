---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-08-25 08:39:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 9 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 13 |
| Allocations | 62 |

<details>
<summary>CPU Timeline (2 unique values: 28-48 cores)</summary>

```
1787661345 48
1787661350 48
1787661355 48
1787661360 48
1787661365 48
1787661370 48
1787661375 48
1787661380 48
1787661385 48
1787661390 48
1787661395 28
1787661400 28
1787661405 28
1787661410 28
1787661415 28
1787661420 28
1787661425 28
1787661430 28
1787661435 28
1787661440 28
```
</details>

---

