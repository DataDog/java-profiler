---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-02-03 07:53:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 51 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 315 |
| Sample Rate | 5.25/sec |
| Health Score | 328% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 194 |
| Sample Rate | 3.23/sec |
| Health Score | 202% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 43-53 cores)</summary>

```
1770122787 51
1770122792 51
1770122797 51
1770122802 51
1770122807 51
1770122812 51
1770122817 51
1770122822 51
1770122827 51
1770122832 51
1770122837 51
1770122842 51
1770122847 51
1770122852 51
1770122857 51
1770122862 51
1770122867 51
1770122872 51
1770122877 53
1770122882 53
```
</details>

---

