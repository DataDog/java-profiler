---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-18 08:24:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 43 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 144 |
| Sample Rate | 2.40/sec |
| Health Score | 150% |
| Threads | 8 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 170 |
| Sample Rate | 2.83/sec |
| Health Score | 177% |
| Threads | 11 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1787055576 43
1787055581 43
1787055586 43
1787055591 43
1787055596 43
1787055601 43
1787055606 43
1787055611 43
1787055616 43
1787055621 43
1787055626 43
1787055631 43
1787055636 43
1787055641 43
1787055646 43
1787055651 43
1787055656 43
1787055661 48
1787055666 48
1787055671 48
```
</details>

---

