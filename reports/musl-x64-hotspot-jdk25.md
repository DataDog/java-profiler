---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-16 04:44:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 7 |
| CPU Cores (end) | 9 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 8 |
| Allocations | 407 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 552 |
| Sample Rate | 9.20/sec |
| Health Score | 575% |
| Threads | 9 |
| Allocations | 467 |

<details>
<summary>CPU Timeline (2 unique values: 7-9 cores)</summary>

```
1792139933 7
1792139938 7
1792139943 7
1792139948 7
1792139953 7
1792139958 7
1792139963 7
1792139968 7
1792139973 7
1792139978 7
1792139983 7
1792139988 7
1792139993 7
1792139998 9
1792140003 9
1792140008 9
1792140013 9
1792140018 9
1792140023 9
1792140028 9
```
</details>

---

