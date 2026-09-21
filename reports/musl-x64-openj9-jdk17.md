---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-21 09:02:26 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 27 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 487 |
| Sample Rate | 8.12/sec |
| Health Score | 507% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 637 |
| Sample Rate | 10.62/sec |
| Health Score | 664% |
| Threads | 10 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (3 unique values: 27-62 cores)</summary>

```
1789995339 27
1789995344 27
1789995349 27
1789995354 27
1789995359 27
1789995364 27
1789995369 27
1789995374 27
1789995379 27
1789995384 29
1789995389 29
1789995394 62
1789995399 62
1789995404 62
1789995409 62
1789995414 62
1789995419 62
1789995424 62
1789995430 62
1789995435 62
```
</details>

---

