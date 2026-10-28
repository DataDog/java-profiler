---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-28 13:11:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 58 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 477 |
| Sample Rate | 7.95/sec |
| Health Score | 497% |
| Threads | 9 |
| Allocations | 405 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 710 |
| Sample Rate | 11.83/sec |
| Health Score | 739% |
| Threads | 10 |
| Allocations | 475 |

<details>
<summary>CPU Timeline (5 unique values: 54-61 cores)</summary>

```
1793207218 61
1793207223 61
1793207228 61
1793207233 61
1793207238 61
1793207243 61
1793207248 59
1793207253 59
1793207258 54
1793207263 54
1793207268 54
1793207273 56
1793207278 56
1793207283 56
1793207288 56
1793207293 56
1793207298 56
1793207303 56
1793207308 56
1793207313 56
```
</details>

---

