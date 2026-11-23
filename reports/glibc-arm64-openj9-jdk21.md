---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 11:06:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 89 |
| Sample Rate | 1.48/sec |
| Health Score | 92% |
| Threads | 10 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1795449572 64
1795449577 64
1795449582 64
1795449587 64
1795449592 64
1795449597 64
1795449602 64
1795449607 64
1795449612 64
1795449617 64
1795449622 64
1795449627 64
1795449632 64
1795449637 64
1795449642 64
1795449647 64
1795449652 64
1795449657 64
1795449662 64
1795449667 64
```
</details>

---

