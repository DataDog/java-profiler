---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-09-17 06:53:09 EDT

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
| CPU Cores (start) | 38 |
| CPU Cores (end) | 41 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 45 |
| Sample Rate | 0.75/sec |
| Health Score | 47% |
| Threads | 7 |
| Allocations | 69 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 55 |
| Sample Rate | 0.92/sec |
| Health Score | 57% |
| Threads | 12 |
| Allocations | 36 |

<details>
<summary>CPU Timeline (6 unique values: 38-48 cores)</summary>

```
1789642118 38
1789642123 38
1789642128 43
1789642133 43
1789642138 43
1789642143 43
1789642148 47
1789642153 47
1789642158 47
1789642163 47
1789642168 47
1789642173 47
1789642178 48
1789642183 48
1789642189 46
1789642194 46
1789642199 46
1789642204 46
1789642209 41
1789642214 41
```
</details>

---

