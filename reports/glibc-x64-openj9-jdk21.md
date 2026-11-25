---
layout: default
title: glibc-x64-openj9-jdk21
---

## glibc-x64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-25 13:14:38 EST

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
| CPU Cores (start) | 79 |
| CPU Cores (end) | 81 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 127 |
| Sample Rate | 2.12/sec |
| Health Score | 132% |
| Threads | 10 |
| Allocations | 71 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 10 |
| Allocations | 18 |

<details>
<summary>CPU Timeline (2 unique values: 79-81 cores)</summary>

```
1795630122 79
1795630127 79
1795630132 79
1795630137 79
1795630142 79
1795630147 79
1795630152 79
1795630157 79
1795630162 79
1795630167 79
1795630172 79
1795630177 79
1795630182 79
1795630187 79
1795630192 79
1795630197 79
1795630202 79
1795630207 79
1795630212 81
1795630217 81
```
</details>

---

