---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-19 08:02:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 50 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 243 |
| Sample Rate | 4.05/sec |
| Health Score | 253% |
| Threads | 11 |
| Allocations | 159 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 297 |
| Sample Rate | 4.95/sec |
| Health Score | 309% |
| Threads | 14 |
| Allocations | 147 |

<details>
<summary>CPU Timeline (1 unique values: 50-50 cores)</summary>

```
1795093137 50
1795093142 50
1795093147 50
1795093152 50
1795093157 50
1795093162 50
1795093167 50
1795093172 50
1795093177 50
1795093182 50
1795093187 50
1795093192 50
1795093197 50
1795093202 50
1795093208 50
1795093213 50
1795093218 50
1795093223 50
1795093228 50
1795093233 50
```
</details>

---

