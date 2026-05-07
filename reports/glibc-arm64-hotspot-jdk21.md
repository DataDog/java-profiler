---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-07 16:34:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 59 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 82 |
| Sample Rate | 1.37/sec |
| Health Score | 86% |
| Threads | 12 |
| Allocations | 70 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1778185661 59
1778185666 59
1778185671 59
1778185676 59
1778185681 59
1778185686 59
1778185691 59
1778185696 59
1778185701 64
1778185706 64
1778185711 64
1778185716 64
1778185721 64
1778185726 64
1778185731 64
1778185736 64
1778185741 64
1778185746 64
1778185751 64
1778185756 64
```
</details>

---

