---
layout: default
title: glibc-x64-openj9-jdk25
---

## glibc-x64-openj9-jdk25 - ✅ PASS

**Date:** 2026-11-13 09:34:14 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 60 |
| CPU Cores (end) | 68 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 381 |
| Sample Rate | 6.35/sec |
| Health Score | 397% |
| Threads | 9 |
| Allocations | 403 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 683 |
| Sample Rate | 11.38/sec |
| Health Score | 711% |
| Threads | 11 |
| Allocations | 477 |

<details>
<summary>CPU Timeline (2 unique values: 60-68 cores)</summary>

```
1794580063 60
1794580068 60
1794580073 60
1794580078 60
1794580083 60
1794580088 60
1794580093 60
1794580098 60
1794580103 60
1794580108 60
1794580113 60
1794580118 60
1794580123 60
1794580128 60
1794580133 60
1794580138 60
1794580143 60
1794580148 68
1794580153 68
1794580158 68
```
</details>

---

