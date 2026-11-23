---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-23 11:05:01 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 109 |
| Sample Rate | 1.82/sec |
| Health Score | 114% |
| Threads | 9 |
| Allocations | 78 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 104 |
| Sample Rate | 1.73/sec |
| Health Score | 108% |
| Threads | 14 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1795449531 48
1795449536 48
1795449541 48
1795449546 48
1795449551 48
1795449556 48
1795449562 48
1795449567 43
1795449572 43
1795449577 43
1795449582 43
1795449587 43
1795449592 43
1795449597 43
1795449602 43
1795449607 43
1795449612 43
1795449617 43
1795449622 43
1795449627 43
```
</details>

---

