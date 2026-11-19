---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-19 06:06:32 EST

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
| CPU Cores (start) | 31 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 618 |
| Sample Rate | 10.30/sec |
| Health Score | 644% |
| Threads | 8 |
| Allocations | 397 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 747 |
| Sample Rate | 12.45/sec |
| Health Score | 778% |
| Threads | 9 |
| Allocations | 541 |

<details>
<summary>CPU Timeline (3 unique values: 31-46 cores)</summary>

```
1795085930 31
1795085935 31
1795085940 31
1795085945 31
1795085950 31
1795085955 33
1795085960 33
1795085965 33
1795085970 33
1795085975 33
1795085980 33
1795085985 33
1795085990 33
1795085995 33
1795086000 33
1795086005 33
1795086010 33
1795086015 33
1795086020 33
1795086025 46
```
</details>

---

