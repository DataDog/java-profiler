---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-31 00:49:32 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 93 |
| Sample Rate | 1.55/sec |
| Health Score | 97% |
| Threads | 7 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 11 |
| Allocations | 35 |

<details>
<summary>CPU Timeline (2 unique values: 29-34 cores)</summary>

```
1788151512 29
1788151517 29
1788151522 29
1788151527 29
1788151532 29
1788151537 29
1788151542 29
1788151547 29
1788151552 29
1788151557 29
1788151562 29
1788151567 34
1788151572 34
1788151577 34
1788151582 34
1788151587 34
1788151592 34
1788151597 34
1788151602 34
1788151607 34
```
</details>

---

