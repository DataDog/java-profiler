---
layout: default
title: musl-x64-openj9-jdk21
---

## musl-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-04-27 05:15:09 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 508 |
| Sample Rate | 8.47/sec |
| Health Score | 529% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 666 |
| Sample Rate | 11.10/sec |
| Health Score | 694% |
| Threads | 9 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (3 unique values: 21-24 cores)</summary>

```
1777280981 22
1777280986 22
1777280991 24
1777280996 24
1777281001 24
1777281006 24
1777281011 24
1777281016 24
1777281021 21
1777281026 21
1777281031 24
1777281036 24
1777281041 24
1777281046 24
1777281051 24
1777281056 24
1777281061 24
1777281066 24
1777281071 24
1777281076 24
```
</details>

---

