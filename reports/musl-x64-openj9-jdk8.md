---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-10-30 13:49:00 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 28 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 184 |
| Sample Rate | 3.07/sec |
| Health Score | 192% |
| Threads | 6 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 166 |
| Sample Rate | 2.77/sec |
| Health Score | 173% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 28-32 cores)</summary>

```
1793382234 28
1793382239 28
1793382244 28
1793382249 28
1793382254 28
1793382259 28
1793382264 28
1793382269 28
1793382274 28
1793382279 28
1793382284 28
1793382289 28
1793382294 28
1793382299 28
1793382304 28
1793382309 32
1793382314 32
1793382319 32
1793382324 32
1793382329 32
```
</details>

---

