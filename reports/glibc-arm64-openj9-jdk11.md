---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-25 08:39:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 50 |
| CPU Cores (end) | 52 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 83 |
| Sample Rate | 1.38/sec |
| Health Score | 86% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 307 |
| Sample Rate | 5.12/sec |
| Health Score | 320% |
| Threads | 13 |
| Allocations | 169 |

<details>
<summary>CPU Timeline (2 unique values: 50-52 cores)</summary>

```
1787661382 50
1787661387 50
1787661392 50
1787661397 50
1787661402 50
1787661407 50
1787661412 50
1787661417 52
1787661422 52
1787661427 52
1787661432 52
1787661437 52
1787661442 52
1787661447 52
1787661452 52
1787661457 52
1787661462 52
1787661467 52
1787661472 52
1787661477 52
```
</details>

---

