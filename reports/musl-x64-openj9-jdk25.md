---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-10 11:01:19 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 405 |
| Sample Rate | 6.75/sec |
| Health Score | 422% |
| Threads | 8 |
| Allocations | 408 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 528 |
| Sample Rate | 8.80/sec |
| Health Score | 550% |
| Threads | 9 |
| Allocations | 523 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1794326096 32
1794326101 32
1794326106 32
1794326111 32
1794326116 32
1794326121 32
1794326126 32
1794326131 32
1794326136 32
1794326141 32
1794326146 32
1794326151 32
1794326156 32
1794326161 32
1794326166 32
1794326171 32
1794326176 32
1794326181 32
1794326186 32
1794326191 32
```
</details>

---

