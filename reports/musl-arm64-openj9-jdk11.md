---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-08-27 13:23:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 44 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 374 |
| Sample Rate | 6.23/sec |
| Health Score | 389% |
| Threads | 9 |
| Allocations | 163 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 38 |
| Sample Rate | 0.63/sec |
| Health Score | 39% |
| Threads | 9 |
| Allocations | 24 |

<details>
<summary>CPU Timeline (3 unique values: 19-44 cores)</summary>

```
1787851093 24
1787851098 24
1787851103 24
1787851108 24
1787851113 24
1787851118 24
1787851123 24
1787851128 24
1787851133 24
1787851138 24
1787851143 24
1787851148 24
1787851153 24
1787851158 24
1787851163 24
1787851168 24
1787851173 19
1787851178 19
1787851183 19
1787851188 19
```
</details>

---

