---
layout: default
title: glibc-x64-hotspot-jdk21
---

## glibc-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-01-29 07:01:52 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 456 |
| Sample Rate | 15.20/sec |
| Health Score | 950% |
| Threads | 9 |
| Allocations | 398 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 691 |
| Sample Rate | 23.03/sec |
| Health Score | 1439% |
| Threads | 13 |
| Allocations | 466 |

<details>
<summary>CPU Timeline (3 unique values: 59-79 cores)</summary>

```
1769687621 64
1769687626 64
1769687631 64
1769687636 64
1769687641 64
1769687646 64
1769687651 64
1769687656 64
1769687661 64
1769687666 59
1769687671 59
1769687676 59
1769687681 59
1769687686 59
1769687691 59
1769687696 59
1769687701 79
1769687706 79
1769687711 79
1769687716 79
```
</details>

---

