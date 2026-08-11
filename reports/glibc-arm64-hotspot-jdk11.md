---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-11 12:25:48 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 12 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (4 unique values: 19-32 cores)</summary>

```
1786465177 20
1786465182 20
1786465187 20
1786465192 20
1786465197 20
1786465202 20
1786465207 32
1786465212 32
1786465217 32
1786465222 32
1786465227 23
1786465232 23
1786465237 23
1786465242 23
1786465247 23
1786465252 23
1786465257 23
1786465262 23
1786465267 23
1786465272 23
```
</details>

---

