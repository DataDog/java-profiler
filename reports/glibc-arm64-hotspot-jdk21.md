---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-07 12:41:45 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 7 |
| Allocations | 77 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 65 |
| Sample Rate | 1.08/sec |
| Health Score | 68% |
| Threads | 14 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1778171886 64
1778171891 64
1778171896 64
1778171901 64
1778171906 64
1778171911 64
1778171916 62
1778171921 62
1778171926 62
1778171931 62
1778171936 62
1778171941 62
1778171946 62
1778171951 62
1778171956 62
1778171961 62
1778171966 62
1778171971 62
1778171976 64
1778171981 64
```
</details>

---

