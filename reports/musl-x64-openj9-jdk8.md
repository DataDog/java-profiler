---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-21 09:02:26 EDT

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
| CPU Cores (start) | 20 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 277 |
| Sample Rate | 4.62/sec |
| Health Score | 289% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 424 |
| Sample Rate | 7.07/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (3 unique values: 20-32 cores)</summary>

```
1789995344 20
1789995349 20
1789995354 30
1789995359 30
1789995364 30
1789995369 30
1789995374 32
1789995379 32
1789995384 32
1789995389 32
1789995394 32
1789995399 32
1789995404 32
1789995409 32
1789995414 32
1789995419 32
1789995424 32
1789995429 32
1789995434 32
1789995439 32
```
</details>

---

