---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-08-12 04:18:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 64 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 135 |
| Sample Rate | 2.25/sec |
| Health Score | 141% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 175 |
| Sample Rate | 2.92/sec |
| Health Score | 182% |
| Threads | 8 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 64-96 cores)</summary>

```
1786522393 64
1786522398 64
1786522403 64
1786522408 64
1786522413 64
1786522418 64
1786522423 96
1786522428 96
1786522433 96
1786522438 96
1786522443 96
1786522448 96
1786522453 96
1786522458 96
1786522463 96
1786522468 96
1786522473 96
1786522478 96
1786522483 96
1786522488 96
```
</details>

---

