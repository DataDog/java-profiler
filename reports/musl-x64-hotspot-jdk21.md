---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-02-03 11:12:38 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 430 |
| Sample Rate | 7.17/sec |
| Health Score | 448% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 719 |
| Sample Rate | 11.98/sec |
| Health Score | 749% |
| Threads | 11 |
| Allocations | 503 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1770134676 30
1770134681 30
1770134686 30
1770134691 30
1770134696 30
1770134701 32
1770134706 32
1770134711 32
1770134716 32
1770134721 32
1770134726 32
1770134731 32
1770134736 32
1770134741 32
1770134746 32
1770134751 32
1770134756 32
1770134761 32
1770134766 32
1770134771 32
```
</details>

---

