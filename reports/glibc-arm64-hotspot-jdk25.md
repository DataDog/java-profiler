---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-04 09:37:55 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 1.45/sec |
| Health Score | 91% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 102 |
| Sample Rate | 1.70/sec |
| Health Score | 106% |
| Threads | 13 |
| Allocations | 75 |

<details>
<summary>CPU Timeline (2 unique values: 20-40 cores)</summary>

```
1788528781 20
1788528786 20
1788528792 20
1788528797 20
1788528802 20
1788528807 20
1788528812 20
1788528817 20
1788528822 20
1788528827 20
1788528832 20
1788528837 20
1788528842 20
1788528847 20
1788528852 20
1788528857 20
1788528862 20
1788528867 20
1788528872 20
1788528877 20
```
</details>

---

