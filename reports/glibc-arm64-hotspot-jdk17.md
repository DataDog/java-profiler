---
layout: default
title: glibc-arm64-hotspot-jdk17
---

## glibc-arm64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-08-28 10:31:44 EDT

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
| CPU Cores (start) | 46 |
| CPU Cores (end) | 43 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 52 |
| Sample Rate | 0.87/sec |
| Health Score | 54% |
| Threads | 10 |
| Allocations | 68 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 61 |
| Sample Rate | 1.02/sec |
| Health Score | 64% |
| Threads | 14 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (4 unique values: 42-46 cores)</summary>

```
1787927134 46
1787927139 46
1787927144 46
1787927149 46
1787927154 46
1787927159 42
1787927164 42
1787927169 44
1787927174 44
1787927179 44
1787927184 44
1787927189 44
1787927194 44
1787927199 44
1787927204 44
1787927209 44
1787927214 44
1787927219 44
1787927224 44
1787927229 44
```
</details>

---

