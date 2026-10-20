---
layout: default
title: glibc-arm64-hotspot-jdk11
---

## glibc-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-10-20 15:10:50 EDT

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
| CPU Cores (start) | 54 |
| CPU Cores (end) | 56 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 368 |
| Sample Rate | 6.13/sec |
| Health Score | 383% |
| Threads | 11 |
| Allocations | 182 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 27 |
| Sample Rate | 0.45/sec |
| Health Score | 28% |
| Threads | 8 |
| Allocations | 23 |

<details>
<summary>CPU Timeline (4 unique values: 41-56 cores)</summary>

```
1792523063 54
1792523068 49
1792523073 49
1792523078 49
1792523083 49
1792523088 41
1792523093 41
1792523098 41
1792523103 41
1792523108 41
1792523113 41
1792523118 41
1792523123 41
1792523128 56
1792523133 56
1792523138 56
1792523143 56
1792523148 56
1792523153 56
1792523158 56
```
</details>

---

