---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 10:52:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 696 |
| Sample Rate | 11.60/sec |
| Health Score | 725% |
| Threads | 8 |
| Allocations | 335 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 12 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1790174743 50
1790174748 50
1790174753 50
1790174758 50
1790174763 50
1790174768 50
1790174773 50
1790174778 50
1790174783 50
1790174788 50
1790174793 50
1790174798 50
1790174803 50
1790174808 50
1790174813 50
1790174818 50
1790174823 50
1790174828 50
1790174833 50
1790174838 50
```
</details>

---

