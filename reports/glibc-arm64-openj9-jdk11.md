---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-22 20:31:39 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 31 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 64 |
| Sample Rate | 1.07/sec |
| Health Score | 67% |
| Threads | 13 |
| Allocations | 48 |

<details>
<summary>CPU Timeline (3 unique values: 29-34 cores)</summary>

```
1795397203 29
1795397208 29
1795397213 29
1795397218 29
1795397223 29
1795397228 29
1795397233 29
1795397238 29
1795397243 34
1795397248 34
1795397253 34
1795397258 34
1795397263 34
1795397268 34
1795397273 31
1795397278 31
1795397283 31
1795397288 31
1795397293 31
1795397298 31
```
</details>

---

