---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-28 06:45:43 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 45 |
| CPU Cores (end) | 66 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 543 |
| Sample Rate | 9.05/sec |
| Health Score | 566% |
| Threads | 9 |
| Allocations | 400 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 697 |
| Sample Rate | 11.62/sec |
| Health Score | 726% |
| Threads | 10 |
| Allocations | 437 |

<details>
<summary>CPU Timeline (3 unique values: 45-78 cores)</summary>

```
1790592072 45
1790592077 45
1790592082 45
1790592087 45
1790592092 45
1790592097 45
1790592102 45
1790592107 45
1790592112 45
1790592117 45
1790592122 45
1790592127 45
1790592132 45
1790592137 78
1790592142 78
1790592147 78
1790592152 78
1790592157 78
1790592162 78
1790592167 78
```
</details>

---

