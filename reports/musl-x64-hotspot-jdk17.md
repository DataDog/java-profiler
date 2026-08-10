---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-10 11:46:29 EDT

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
| CPU Cores (start) | 80 |
| CPU Cores (end) | 76 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 690 |
| Sample Rate | 11.50/sec |
| Health Score | 719% |
| Threads | 9 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 799 |
| Sample Rate | 13.32/sec |
| Health Score | 832% |
| Threads | 11 |
| Allocations | 510 |

<details>
<summary>CPU Timeline (3 unique values: 76-80 cores)</summary>

```
1786376415 80
1786376420 80
1786376425 80
1786376430 80
1786376435 80
1786376440 80
1786376445 78
1786376450 78
1786376455 78
1786376460 78
1786376465 78
1786376470 78
1786376475 78
1786376480 78
1786376485 76
1786376490 76
1786376495 76
1786376500 76
1786376505 76
1786376510 76
```
</details>

---

