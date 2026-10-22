---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 13:10:14 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 497 |
| Sample Rate | 8.28/sec |
| Health Score | 517% |
| Threads | 8 |
| Allocations | 404 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 9 |
| Allocations | 537 |

<details>
<summary>CPU Timeline (2 unique values: 41-43 cores)</summary>

```
1792688640 43
1792688645 43
1792688650 41
1792688655 41
1792688660 41
1792688665 41
1792688670 41
1792688675 41
1792688680 41
1792688686 41
1792688691 41
1792688696 43
1792688701 43
1792688706 43
1792688711 43
1792688716 43
1792688721 43
1792688726 43
1792688731 43
1792688736 43
```
</details>

---

