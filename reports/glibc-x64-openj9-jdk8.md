---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ❌ FAIL

**Date:** 2026-11-28 00:04:23 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk8 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 96 |
| CPU Cores (end) | 96 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 31 |
| Sample Rate | 0.52/sec |
| Health Score | 32% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 1 |
| Sample Rate | 0.02/sec |
| Health Score | 1% |
| Threads | 1 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (1 unique values: 96-96 cores)</summary>

```
1795842031 96
1795842036 96
1795842041 96
1795842046 96
1795842051 96
1795842056 96
1795842061 96
1795842066 96
1795842071 96
1795842076 96
1795842081 96
1795842086 96
1795842091 96
1795842096 96
1795842101 96
1795842106 96
1795842111 96
1795842116 96
1795842121 96
1795842126 96
```
</details>

---

