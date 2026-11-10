---
layout: default
title: glibc-x64-hotspot-jdk25
---

## glibc-x64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-11-10 11:01:15 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 80 |
| CPU Cores (end) | 73 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 438 |
| Sample Rate | 7.30/sec |
| Health Score | 456% |
| Threads | 9 |
| Allocations | 392 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 526 |
| Sample Rate | 8.77/sec |
| Health Score | 548% |
| Threads | 10 |
| Allocations | 472 |

<details>
<summary>CPU Timeline (4 unique values: 73-87 cores)</summary>

```
1794326131 80
1794326136 80
1794326141 80
1794326146 87
1794326151 87
1794326156 87
1794326161 87
1794326166 87
1794326171 87
1794326176 87
1794326181 87
1794326186 87
1794326191 87
1794326196 87
1794326201 87
1794326206 87
1794326211 87
1794326216 87
1794326221 79
1794326226 79
```
</details>

---

