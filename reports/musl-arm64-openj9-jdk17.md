---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-29 16:22:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 47 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 422 |
| Sample Rate | 7.03/sec |
| Health Score | 439% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 10 |
| Allocations | 32 |

<details>
<summary>CPU Timeline (3 unique values: 43-47 cores)</summary>

```
1790713068 45
1790713073 45
1790713078 45
1790713083 43
1790713088 43
1790713093 43
1790713098 43
1790713103 43
1790713108 43
1790713113 43
1790713118 43
1790713123 43
1790713128 43
1790713133 43
1790713138 43
1790713143 43
1790713148 43
1790713153 43
1790713158 43
1790713163 43
```
</details>

---

