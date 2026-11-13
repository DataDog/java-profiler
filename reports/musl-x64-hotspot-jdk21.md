---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-13 06:08:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 81 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 612 |
| Sample Rate | 10.20/sec |
| Health Score | 637% |
| Threads | 9 |
| Allocations | 377 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 907 |
| Sample Rate | 15.12/sec |
| Health Score | 945% |
| Threads | 11 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (5 unique values: 78-82 cores)</summary>

```
1794567778 81
1794567783 81
1794567788 81
1794567793 81
1794567798 81
1794567803 81
1794567808 81
1794567813 81
1794567818 81
1794567823 81
1794567829 81
1794567834 79
1794567839 79
1794567844 82
1794567849 82
1794567854 82
1794567859 80
1794567864 80
1794567869 80
1794567874 80
```
</details>

---

