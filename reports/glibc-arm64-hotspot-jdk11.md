---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-08-13 04:00:00 EDT

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 8 |
| Allocations | 59 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 84 |
| Sample Rate | 1.40/sec |
| Health Score | 87% |
| Threads | 12 |
| Allocations | 28 |

<details>
<summary>CPU Timeline (2 unique values: 31-34 cores)</summary>

```
1786607784 31
1786607789 31
1786607794 31
1786607799 31
1786607804 31
1786607809 31
1786607814 31
1786607819 31
1786607824 31
1786607829 31
1786607834 31
1786607839 31
1786607844 31
1786607849 31
1786607854 31
1786607859 31
1786607864 31
1786607869 31
1786607874 31
1786607879 31
```
</details>

---

