---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-19 08:02:14 EST

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
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 353 |
| Sample Rate | 5.88/sec |
| Health Score | 368% |
| Threads | 9 |
| Allocations | 369 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 12 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (9 unique values: 45-61 cores)</summary>

```
1795093115 48
1795093120 48
1795093125 50
1795093130 50
1795093135 48
1795093140 48
1795093145 48
1795093150 48
1795093155 49
1795093160 49
1795093165 51
1795093170 51
1795093175 51
1795093180 51
1795093185 51
1795093191 53
1795093196 53
1795093201 58
1795093206 58
1795093211 60
```
</details>

---

