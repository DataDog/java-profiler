---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-16 04:44:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 75 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 490 |
| Sample Rate | 8.17/sec |
| Health Score | 511% |
| Threads | 9 |
| Allocations | 384 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 754 |
| Sample Rate | 12.57/sec |
| Health Score | 786% |
| Threads | 11 |
| Allocations | 506 |

<details>
<summary>CPU Timeline (3 unique values: 52-75 cores)</summary>

```
1792139933 52
1792139938 52
1792139943 52
1792139948 52
1792139953 52
1792139958 52
1792139963 52
1792139968 54
1792139973 54
1792139978 54
1792139983 54
1792139988 54
1792139993 54
1792139998 54
1792140003 54
1792140008 54
1792140013 54
1792140018 54
1792140023 54
1792140028 54
```
</details>

---

