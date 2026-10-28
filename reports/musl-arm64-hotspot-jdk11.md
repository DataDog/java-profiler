---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-28 07:17:15 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 34 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 106 |
| Sample Rate | 1.77/sec |
| Health Score | 111% |
| Threads | 9 |
| Allocations | 39 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 411 |
| Sample Rate | 6.85/sec |
| Health Score | 428% |
| Threads | 13 |
| Allocations | 142 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1793185676 34
1793185681 34
1793185686 34
1793185691 34
1793185696 34
1793185701 34
1793185706 34
1793185711 34
1793185716 34
1793185721 34
1793185726 39
1793185731 39
1793185736 39
1793185741 39
1793185746 39
1793185751 39
1793185756 39
1793185761 39
1793185766 39
1793185771 39
```
</details>

---

