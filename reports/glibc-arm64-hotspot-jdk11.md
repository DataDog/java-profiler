---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-23 11:06:25 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 45 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 9 |
| Allocations | 55 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 10 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (2 unique values: 40-45 cores)</summary>

```
1795449782 40
1795449787 40
1795449792 40
1795449797 40
1795449802 40
1795449807 40
1795449812 40
1795449817 40
1795449822 40
1795449827 40
1795449832 40
1795449837 40
1795449842 40
1795449847 40
1795449852 45
1795449857 45
1795449862 45
1795449867 45
1795449872 45
1795449877 45
```
</details>

---

