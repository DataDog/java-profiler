---
layout: default
title: musl-x64-openj9-jdk25
---

## musl-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-12 06:55:48 EST

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
| CPU Cores (start) | 96 |
| CPU Cores (end) | 87 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 432 |
| Sample Rate | 7.20/sec |
| Health Score | 450% |
| Threads | 9 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 545 |
| Sample Rate | 9.08/sec |
| Health Score | 568% |
| Threads | 10 |
| Allocations | 512 |

<details>
<summary>CPU Timeline (3 unique values: 87-96 cores)</summary>

```
1794484067 96
1794484072 96
1794484077 96
1794484082 96
1794484087 96
1794484092 96
1794484097 96
1794484102 96
1794484107 94
1794484112 94
1794484117 94
1794484122 94
1794484127 94
1794484132 94
1794484137 94
1794484142 94
1794484147 87
1794484152 87
1794484157 87
1794484162 87
```
</details>

---

