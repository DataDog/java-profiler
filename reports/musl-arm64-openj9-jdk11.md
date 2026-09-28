---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-28 10:16:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 103 |
| Sample Rate | 1.72/sec |
| Health Score | 108% |
| Threads | 11 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1019 |
| Sample Rate | 16.98/sec |
| Health Score | 1061% |
| Threads | 9 |
| Allocations | 499 |

<details>
<summary>CPU Timeline (2 unique values: 33-45 cores)</summary>

```
1790604678 33
1790604683 33
1790604688 33
1790604693 33
1790604698 33
1790604703 33
1790604708 33
1790604713 33
1790604718 33
1790604723 33
1790604728 33
1790604733 33
1790604738 45
1790604743 45
1790604748 45
1790604753 45
1790604758 45
1790604763 45
1790604768 45
1790604773 45
```
</details>

---

