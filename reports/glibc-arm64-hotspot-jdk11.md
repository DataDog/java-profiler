---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-22 05:55:17 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 8 |
| Allocations | 81 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 11 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (2 unique values: 46-51 cores)</summary>

```
1792662649 46
1792662654 46
1792662659 51
1792662664 51
1792662669 51
1792662674 51
1792662679 51
1792662684 51
1792662689 51
1792662694 51
1792662699 51
1792662704 51
1792662709 51
1792662714 51
1792662719 51
1792662724 51
1792662729 51
1792662734 51
1792662739 46
1792662744 46
```
</details>

---

