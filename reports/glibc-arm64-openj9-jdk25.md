---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-10-02 04:21:37 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 32 |
| CPU Cores (end) | 32 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 302 |
| Sample Rate | 5.03/sec |
| Health Score | 314% |
| Threads | 10 |
| Allocations | 154 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 79 |
| Sample Rate | 1.32/sec |
| Health Score | 82% |
| Threads | 12 |
| Allocations | 44 |

<details>
<summary>CPU Timeline (1 unique values: 32-32 cores)</summary>

```
1790929068 32
1790929073 32
1790929078 32
1790929083 32
1790929088 32
1790929093 32
1790929098 32
1790929103 32
1790929108 32
1790929113 32
1790929118 32
1790929123 32
1790929128 32
1790929133 32
1790929138 32
1790929143 32
1790929148 32
1790929153 32
1790929158 32
1790929163 32
```
</details>

---

