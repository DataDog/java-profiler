---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-12 06:55:47 EST

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
| CPU Cores (start) | 64 |
| CPU Cores (end) | 78 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 579 |
| Sample Rate | 9.65/sec |
| Health Score | 603% |
| Threads | 8 |
| Allocations | 386 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 722 |
| Sample Rate | 12.03/sec |
| Health Score | 752% |
| Threads | 9 |
| Allocations | 509 |

<details>
<summary>CPU Timeline (4 unique values: 57-78 cores)</summary>

```
1794484080 64
1794484085 64
1794484090 64
1794484095 64
1794484100 64
1794484105 64
1794484110 64
1794484115 64
1794484120 64
1794484125 66
1794484130 66
1794484135 66
1794484140 66
1794484145 57
1794484150 57
1794484155 57
1794484160 57
1794484165 57
1794484170 57
1794484175 57
```
</details>

---

