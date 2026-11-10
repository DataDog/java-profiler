---
layout: default
title: glibc-x64-openj9-jdk8
---

## glibc-x64-openj9-jdk8 - ✅ PASS

**Date:** 2026-11-10 14:54:02 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 62 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 343 |
| Sample Rate | 5.72/sec |
| Health Score | 358% |
| Threads | 7 |
| Allocations | 0 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 167 |
| Sample Rate | 2.78/sec |
| Health Score | 174% |
| Threads | 7 |
| Allocations | 0 |

<details>
<summary>CPU Timeline (2 unique values: 62-64 cores)</summary>

```
1794340092 64
1794340097 64
1794340102 64
1794340107 64
1794340112 64
1794340117 64
1794340122 64
1794340127 64
1794340132 64
1794340137 64
1794340142 64
1794340147 64
1794340152 64
1794340157 64
1794340162 62
1794340167 62
1794340172 62
1794340177 62
1794340182 62
1794340187 62
```
</details>

---

