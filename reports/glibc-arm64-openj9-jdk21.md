---
layout: default
title: glibc-arm64-openj9-jdk21
---

## glibc-arm64-openj9-jdk21 - ✅ PASS

**Date:** 2026-11-23 05:22:24 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 52 |
| CPU Cores (end) | 37 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 10 |
| Allocations | 63 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 86 |
| Sample Rate | 1.43/sec |
| Health Score | 89% |
| Threads | 13 |
| Allocations | 39 |

<details>
<summary>CPU Timeline (3 unique values: 32-52 cores)</summary>

```
1795429068 52
1795429073 52
1795429078 52
1795429083 37
1795429088 37
1795429093 37
1795429098 37
1795429103 37
1795429108 37
1795429113 37
1795429118 37
1795429123 37
1795429128 37
1795429134 32
1795429139 32
1795429144 32
1795429149 32
1795429154 32
1795429159 32
1795429164 32
```
</details>

---

