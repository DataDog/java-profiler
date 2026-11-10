---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-11-10 06:59:39 EST

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 42 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 627 |
| Sample Rate | 10.45/sec |
| Health Score | 653% |
| Threads | 8 |
| Allocations | 340 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 11 |
| Allocations | 65 |

<details>
<summary>CPU Timeline (3 unique values: 39-43 cores)</summary>

```
1794311762 39
1794311767 39
1794311772 39
1794311777 39
1794311782 39
1794311787 39
1794311792 43
1794311797 43
1794311802 43
1794311807 43
1794311812 43
1794311817 43
1794311822 43
1794311827 43
1794311832 43
1794311837 43
1794311842 43
1794311847 43
1794311852 43
1794311857 43
```
</details>

---

