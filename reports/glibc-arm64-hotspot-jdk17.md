---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-18 03:37:49 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
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
| CPU Samples | 219 |
| Sample Rate | 3.65/sec |
| Health Score | 228% |
| Threads | 9 |
| Allocations | 170 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 7 |
| Sample Rate | 0.12/sec |
| Health Score | 8% |
| Threads | 6 |
| Allocations | 11 |

<details>
<summary>CPU Timeline (2 unique values: 43-48 cores)</summary>

```
1789716693 43
1789716698 43
1789716703 43
1789716708 43
1789716713 43
1789716718 43
1789716723 43
1789716728 43
1789716733 43
1789716738 43
1789716743 43
1789716748 43
1789716753 43
1789716758 43
1789716763 43
1789716768 43
1789716773 43
1789716778 43
1789716783 43
1789716788 48
```
</details>

---

