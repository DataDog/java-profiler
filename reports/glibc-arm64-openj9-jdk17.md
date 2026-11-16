---
layout: default
title: glibc-arm64-openj9-jdk17
---

## glibc-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-16 10:22:05 EST

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
| CPU Cores (start) | 40 |
| CPU Cores (end) | 36 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 62 |
| Sample Rate | 1.03/sec |
| Health Score | 64% |
| Threads | 9 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 13 |
| Allocations | 52 |

<details>
<summary>CPU Timeline (3 unique values: 36-40 cores)</summary>

```
1794842221 40
1794842226 40
1794842231 40
1794842236 40
1794842241 40
1794842246 40
1794842251 40
1794842256 40
1794842261 40
1794842266 40
1794842271 40
1794842276 38
1794842281 38
1794842286 38
1794842291 38
1794842296 38
1794842301 38
1794842306 38
1794842311 38
1794842316 38
```
</details>

---

