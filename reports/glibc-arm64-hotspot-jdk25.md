---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-13 10:54:07 EST

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 267 |
| Sample Rate | 4.45/sec |
| Health Score | 278% |
| Threads | 12 |
| Allocations | 128 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 85 |
| Sample Rate | 1.42/sec |
| Health Score | 89% |
| Threads | 15 |
| Allocations | 66 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1794585028 48
1794585033 48
1794585038 48
1794585043 48
1794585048 48
1794585053 48
1794585058 48
1794585063 48
1794585068 48
1794585073 48
1794585078 48
1794585083 48
1794585088 36
1794585093 36
1794585098 36
1794585103 36
1794585108 36
1794585113 36
1794585118 36
1794585123 36
```
</details>

---

