---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-28 06:45:40 EDT

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
| CPU Cores (start) | 39 |
| CPU Cores (end) | 22 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 73 |
| Sample Rate | 1.22/sec |
| Health Score | 76% |
| Threads | 9 |
| Allocations | 61 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 78 |
| Sample Rate | 1.30/sec |
| Health Score | 81% |
| Threads | 12 |
| Allocations | 54 |

<details>
<summary>CPU Timeline (3 unique values: 22-39 cores)</summary>

```
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
1790592187 27
1790592192 27
1790592197 27
1790592202 27
1790592207 22
1790592212 22
1790592217 22
1790592222 22
1790592227 22
1790592232 22
```
</details>

---

