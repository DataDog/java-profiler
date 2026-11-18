---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-18 05:59:05 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 37 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 265 |
| Sample Rate | 4.42/sec |
| Health Score | 276% |
| Threads | 12 |
| Allocations | 139 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 12 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (4 unique values: 37-42 cores)</summary>

```
1794999178 37
1794999183 37
1794999188 37
1794999193 37
1794999198 37
1794999203 37
1794999208 37
1794999213 37
1794999218 42
1794999223 42
1794999228 42
1794999233 42
1794999238 41
1794999243 41
1794999248 41
1794999253 41
1794999258 41
1794999263 41
1794999268 40
1794999273 40
```
</details>

---

