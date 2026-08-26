---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-26 16:19:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 61 |
| CPU Cores (end) | 63 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 599 |
| Sample Rate | 9.98/sec |
| Health Score | 624% |
| Threads | 8 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 700 |
| Sample Rate | 11.67/sec |
| Health Score | 729% |
| Threads | 8 |
| Allocations | 500 |

<details>
<summary>CPU Timeline (2 unique values: 61-63 cores)</summary>

```
1787775264 61
1787775269 61
1787775274 61
1787775279 61
1787775284 61
1787775289 61
1787775294 61
1787775299 61
1787775304 63
1787775309 63
1787775314 63
1787775319 63
1787775324 63
1787775329 63
1787775334 63
1787775339 63
1787775344 63
1787775349 63
1787775354 63
1787775359 63
```
</details>

---

