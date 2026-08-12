---
layout: default
title: musl-x64-openj9-jdk11
---

## musl-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-12 05:20:33 EDT

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
| CPU Cores (start) | 32 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 628 |
| Sample Rate | 10.47/sec |
| Health Score | 654% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 838 |
| Sample Rate | 13.97/sec |
| Health Score | 873% |
| Threads | 9 |
| Allocations | 471 |

<details>
<summary>CPU Timeline (2 unique values: 30-32 cores)</summary>

```
1786526117 32
1786526122 32
1786526127 32
1786526132 32
1786526137 32
1786526142 32
1786526147 32
1786526152 32
1786526157 32
1786526162 32
1786526167 32
1786526172 32
1786526177 32
1786526182 30
1786526187 30
1786526192 30
1786526197 30
1786526202 30
1786526207 30
1786526212 30
```
</details>

---

