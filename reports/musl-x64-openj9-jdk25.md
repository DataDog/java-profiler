---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-16 10:22:08 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 88 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 455 |
| Sample Rate | 7.58/sec |
| Health Score | 474% |
| Threads | 9 |
| Allocations | 401 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 580 |
| Sample Rate | 9.67/sec |
| Health Score | 604% |
| Threads | 11 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (5 unique values: 86-90 cores)</summary>

```
1794842261 88
1794842266 86
1794842271 86
1794842276 86
1794842281 86
1794842286 86
1794842291 88
1794842296 88
1794842301 88
1794842306 88
1794842311 88
1794842316 88
1794842321 88
1794842327 88
1794842332 90
1794842337 90
1794842342 90
1794842347 90
1794842352 90
1794842357 89
```
</details>

---

