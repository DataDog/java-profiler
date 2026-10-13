---
layout: default
title: musl-x64-hotspot-jdk11
---

## musl-x64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-13 08:38:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 550 |
| Sample Rate | 9.17/sec |
| Health Score | 573% |
| Threads | 8 |
| Allocations | 366 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 685 |
| Sample Rate | 11.42/sec |
| Health Score | 714% |
| Threads | 9 |
| Allocations | 553 |

<details>
<summary>CPU Timeline (3 unique values: 28-32 cores)</summary>

```
1791894791 30
1791894796 30
1791894801 30
1791894806 30
1791894811 30
1791894816 30
1791894821 30
1791894826 30
1791894831 30
1791894836 28
1791894841 28
1791894846 28
1791894851 28
1791894856 28
1791894861 28
1791894866 28
1791894871 28
1791894876 30
1791894881 30
1791894886 30
```
</details>

---

