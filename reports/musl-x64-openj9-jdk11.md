---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-04-10 02:47:33 EDT

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
| CPU Cores (start) | 35 |
| CPU Cores (end) | 28 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 525 |
| Sample Rate | 8.75/sec |
| Health Score | 547% |
| Threads | 8 |
| Allocations | 376 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 834 |
| Sample Rate | 13.90/sec |
| Health Score | 869% |
| Threads | 10 |
| Allocations | 490 |

<details>
<summary>CPU Timeline (3 unique values: 28-35 cores)</summary>

```
1775803424 35
1775803429 35
1775803434 35
1775803439 35
1775803444 35
1775803449 35
1775803454 35
1775803459 35
1775803464 35
1775803469 35
1775803474 35
1775803479 31
1775803484 31
1775803489 31
1775803494 31
1775803499 31
1775803504 31
1775803509 31
1775803514 31
1775803519 31
```
</details>

---

