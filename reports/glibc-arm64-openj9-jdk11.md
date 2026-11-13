---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-13 09:34:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 40 |
| CPU Cores (end) | 40 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 100 |
| Sample Rate | 1.67/sec |
| Health Score | 104% |
| Threads | 10 |
| Allocations | 58 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 98 |
| Sample Rate | 1.63/sec |
| Health Score | 102% |
| Threads | 13 |
| Allocations | 49 |

<details>
<summary>CPU Timeline (1 unique values: 40-40 cores)</summary>

```
1794580094 40
1794580099 40
1794580104 40
1794580109 40
1794580114 40
1794580119 40
1794580124 40
1794580129 40
1794580134 40
1794580139 40
1794580144 40
1794580149 40
1794580154 40
1794580159 40
1794580164 40
1794580169 40
1794580174 40
1794580179 40
1794580184 40
1794580189 40
```
</details>

---

