---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-05-11 10:05:28 EDT

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
| CPU Cores (start) | 52 |
| CPU Cores (end) | 70 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 659 |
| Sample Rate | 10.98/sec |
| Health Score | 686% |
| Threads | 9 |
| Allocations | 410 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1034 |
| Sample Rate | 17.23/sec |
| Health Score | 1077% |
| Threads | 10 |
| Allocations | 548 |

<details>
<summary>CPU Timeline (6 unique values: 52-72 cores)</summary>

```
1778508073 52
1778508078 52
1778508083 52
1778508089 52
1778508094 71
1778508099 71
1778508104 72
1778508109 72
1778508114 72
1778508119 72
1778508124 72
1778508129 72
1778508134 72
1778508139 69
1778508144 69
1778508149 69
1778508154 67
1778508159 67
1778508164 69
1778508169 69
```
</details>

---

