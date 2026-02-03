---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-02-03 07:53:26 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 73 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 638 |
| Sample Rate | 10.63/sec |
| Health Score | 664% |
| Threads | 10 |
| Allocations | 419 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 847 |
| Sample Rate | 14.12/sec |
| Health Score | 882% |
| Threads | 12 |
| Allocations | 463 |

<details>
<summary>CPU Timeline (5 unique values: 59-75 cores)</summary>

```
1770122802 73
1770122807 73
1770122812 73
1770122817 73
1770122822 73
1770122827 73
1770122832 73
1770122837 75
1770122842 75
1770122847 75
1770122852 75
1770122857 75
1770122862 75
1770122867 75
1770122872 75
1770122877 75
1770122882 75
1770122887 70
1770122892 70
1770122897 70
```
</details>

---

