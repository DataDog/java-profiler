---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-02-03 07:53:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 475 |
| Sample Rate | 7.92/sec |
| Health Score | 495% |
| Threads | 8 |
| Allocations | 359 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 645 |
| Sample Rate | 10.75/sec |
| Health Score | 672% |
| Threads | 12 |
| Allocations | 458 |

<details>
<summary>CPU Timeline (2 unique values: 59-64 cores)</summary>

```
1770122797 64
1770122802 64
1770122807 64
1770122812 64
1770122817 64
1770122822 64
1770122827 64
1770122832 64
1770122837 64
1770122842 64
1770122847 64
1770122852 64
1770122857 64
1770122862 64
1770122867 64
1770122872 64
1770122877 59
1770122882 59
1770122887 59
1770122892 59
```
</details>

---

