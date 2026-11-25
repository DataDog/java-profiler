---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 16:18:47 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 41 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 116 |
| Sample Rate | 1.93/sec |
| Health Score | 121% |
| Threads | 8 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 18 |
| Sample Rate | 0.30/sec |
| Health Score | 19% |
| Threads | 7 |
| Allocations | 9 |

<details>
<summary>CPU Timeline (3 unique values: 41-51 cores)</summary>

```
1795641223 41
1795641228 41
1795641233 41
1795641238 41
1795641243 41
1795641248 41
1795641253 51
1795641258 51
1795641263 51
1795641268 51
1795641273 51
1795641278 51
1795641283 51
1795641288 51
1795641293 51
1795641298 51
1795641303 51
1795641308 51
1795641313 51
1795641318 42
```
</details>

---

