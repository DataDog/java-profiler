---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-22 08:01:51 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 29 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 473 |
| Sample Rate | 7.88/sec |
| Health Score | 492% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 561 |
| Sample Rate | 9.35/sec |
| Health Score | 584% |
| Threads | 9 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 21-29 cores)</summary>

```
1792670188 24
1792670193 24
1792670198 24
1792670203 24
1792670208 24
1792670213 24
1792670218 21
1792670223 21
1792670228 21
1792670233 21
1792670238 21
1792670243 29
1792670248 29
1792670253 29
1792670258 29
1792670263 29
1792670268 29
1792670273 29
1792670278 29
1792670283 29
```
</details>

---

