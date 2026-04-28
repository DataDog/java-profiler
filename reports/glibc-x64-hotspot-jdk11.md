---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-28 11:22:29 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 548 |
| Sample Rate | 9.13/sec |
| Health Score | 571% |
| Threads | 8 |
| Allocations | 321 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1004 |
| Sample Rate | 16.73/sec |
| Health Score | 1046% |
| Threads | 10 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 40-45 cores)</summary>

```
1777389459 45
1777389464 44
1777389469 44
1777389474 44
1777389479 40
1777389484 40
1777389489 40
1777389494 40
1777389499 40
1777389504 40
1777389509 40
1777389514 40
1777389519 40
1777389524 40
1777389529 40
1777389534 40
1777389539 40
1777389544 40
1777389549 40
1777389554 40
```
</details>

---

