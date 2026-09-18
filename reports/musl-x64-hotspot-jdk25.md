---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-18 11:01:55 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 69 |
| CPU Cores (end) | 71 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 524 |
| Sample Rate | 8.73/sec |
| Health Score | 546% |
| Threads | 9 |
| Allocations | 409 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 629 |
| Sample Rate | 10.48/sec |
| Health Score | 655% |
| Threads | 11 |
| Allocations | 529 |

<details>
<summary>CPU Timeline (4 unique values: 65-71 cores)</summary>

```
1789743319 69
1789743324 69
1789743329 67
1789743334 67
1789743339 67
1789743344 67
1789743349 65
1789743354 65
1789743359 65
1789743364 65
1789743369 65
1789743374 65
1789743379 65
1789743384 67
1789743390 67
1789743395 71
1789743400 71
1789743405 71
1789743410 71
1789743415 71
```
</details>

---

