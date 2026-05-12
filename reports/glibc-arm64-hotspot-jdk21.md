---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-05-12 05:49:50 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 11 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 122 |
| Sample Rate | 2.03/sec |
| Health Score | 127% |
| Threads | 11 |
| Allocations | 77 |

<details>
<summary>CPU Timeline (3 unique values: 44-56 cores)</summary>

```
1778579057 48
1778579062 56
1778579067 56
1778579072 56
1778579077 56
1778579082 56
1778579087 56
1778579092 56
1778579097 56
1778579102 56
1778579107 56
1778579112 56
1778579117 56
1778579122 56
1778579127 56
1778579132 56
1778579137 56
1778579142 44
1778579147 44
1778579152 44
```
</details>

---

