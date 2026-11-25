---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-25 16:21:57 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
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
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 8 |
| Allocations | 46 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 20 |
| Sample Rate | 0.33/sec |
| Health Score | 21% |
| Threads | 5 |
| Allocations | 7 |

<details>
<summary>CPU Timeline (2 unique values: 49-51 cores)</summary>

```
1795641260 49
1795641265 49
1795641270 49
1795641275 49
1795641280 49
1795641285 49
1795641290 49
1795641295 49
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

