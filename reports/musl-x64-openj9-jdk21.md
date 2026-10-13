---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-13 07:44:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 61 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 393 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 688 |
| Sample Rate | 11.47/sec |
| Health Score | 717% |
| Threads | 9 |
| Allocations | 461 |

<details>
<summary>CPU Timeline (2 unique values: 59-61 cores)</summary>

```
1791891526 61
1791891531 61
1791891536 61
1791891541 61
1791891546 61
1791891551 61
1791891556 61
1791891561 61
1791891566 61
1791891571 59
1791891576 59
1791891581 59
1791891586 59
1791891591 61
1791891596 61
1791891601 61
1791891606 61
1791891611 61
1791891616 61
1791891621 61
```
</details>

---

