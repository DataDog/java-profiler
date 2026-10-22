---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-10-22 01:13:27 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 64 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 10 |
| Allocations | 76 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 80 |
| Sample Rate | 1.33/sec |
| Health Score | 83% |
| Threads | 15 |
| Allocations | 60 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1792645522 64
1792645527 64
1792645532 64
1792645537 64
1792645542 64
1792645547 64
1792645552 64
1792645557 64
1792645562 64
1792645567 64
1792645572 64
1792645577 64
1792645582 64
1792645587 64
1792645592 64
1792645597 64
1792645602 64
1792645607 64
1792645612 64
1792645617 64
```
</details>

---

