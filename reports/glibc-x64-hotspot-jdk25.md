---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-24 07:51:04 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 91 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 444 |
| Sample Rate | 7.40/sec |
| Health Score | 462% |
| Threads | 9 |
| Allocations | 406 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 11 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (5 unique values: 85-94 cores)</summary>

```
1795524413 91
1795524418 91
1795524423 91
1795524428 91
1795524433 91
1795524438 91
1795524443 91
1795524448 91
1795524453 91
1795524458 91
1795524463 91
1795524468 91
1795524473 91
1795524478 91
1795524483 91
1795524488 91
1795524493 89
1795524498 89
1795524503 89
1795524508 89
```
</details>

---

