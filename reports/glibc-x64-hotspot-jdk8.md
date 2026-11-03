---
layout: default
title: glibc-x64-hotspot-jdk8
---

## glibc-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-11-03 11:25:56 EST

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 167 |
| Sample Rate | 2.78/sec |
| Health Score | 174% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 183 |
| Sample Rate | 3.05/sec |
| Health Score | 191% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 81-85 cores)</summary>

```
1793722767 81
1793722772 81
1793722777 83
1793722782 83
1793722787 83
1793722792 83
1793722797 85
1793722802 85
1793722807 85
1793722812 85
1793722817 85
1793722822 85
1793722827 85
1793722832 85
1793722837 85
1793722842 85
1793722847 85
1793722852 85
1793722857 85
1793722862 85
```
</details>

---

