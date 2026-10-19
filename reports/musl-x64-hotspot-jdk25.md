---
layout: default
title: musl-x64-hotspot-jdk25
---

## musl-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-10-19 15:32:48 EDT

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
| CPU Cores (start) | 81 |
| CPU Cores (end) | 79 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 560 |
| Sample Rate | 9.33/sec |
| Health Score | 583% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 555 |
| Sample Rate | 9.25/sec |
| Health Score | 578% |
| Threads | 10 |
| Allocations | 535 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1792437986 81
1792437991 81
1792437996 81
1792438001 81
1792438006 81
1792438011 81
1792438016 81
1792438022 81
1792438027 81
1792438032 81
1792438037 81
1792438042 81
1792438047 79
1792438052 79
1792438057 79
1792438062 79
1792438067 79
1792438072 79
1792438077 79
1792438082 79
```
</details>

---

