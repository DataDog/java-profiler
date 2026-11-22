---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-22 15:55:19 EST

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 29 |
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
| CPU Samples | 114 |
| Sample Rate | 1.90/sec |
| Health Score | 119% |
| Threads | 9 |
| Allocations | 58 |

<details>
<summary>CPU Timeline (3 unique values: 17-29 cores)</summary>

```
1795380691 22
1795380696 22
1795380701 22
1795380706 22
1795380711 22
1795380716 22
1795380721 22
1795380726 22
1795380731 17
1795380736 17
1795380741 17
1795380746 17
1795380751 17
1795380756 17
1795380761 17
1795380766 17
1795380771 29
1795380776 29
1795380781 29
1795380786 29
```
</details>

---

