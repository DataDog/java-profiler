---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 06:38:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 563 |
| Sample Rate | 9.38/sec |
| Health Score | 586% |
| Threads | 9 |
| Allocations | 351 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 12 |
| Allocations | 73 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1795001577 29
1795001582 29
1795001587 29
1795001592 29
1795001597 29
1795001602 29
1795001607 29
1795001612 29
1795001617 29
1795001622 29
1795001627 29
1795001632 29
1795001637 29
1795001642 34
1795001647 34
1795001652 34
1795001657 34
1795001662 34
1795001667 34
1795001672 34
```
</details>

---

