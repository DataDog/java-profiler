---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-11-25 16:21:58 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 115 |
| Sample Rate | 1.92/sec |
| Health Score | 120% |
| Threads | 9 |
| Allocations | 66 |

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
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1795641260 49
1795641265 49
1795641271 49
1795641276 49
1795641281 49
1795641286 49
1795641291 49
1795641296 49
1795641301 49
1795641306 49
1795641311 49
1795641316 49
1795641321 49
1795641326 51
1795641331 51
1795641336 51
1795641341 51
1795641346 51
1795641351 51
1795641356 51
```
</details>

---

