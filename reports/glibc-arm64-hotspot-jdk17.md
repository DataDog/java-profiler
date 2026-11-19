---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 12:38:10 EST

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
| CPU Cores (start) | 36 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 54 |
| Sample Rate | 0.90/sec |
| Health Score | 56% |
| Threads | 9 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 221 |
| Sample Rate | 3.68/sec |
| Health Score | 230% |
| Threads | 10 |
| Allocations | 128 |

<details>
<summary>CPU Timeline (2 unique values: 36-50 cores)</summary>

```
1795109671 36
1795109676 36
1795109681 36
1795109686 36
1795109691 50
1795109696 50
1795109701 50
1795109706 50
1795109711 50
1795109716 50
1795109721 50
1795109726 50
1795109731 50
1795109736 50
1795109741 50
1795109746 50
1795109751 50
1795109756 50
1795109761 50
1795109766 50
```
</details>

---

