---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-20 10:11:02 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
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
| CPU Samples | 375 |
| Sample Rate | 6.25/sec |
| Health Score | 391% |
| Threads | 8 |
| Allocations | 385 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 466 |
| Sample Rate | 7.77/sec |
| Health Score | 486% |
| Threads | 9 |
| Allocations | 504 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1792505081 30
1792505086 32
1792505091 32
1792505096 32
1792505101 32
1792505106 32
1792505111 32
1792505116 32
1792505121 32
1792505126 32
1792505132 32
1792505137 32
1792505142 32
1792505147 32
1792505152 32
1792505157 32
1792505162 32
1792505167 32
1792505172 32
1792505177 32
```
</details>

---

