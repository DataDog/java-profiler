---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-11 05:05:54 EST

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
| CPU Cores (start) | 49 |
| CPU Cores (end) | 51 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 170 |
| Sample Rate | 2.83/sec |
| Health Score | 177% |
| Threads | 9 |
| Allocations | 167 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 51 |
| Sample Rate | 0.85/sec |
| Health Score | 53% |
| Threads | 10 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (3 unique values: 49-51 cores)</summary>

```
1794391239 49
1794391244 49
1794391249 49
1794391254 49
1794391259 49
1794391264 49
1794391269 49
1794391274 49
1794391279 49
1794391284 49
1794391289 49
1794391294 50
1794391299 50
1794391304 50
1794391309 50
1794391314 50
1794391319 50
1794391324 50
1794391330 50
1794391335 51
```
</details>

---

