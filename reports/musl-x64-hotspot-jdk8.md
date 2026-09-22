---
layout: default
title: musl-x64-hotspot-jdk8
---

## musl-x64-hotspot-jdk8 - ✅ PASS

**Date:** 2026-09-22 13:14:52 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 71 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 155 |
| Sample Rate | 2.58/sec |
| Health Score | 161% |
| Threads | 5 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 450 |
| Sample Rate | 7.50/sec |
| Health Score | 469% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 71-96 cores)</summary>

```
1790096982 71
1790096987 71
1790096992 71
1790096997 71
1790097002 71
1790097007 71
1790097012 71
1790097017 71
1790097022 71
1790097027 71
1790097032 71
1790097037 71
1790097042 71
1790097047 71
1790097052 71
1790097057 71
1790097062 71
1790097067 71
1790097072 96
1790097077 96
```
</details>

---

