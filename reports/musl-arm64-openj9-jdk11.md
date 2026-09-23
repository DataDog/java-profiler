---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-23 09:06:34 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 48 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 95 |
| Sample Rate | 1.58/sec |
| Health Score | 99% |
| Threads | 10 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 112 |
| Sample Rate | 1.87/sec |
| Health Score | 117% |
| Threads | 9 |
| Allocations | 57 |

<details>
<summary>CPU Timeline (3 unique values: 38-48 cores)</summary>

```
1790168552 48
1790168557 48
1790168562 48
1790168567 48
1790168572 48
1790168577 48
1790168582 48
1790168587 48
1790168592 48
1790168597 48
1790168602 48
1790168607 48
1790168612 48
1790168617 43
1790168622 43
1790168627 43
1790168632 43
1790168637 43
1790168642 38
1790168647 38
```
</details>

---

