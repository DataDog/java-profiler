---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 07:55:58 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 99 |
| Sample Rate | 1.65/sec |
| Health Score | 103% |
| Threads | 12 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 26 |
| Sample Rate | 0.43/sec |
| Health Score | 27% |
| Threads | 9 |
| Allocations | 13 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1794574188 64
1794574193 64
1794574198 64
1794574203 64
1794574208 64
1794574213 64
1794574218 64
1794574223 64
1794574228 64
1794574233 64
1794574238 64
1794574243 64
1794574248 64
1794574253 64
1794574258 64
1794574263 64
1794574268 64
1794574273 64
1794574278 64
1794574283 64
```
</details>

---

