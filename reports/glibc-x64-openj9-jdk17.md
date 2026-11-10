---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-10 11:01:15 EST

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
| CPU Cores (start) | 56 |
| CPU Cores (end) | 65 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 510 |
| Sample Rate | 8.50/sec |
| Health Score | 531% |
| Threads | 9 |
| Allocations | 352 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 584 |
| Sample Rate | 9.73/sec |
| Health Score | 608% |
| Threads | 11 |
| Allocations | 460 |

<details>
<summary>CPU Timeline (6 unique values: 47-67 cores)</summary>

```
1794326116 56
1794326121 56
1794326126 58
1794326131 58
1794326136 47
1794326141 47
1794326146 47
1794326151 47
1794326156 50
1794326161 50
1794326166 50
1794326171 50
1794326176 50
1794326181 50
1794326186 50
1794326191 50
1794326196 50
1794326201 67
1794326206 67
1794326211 67
```
</details>

---

