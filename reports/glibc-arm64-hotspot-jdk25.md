---
layout: default
title: glibc-arm64-hotspot-jdk25
---

## glibc-arm64-hotspot-jdk25 - ✅ PASS

**Date:** 2026-09-28 06:45:40 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 39 |
| CPU Cores (end) | 34 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 24 |
| Sample Rate | 0.40/sec |
| Health Score | 25% |
| Threads | 10 |
| Allocations | 17 |

<details>
<summary>CPU Timeline (2 unique values: 34-39 cores)</summary>

```
1790592122 39
1790592127 39
1790592132 39
1790592137 39
1790592142 39
1790592147 39
1790592152 39
1790592157 39
1790592162 39
1790592167 39
1790592172 39
1790592177 39
1790592182 39
1790592187 39
1790592192 39
1790592197 39
1790592202 39
1790592207 39
1790592212 39
1790592217 39
```
</details>

---

