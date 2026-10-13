---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-13 07:44:39 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 58 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 8 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 757 |
| Sample Rate | 12.62/sec |
| Health Score | 789% |
| Threads | 10 |
| Allocations | 573 |

<details>
<summary>CPU Timeline (2 unique values: 56-58 cores)</summary>

```
1791891596 58
1791891601 58
1791891606 58
1791891611 58
1791891616 58
1791891621 58
1791891626 58
1791891631 58
1791891636 58
1791891641 58
1791891646 58
1791891651 58
1791891656 56
1791891661 56
1791891666 56
1791891671 56
1791891676 56
1791891681 56
1791891686 56
1791891691 56
```
</details>

---

