---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-10-23 05:58:13 EDT

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
| CPU Cores (start) | 48 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 92 |
| Sample Rate | 1.53/sec |
| Health Score | 96% |
| Threads | 12 |
| Allocations | 54 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 303 |
| Sample Rate | 5.05/sec |
| Health Score | 316% |
| Threads | 16 |
| Allocations | 151 |

<details>
<summary>CPU Timeline (2 unique values: 36-48 cores)</summary>

```
1792749128 48
1792749133 48
1792749138 48
1792749143 48
1792749148 48
1792749153 48
1792749158 48
1792749163 48
1792749168 48
1792749173 36
1792749178 36
1792749183 36
1792749188 36
1792749193 36
1792749198 36
1792749203 36
1792749208 36
1792749213 36
1792749218 36
1792749223 36
```
</details>

---

