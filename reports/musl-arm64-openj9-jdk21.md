---
layout: default
title: musl-arm64-openj9-jdk21
---

## musl-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-09-04 01:03:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
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
| CPU Samples | 75 |
| Sample Rate | 1.25/sec |
| Health Score | 78% |
| Threads | 9 |
| Allocations | 75 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 63 |

<details>
<summary>CPU Timeline (1 unique values: 64-64 cores)</summary>

```
1788497968 64
1788497973 64
1788497978 64
1788497983 64
1788497989 64
1788497994 64
1788497999 64
1788498004 64
1788498009 64
1788498014 64
1788498019 64
1788498024 64
1788498029 64
1788498034 64
1788498039 64
1788498044 64
1788498049 64
1788498054 64
1788498059 64
1788498064 64
```
</details>

---

