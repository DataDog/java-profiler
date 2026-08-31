---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-30 21:25:13 EDT

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
| Threads | 6 |
| Allocations | 52 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 10 |
| Allocations | 41 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1788139172 64
1788139177 64
1788139182 64
1788139187 64
1788139192 64
1788139197 64
1788139202 64
1788139207 64
1788139212 64
1788139217 64
1788139222 64
1788139227 64
1788139232 64
1788139237 64
1788139242 64
1788139247 64
1788139252 64
1788139257 64
1788139262 64
1788139267 64
```
</details>

---

