---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-17 08:01:56 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 89 |
| CPU Cores (end) | 93 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 449 |
| Sample Rate | 7.48/sec |
| Health Score | 468% |
| Threads | 9 |
| Allocations | 336 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 957 |
| Sample Rate | 15.95/sec |
| Health Score | 997% |
| Threads | 12 |
| Allocations | 468 |

<details>
<summary>CPU Timeline (3 unique values: 87-93 cores)</summary>

```
1794920169 89
1794920174 89
1794920179 89
1794920184 89
1794920189 87
1794920194 87
1794920199 87
1794920204 87
1794920210 87
1794920215 87
1794920220 87
1794920225 87
1794920230 87
1794920235 87
1794920240 87
1794920245 87
1794920250 87
1794920255 87
1794920260 87
1794920265 87
```
</details>

---

