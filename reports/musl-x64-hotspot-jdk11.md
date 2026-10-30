---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-30 17:09:24 EDT

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
| CPU Cores (start) | 63 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 833 |
| Sample Rate | 13.88/sec |
| Health Score | 868% |
| Threads | 11 |
| Allocations | 532 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1793394240 63
1793394245 61
1793394250 61
1793394255 61
1793394260 61
1793394265 61
1793394270 61
1793394276 61
1793394281 61
1793394286 61
1793394291 61
1793394296 61
1793394301 61
1793394306 61
1793394311 61
1793394316 61
1793394321 61
1793394326 61
1793394331 61
1793394336 61
```
</details>

---

