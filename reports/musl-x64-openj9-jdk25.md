---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-24 11:42:52 EST

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
| CPU Cores (start) | 82 |
| CPU Cores (end) | 72 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 493 |
| Sample Rate | 8.22/sec |
| Health Score | 514% |
| Threads | 9 |
| Allocations | 413 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 592 |
| Sample Rate | 9.87/sec |
| Health Score | 617% |
| Threads | 11 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (5 unique values: 72-87 cores)</summary>

```
1795538254 82
1795538259 82
1795538264 82
1795538269 82
1795538274 82
1795538279 82
1795538284 87
1795538289 87
1795538294 87
1795538299 87
1795538304 87
1795538309 87
1795538314 87
1795538319 87
1795538324 87
1795538329 87
1795538334 87
1795538339 87
1795538344 84
1795538349 84
```
</details>

---

