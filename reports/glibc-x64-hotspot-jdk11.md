---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-26 10:05:14 EDT

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
| CPU Cores (start) | 84 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 503 |
| Sample Rate | 8.38/sec |
| Health Score | 524% |
| Threads | 8 |
| Allocations | 375 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 797 |
| Sample Rate | 13.28/sec |
| Health Score | 830% |
| Threads | 10 |
| Allocations | 483 |

<details>
<summary>CPU Timeline (4 unique values: 71-86 cores)</summary>

```
1793023171 84
1793023176 84
1793023181 84
1793023186 86
1793023191 86
1793023196 86
1793023201 86
1793023206 86
1793023211 86
1793023216 86
1793023221 86
1793023226 86
1793023231 86
1793023236 86
1793023241 86
1793023246 71
1793023251 71
1793023256 71
1793023261 71
1793023266 71
```
</details>

---

