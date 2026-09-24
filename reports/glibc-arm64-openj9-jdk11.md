---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-24 10:00:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 415 |
| Sample Rate | 6.92/sec |
| Health Score | 432% |
| Threads | 8 |
| Allocations | 343 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 63 |
| Sample Rate | 1.05/sec |
| Health Score | 66% |
| Threads | 12 |
| Allocations | 46 |

<details>
<summary>CPU Timeline (3 unique values: 39-48 cores)</summary>

```
1790258102 45
1790258107 48
1790258112 48
1790258117 48
1790258122 48
1790258127 48
1790258132 48
1790258137 48
1790258142 48
1790258147 48
1790258152 48
1790258157 39
1790258162 39
1790258167 39
1790258172 39
1790258177 39
1790258182 39
1790258187 39
1790258192 39
1790258197 39
```
</details>

---

