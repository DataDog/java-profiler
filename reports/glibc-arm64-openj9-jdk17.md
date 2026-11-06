---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-05 19:52:37 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 81 |
| Sample Rate | 1.35/sec |
| Health Score | 84% |
| Threads | 12 |
| Allocations | 56 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 11 |
| Sample Rate | 0.18/sec |
| Health Score | 11% |
| Threads | 5 |
| Allocations | 14 |

<details>
<summary>CPU Timeline (3 unique values: 39-48 cores)</summary>

```
1793926122 39
1793926127 39
1793926132 39
1793926137 39
1793926142 39
1793926147 39
1793926152 39
1793926157 39
1793926162 39
1793926167 44
1793926172 44
1793926177 48
1793926182 48
1793926187 48
1793926192 48
1793926197 48
1793926202 48
1793926207 48
1793926212 48
1793926217 48
```
</details>

---

