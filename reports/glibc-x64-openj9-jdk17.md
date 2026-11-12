---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-11-12 12:27:12 EST

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
| CPU Cores (start) | 71 |
| CPU Cores (end) | 67 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 448 |
| Sample Rate | 7.47/sec |
| Health Score | 467% |
| Threads | 9 |
| Allocations | 357 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 530 |
| Sample Rate | 8.83/sec |
| Health Score | 552% |
| Threads | 11 |
| Allocations | 442 |

<details>
<summary>CPU Timeline (3 unique values: 67-73 cores)</summary>

```
1794504133 71
1794504138 71
1794504143 71
1794504148 71
1794504153 71
1794504158 71
1794504163 71
1794504168 73
1794504173 73
1794504178 73
1794504183 73
1794504188 73
1794504193 67
1794504198 67
1794504203 67
1794504208 67
1794504213 67
1794504218 67
1794504223 67
1794504228 67
```
</details>

---

