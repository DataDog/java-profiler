---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-01-29 11:12:24 EST

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
| CPU Cores (start) | 83 |
| CPU Cores (end) | 85 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 170 |
| Sample Rate | 5.67/sec |
| Health Score | 354% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 517 |
| Sample Rate | 17.23/sec |
| Health Score | 1077% |
| Threads | 12 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 83-85 cores)</summary>

```
1769702693 83
1769702698 83
1769702703 83
1769702708 83
1769702713 83
1769702718 83
1769702723 83
1769702728 83
1769702733 83
1769702738 85
1769702743 85
1769702748 85
1769702753 85
1769702758 85
1769702763 85
1769702768 85
1769702773 85
1769702778 85
1769702783 85
1769702788 85
```
</details>

---

