---
layout: default
title: glibc-x64-hotspot-jdk11
---

## glibc-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-13 07:44:37 EDT

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 567 |
| Sample Rate | 9.45/sec |
| Health Score | 591% |
| Threads | 8 |
| Allocations | 353 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 863 |
| Sample Rate | 14.38/sec |
| Health Score | 899% |
| Threads | 9 |
| Allocations | 473 |

<details>
<summary>CPU Timeline (2 unique values: 45-96 cores)</summary>

```
1791891566 96
1791891571 96
1791891576 96
1791891581 96
1791891586 96
1791891591 45
1791891596 45
1791891601 45
1791891606 45
1791891611 45
1791891616 45
1791891621 45
1791891626 45
1791891631 45
1791891636 45
1791891641 45
1791891646 45
1791891651 45
1791891656 45
1791891661 45
```
</details>

---

