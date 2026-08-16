---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-16 05:46:48 EDT

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 10 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1027 |
| Sample Rate | 17.12/sec |
| Health Score | 1070% |
| Threads | 12 |
| Allocations | 484 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1786873383 79
1786873388 79
1786873393 79
1786873398 79
1786873403 79
1786873408 79
1786873413 79
1786873418 81
1786873423 81
1786873428 81
1786873433 81
1786873438 81
1786873443 81
1786873448 81
1786873453 81
1786873458 81
1786873463 81
1786873468 81
1786873473 81
1786873478 81
```
</details>

---

