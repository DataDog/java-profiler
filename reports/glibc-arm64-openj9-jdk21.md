---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-13 09:34:12 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 174 |
| Sample Rate | 2.90/sec |
| Health Score | 181% |
| Threads | 11 |
| Allocations | 150 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 67 |
| Sample Rate | 1.12/sec |
| Health Score | 70% |
| Threads | 12 |
| Allocations | 53 |

<details>
<summary>CPU Timeline (3 unique values: 43-48 cores)</summary>

```
1794580079 46
1794580084 46
1794580089 46
1794580094 46
1794580099 46
1794580104 46
1794580109 46
1794580114 46
1794580119 46
1794580124 46
1794580129 46
1794580134 46
1794580139 46
1794580144 46
1794580149 48
1794580154 48
1794580159 48
1794580164 48
1794580169 43
1794580174 43
```
</details>

---

