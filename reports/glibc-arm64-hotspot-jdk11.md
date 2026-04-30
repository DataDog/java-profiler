---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-04-30 19:50:54 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 7 |
| Allocations | 70 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 891 |
| Sample Rate | 14.85/sec |
| Health Score | 928% |
| Threads | 9 |
| Allocations | 474 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1777592836 64
1777592841 64
1777592846 64
1777592851 64
1777592856 64
1777592861 64
1777592866 64
1777592871 64
1777592876 64
1777592881 64
1777592886 64
1777592891 64
1777592896 64
1777592901 64
1777592906 64
1777592911 64
1777592916 64
1777592921 64
1777592926 64
1777592931 64
```
</details>

---

