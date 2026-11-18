---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-18 06:38:22 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 703 |
| Sample Rate | 11.72/sec |
| Health Score | 732% |
| Threads | 10 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (3 unique values: 56-64 cores)</summary>

```
1795001572 56
1795001577 56
1795001582 56
1795001587 56
1795001592 56
1795001597 56
1795001602 56
1795001607 56
1795001612 56
1795001617 56
1795001622 56
1795001627 56
1795001632 56
1795001637 56
1795001642 64
1795001647 64
1795001652 64
1795001657 64
1795001662 62
1795001667 62
```
</details>

---

