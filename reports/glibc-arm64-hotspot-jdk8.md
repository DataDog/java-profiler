---
layout: default
title: glibc-arm64-hotspot-jdk8
---

## glibc-arm64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-04 09:37:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 55 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 8 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 13 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 55-64 cores)</summary>

```
1788528827 55
1788528832 55
1788528837 55
1788528842 55
1788528847 55
1788528852 59
1788528857 59
1788528862 59
1788528867 59
1788528872 59
1788528877 59
1788528882 59
1788528887 59
1788528892 59
1788528897 59
1788528902 59
1788528907 59
1788528912 59
1788528917 59
1788528923 59
```
</details>

---

