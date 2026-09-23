---
layout: default
title: musl-arm64-openj9-jdk8
---

## musl-arm64-openj9-jdk8 - ✅ PASS

**Date:** 2026-09-23 09:06:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 36 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 76 |
| Sample Rate | 1.27/sec |
| Health Score | 79% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 74 |
| Sample Rate | 1.23/sec |
| Health Score | 77% |
| Threads | 11 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (6 unique values: 34-48 cores)</summary>

```
1790168527 36
1790168532 36
1790168537 36
1790168542 36
1790168547 34
1790168552 34
1790168557 34
1790168562 34
1790168567 34
1790168572 34
1790168577 46
1790168582 46
1790168587 46
1790168592 46
1790168597 41
1790168602 41
1790168607 41
1790168612 41
1790168617 41
1790168622 41
```
</details>

---

