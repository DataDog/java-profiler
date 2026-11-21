---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-21 00:02:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 15 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 8 |
| Allocations | 349 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 9 |
| Allocations | 521 |

<details>
<summary>CPU Timeline (3 unique values: 13-48 cores)</summary>

```
1795237082 15
1795237087 15
1795237092 15
1795237097 15
1795237102 15
1795237107 15
1795237112 15
1795237117 13
1795237122 13
1795237127 13
1795237132 13
1795237137 13
1795237142 13
1795237147 13
1795237152 13
1795237157 13
1795237162 48
1795237167 48
1795237172 48
1795237177 48
```
</details>

---

