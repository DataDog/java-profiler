---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-11-10 06:59:40 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 33 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 180 |
| Sample Rate | 3.00/sec |
| Health Score | 188% |
| Threads | 11 |
| Allocations | 145 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 11 |
| Allocations | 43 |

<details>
<summary>CPU Timeline (4 unique values: 29-33 cores)</summary>

```
1794311782 29
1794311787 29
1794311792 29
1794311797 29
1794311802 29
1794311807 29
1794311812 29
1794311817 29
1794311822 29
1794311827 29
1794311832 29
1794311837 29
1794311842 29
1794311847 29
1794311852 29
1794311857 29
1794311862 29
1794311867 31
1794311872 31
1794311877 30
```
</details>

---

