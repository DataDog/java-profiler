---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-18 10:58:03 EDT

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 9 |
| Allocations | 64 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 647 |
| Sample Rate | 10.78/sec |
| Health Score | 674% |
| Threads | 9 |
| Allocations | 511 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1787064753 64
1787064758 64
1787064763 64
1787064768 64
1787064773 64
1787064778 64
1787064783 64
1787064788 64
1787064793 64
1787064798 64
1787064803 64
1787064808 64
1787064813 64
1787064818 64
1787064823 64
1787064828 64
1787064833 62
1787064838 62
1787064843 62
1787064848 62
```
</details>

---

