---
layout: default
title: glibc-x64-openj9-jdk11
---

## glibc-x64-openj9-jdk11 - ✅ PASS

**Date:** 2026-09-29 05:50:06 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 33 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 558 |
| Sample Rate | 9.30/sec |
| Health Score | 581% |
| Threads | 8 |
| Allocations | 387 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 766 |
| Sample Rate | 12.77/sec |
| Health Score | 798% |
| Threads | 9 |
| Allocations | 538 |

<details>
<summary>CPU Timeline (4 unique values: 31-44 cores)</summary>

```
1790675062 33
1790675067 33
1790675072 33
1790675077 33
1790675082 33
1790675087 33
1790675092 33
1790675097 33
1790675102 33
1790675107 33
1790675112 31
1790675117 31
1790675122 42
1790675127 42
1790675132 44
1790675137 44
1790675142 44
1790675147 44
1790675152 44
1790675157 44
```
</details>

---

