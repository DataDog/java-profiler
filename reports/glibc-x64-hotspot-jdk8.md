---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-18 06:08:50 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 31 |
| CPU Cores (end) | 49 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 177 |
| Sample Rate | 2.95/sec |
| Health Score | 184% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 165 |
| Sample Rate | 2.75/sec |
| Health Score | 172% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 31-49 cores)</summary>

```
1794999756 31
1794999761 34
1794999766 34
1794999771 34
1794999776 34
1794999781 34
1794999786 34
1794999791 36
1794999796 36
1794999801 36
1794999806 36
1794999811 36
1794999816 36
1794999821 38
1794999826 38
1794999831 38
1794999836 47
1794999841 47
1794999846 49
1794999851 49
```
</details>

---

