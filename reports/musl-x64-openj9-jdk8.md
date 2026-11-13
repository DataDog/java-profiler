---
layout: default
title: musl-x64-openj9-jdk8
---

## musl-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-13 09:34:16 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 82 |
| CPU Cores (end) | 83 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 346 |
| Sample Rate | 5.77/sec |
| Health Score | 361% |
| Threads | 9 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 425 |
| Sample Rate | 7.08/sec |
| Health Score | 442% |
| Threads | 9 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (4 unique values: 82-86 cores)</summary>

```
1794580051 82
1794580056 82
1794580061 82
1794580066 82
1794580071 82
1794580076 82
1794580081 82
1794580086 82
1794580091 84
1794580096 84
1794580101 84
1794580106 84
1794580111 86
1794580116 86
1794580121 86
1794580126 83
1794580131 83
1794580136 83
1794580141 83
1794580146 83
```
</details>

---

