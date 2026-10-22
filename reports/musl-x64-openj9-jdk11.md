---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-10-22 17:27:09 EDT

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
| CPU Cores (start) | 30 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 611 |
| Sample Rate | 10.18/sec |
| Health Score | 636% |
| Threads | 8 |
| Allocations | 389 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 679 |
| Sample Rate | 11.32/sec |
| Health Score | 708% |
| Threads | 9 |
| Allocations | 515 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792704082 30
1792704087 30
1792704092 30
1792704097 30
1792704102 30
1792704107 30
1792704112 30
1792704117 30
1792704122 30
1792704127 30
1792704132 30
1792704137 30
1792704142 30
1792704147 30
1792704152 30
1792704157 30
1792704162 30
1792704167 30
1792704172 30
1792704177 32
```
</details>

---

