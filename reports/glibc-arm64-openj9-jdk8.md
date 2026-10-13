---
layout: default
title: glibc-arm64-openj9-jdk8
---

## glibc-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-13 07:44:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 10 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 58 |
| Sample Rate | 0.97/sec |
| Health Score | 61% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 40-48 cores)</summary>

```
1791891521 48
1791891526 48
1791891531 48
1791891536 48
1791891541 48
1791891546 48
1791891551 48
1791891556 43
1791891561 43
1791891566 43
1791891571 43
1791891576 43
1791891581 43
1791891586 43
1791891591 43
1791891596 43
1791891601 43
1791891606 43
1791891611 43
1791891616 43
```
</details>

---

