---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-12 11:57:02 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 30 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 119 |
| Sample Rate | 1.98/sec |
| Health Score | 124% |
| Threads | 10 |
| Allocations | 73 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 17 |
| Sample Rate | 0.28/sec |
| Health Score | 18% |
| Threads | 7 |
| Allocations | 12 |

<details>
<summary>CPU Timeline (3 unique values: 21-30 cores)</summary>

```
1794502136 21
1794502141 21
1794502146 21
1794502151 21
1794502156 21
1794502161 21
1794502166 21
1794502171 21
1794502176 21
1794502181 23
1794502186 23
1794502191 23
1794502196 23
1794502202 23
1794502207 23
1794502212 23
1794502217 23
1794502222 21
1794502227 21
1794502232 21
```
</details>

---

