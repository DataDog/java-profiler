---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-18 06:36:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 38 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 351 |
| Sample Rate | 5.85/sec |
| Health Score | 366% |
| Threads | 11 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 105 |
| Sample Rate | 1.75/sec |
| Health Score | 109% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 38-51 cores)</summary>

```
1795001572 38
1795001577 38
1795001582 38
1795001587 51
1795001592 51
1795001597 51
1795001602 51
1795001607 51
1795001612 51
1795001617 51
1795001622 51
1795001627 51
1795001632 51
1795001637 51
1795001642 51
1795001647 51
1795001652 51
1795001657 51
1795001662 51
1795001667 51
```
</details>

---

