---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-08-11 09:27:59 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 522 |
| Sample Rate | 8.70/sec |
| Health Score | 544% |
| Threads | 9 |
| Allocations | 368 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 149 |
| Sample Rate | 2.48/sec |
| Health Score | 155% |
| Threads | 12 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (3 unique values: 46-51 cores)</summary>

```
1786454491 46
1786454496 47
1786454501 47
1786454506 47
1786454511 47
1786454516 47
1786454521 47
1786454526 47
1786454531 47
1786454536 47
1786454541 47
1786454546 47
1786454551 47
1786454556 47
1786454561 51
1786454566 51
1786454571 51
1786454576 51
1786454581 51
1786454586 51
```
</details>

---

