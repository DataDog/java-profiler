---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-02 11:43:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 76 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 8 |
| Allocations | 383 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 675 |
| Sample Rate | 11.25/sec |
| Health Score | 703% |
| Threads | 10 |
| Allocations | 481 |

<details>
<summary>CPU Timeline (2 unique values: 66-76 cores)</summary>

```
1788363494 76
1788363499 76
1788363504 76
1788363509 76
1788363514 76
1788363519 76
1788363524 76
1788363529 76
1788363534 76
1788363539 76
1788363544 76
1788363549 76
1788363554 76
1788363559 66
1788363564 66
1788363569 66
1788363574 66
1788363579 66
1788363584 66
1788363589 66
```
</details>

---

