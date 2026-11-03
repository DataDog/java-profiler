---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-03 11:00:44 EST

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 26 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 436 |
| Sample Rate | 7.27/sec |
| Health Score | 454% |
| Threads | 8 |
| Allocations | 424 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 531 |
| Sample Rate | 8.85/sec |
| Health Score | 553% |
| Threads | 9 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (2 unique values: 26-30 cores)</summary>

```
1793721188 30
1793721193 30
1793721198 30
1793721203 30
1793721208 30
1793721213 30
1793721218 30
1793721223 30
1793721228 26
1793721233 26
1793721238 26
1793721243 26
1793721248 26
1793721253 26
1793721258 26
1793721263 26
1793721268 26
1793721273 26
1793721278 26
1793721283 26
```
</details>

---

