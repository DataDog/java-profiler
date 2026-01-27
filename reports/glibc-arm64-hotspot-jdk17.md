---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ❌ FAIL

**Date:** 2026-01-27 10:22:44 EST

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 24 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 87 |
| Sample Rate | 2.90/sec |
| Health Score | 181% |
| Threads | 9 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ❌
| Metric | Value |
|--------|-------|
| Status | FAIL |
| CPU Samples | 12 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 6 |
| Allocations | 8 |

<details>
<summary>CPU Timeline (1 unique values: 24-24 cores)</summary>

```
1769527068 24
1769527073 24
1769527078 24
1769527083 24
1769527088 24
1769527093 24
1769527098 24
1769527103 24
1769527108 24
1769527113 24
1769527118 24
1769527123 24
1769527128 24
1769527133 24
1769527138 24
1769527143 24
1769527148 24
1769527153 24
1769527158 24
1769527163 24
```
</details>

---

