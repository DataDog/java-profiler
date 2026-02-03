---
layout: default
title: musl-x64-openj9-jdk17
---

## musl-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-02-03 11:36:28 EST

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
| CPU Cores (start) | 89 |
| CPU Cores (end) | 92 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 632 |
| Sample Rate | 10.53/sec |
| Health Score | 658% |
| Threads | 9 |
| Allocations | 350 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 997 |
| Sample Rate | 16.62/sec |
| Health Score | 1039% |
| Threads | 12 |
| Allocations | 487 |

<details>
<summary>CPU Timeline (3 unique values: 87-92 cores)</summary>

```
1770136121 89
1770136126 89
1770136131 89
1770136137 89
1770136142 89
1770136147 89
1770136152 87
1770136157 87
1770136162 87
1770136167 87
1770136172 92
1770136177 92
1770136182 92
1770136187 92
1770136192 92
1770136197 92
1770136202 92
1770136207 92
1770136212 92
1770136217 92
```
</details>

---

