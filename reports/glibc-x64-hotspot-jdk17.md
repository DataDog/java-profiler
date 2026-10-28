---
layout: default
title: glibc-x64-hotspot-jdk17
---

## glibc-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-28 13:11:28 EDT

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
| CPU Cores (start) | 25 |
| CPU Cores (end) | 27 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 484 |
| Sample Rate | 8.07/sec |
| Health Score | 504% |
| Threads | 8 |
| Allocations | 365 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 494 |
| Sample Rate | 8.23/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (2 unique values: 25-27 cores)</summary>

```
1793207248 25
1793207254 25
1793207259 25
1793207264 25
1793207269 25
1793207274 25
1793207279 25
1793207284 25
1793207289 25
1793207294 25
1793207299 27
1793207304 27
1793207309 27
1793207314 27
1793207319 27
1793207324 27
1793207329 27
1793207334 27
1793207339 27
1793207344 27
```
</details>

---

