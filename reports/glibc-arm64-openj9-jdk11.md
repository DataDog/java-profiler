---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-17 14:55:31 EST

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
| CPU Cores (start) | 34 |
| CPU Cores (end) | 39 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 404 |
| Sample Rate | 6.73/sec |
| Health Score | 421% |
| Threads | 12 |
| Allocations | 191 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 117 |
| Sample Rate | 1.95/sec |
| Health Score | 122% |
| Threads | 12 |
| Allocations | 68 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1794945128 34
1794945133 34
1794945138 34
1794945143 34
1794945148 34
1794945153 34
1794945158 34
1794945163 34
1794945168 34
1794945173 34
1794945178 34
1794945183 39
1794945188 39
1794945193 39
1794945198 39
1794945203 39
1794945208 39
1794945213 39
1794945218 39
1794945223 39
```
</details>

---

