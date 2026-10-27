---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-27 11:47:25 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 14 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 62 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 231 |
| Sample Rate | 3.85/sec |
| Health Score | 241% |
| Threads | 12 |
| Allocations | 151 |

<details>
<summary>CPU Timeline (2 unique values: 9-14 cores)</summary>

```
1793115765 14
1793115770 14
1793115775 14
1793115780 14
1793115785 14
1793115790 14
1793115795 14
1793115800 14
1793115805 14
1793115810 14
1793115815 14
1793115820 14
1793115825 14
1793115830 14
1793115835 14
1793115840 14
1793115845 14
1793115850 9
1793115855 9
1793115860 9
```
</details>

---

