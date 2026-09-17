---
layout: default
title: musl-arm64-openj9-jdk17
---

## musl-arm64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-17 06:53:11 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 38 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 59 |
| Sample Rate | 0.98/sec |
| Health Score | 61% |
| Threads | 9 |
| Allocations | 66 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 240 |
| Sample Rate | 4.00/sec |
| Health Score | 250% |
| Threads | 10 |
| Allocations | 110 |

<details>
<summary>CPU Timeline (3 unique values: 30-38 cores)</summary>

```
1789642108 35
1789642113 35
1789642118 35
1789642123 35
1789642128 35
1789642133 35
1789642138 35
1789642143 35
1789642148 35
1789642153 35
1789642158 35
1789642163 35
1789642168 35
1789642173 35
1789642178 35
1789642183 35
1789642188 30
1789642193 30
1789642198 30
1789642203 30
```
</details>

---

