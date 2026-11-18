---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-18 05:43:45 EST

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
| CPU Cores (start) | 16 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 154 |
| Sample Rate | 2.57/sec |
| Health Score | 161% |
| Threads | 9 |
| Allocations | 86 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 790 |
| Sample Rate | 13.17/sec |
| Health Score | 823% |
| Threads | 11 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 16-21 cores)</summary>

```
1794998145 16
1794998150 16
1794998155 16
1794998160 16
1794998165 16
1794998170 16
1794998175 21
1794998180 21
1794998185 21
1794998191 21
1794998196 21
1794998201 21
1794998206 21
1794998211 21
1794998216 21
1794998221 21
1794998226 21
1794998231 21
1794998236 21
1794998241 21
```
</details>

---

