---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-24 07:51:03 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 386 |
| Sample Rate | 6.43/sec |
| Health Score | 402% |
| Threads | 12 |
| Allocations | 197 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 44 |
| Sample Rate | 0.73/sec |
| Health Score | 46% |
| Threads | 10 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1795524442 64
1795524447 64
1795524452 64
1795524457 64
1795524462 64
1795524467 64
1795524472 64
1795524477 64
1795524482 64
1795524487 64
1795524492 59
1795524497 59
1795524502 59
1795524507 59
1795524512 59
1795524517 59
1795524522 59
1795524527 59
1795524532 59
1795524537 59
```
</details>

---

