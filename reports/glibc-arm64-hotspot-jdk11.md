---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 06:16:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 94 |
| Sample Rate | 1.57/sec |
| Health Score | 98% |
| Threads | 11 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 15 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (2 unique values: 44-49 cores)</summary>

```
1795432118 49
1795432123 49
1795432128 49
1795432133 49
1795432138 49
1795432143 49
1795432148 49
1795432153 49
1795432158 49
1795432163 49
1795432168 49
1795432173 44
1795432178 44
1795432183 44
1795432188 44
1795432193 44
1795432198 44
1795432203 44
1795432208 44
1795432213 44
```
</details>

---

