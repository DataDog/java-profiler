---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-22 05:47:54 EST

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
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 12 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (3 unique values: 22-29 cores)</summary>

```
1795344202 22
1795344207 24
1795344213 24
1795344218 24
1795344223 24
1795344228 24
1795344233 24
1795344238 24
1795344243 24
1795344248 24
1795344253 24
1795344258 24
1795344263 24
1795344268 29
1795344273 29
1795344278 29
1795344283 29
1795344288 29
1795344293 29
1795344298 29
```
</details>

---

