---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-13 07:44:37 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 35 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 69 |
| Sample Rate | 1.15/sec |
| Health Score | 72% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 72 |
| Sample Rate | 1.20/sec |
| Health Score | 75% |
| Threads | 12 |
| Allocations | 30 |

<details>
<summary>CPU Timeline (5 unique values: 35-39 cores)</summary>

```
1791891571 39
1791891576 38
1791891581 38
1791891586 38
1791891591 38
1791891596 38
1791891601 38
1791891606 38
1791891611 38
1791891616 38
1791891621 38
1791891626 37
1791891631 37
1791891636 37
1791891641 37
1791891646 36
1791891651 36
1791891656 35
1791891661 35
1791891666 35
```
</details>

---

