---
layout: default
title: glibc-arm64-openj9-jdk11
---

## glibc-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-20 12:39:27 EST

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
| CPU Cores (start) | 29 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 8 |
| Allocations | 60 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 101 |
| Sample Rate | 1.68/sec |
| Health Score | 105% |
| Threads | 12 |
| Allocations | 42 |

<details>
<summary>CPU Timeline (3 unique values: 29-64 cores)</summary>

```
1795196098 29
1795196103 29
1795196108 29
1795196113 29
1795196118 29
1795196123 64
1795196128 64
1795196133 64
1795196138 64
1795196143 34
1795196148 34
1795196153 34
1795196158 34
1795196163 34
1795196168 34
1795196173 34
1795196178 34
1795196183 34
1795196188 34
1795196193 34
```
</details>

---

