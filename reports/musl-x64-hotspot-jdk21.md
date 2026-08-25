---
layout: default
title: musl-x64-hotspot-jdk21
---

## musl-x64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-08-25 11:03:31 EDT

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
| CPU Cores (start) | 22 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 8 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 9 |
| Allocations | 497 |

<details>
<summary>CPU Timeline (2 unique values: 20-22 cores)</summary>

```
1787669834 22
1787669839 22
1787669844 22
1787669849 22
1787669854 22
1787669859 22
1787669864 22
1787669869 22
1787669874 22
1787669879 22
1787669884 22
1787669889 22
1787669894 22
1787669899 22
1787669904 20
1787669909 20
1787669914 20
1787669919 20
1787669924 20
1787669929 20
```
</details>

---

