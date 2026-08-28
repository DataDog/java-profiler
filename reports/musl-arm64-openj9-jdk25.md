---
layout: default
title: musl-arm64-openj9-jdk25
---

## musl-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-08-28 10:31:46 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 18 |
| CPU Cores (end) | 19 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 171 |
| Sample Rate | 2.85/sec |
| Health Score | 178% |
| Threads | 9 |
| Allocations | 131 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 56 |
| Sample Rate | 0.93/sec |
| Health Score | 58% |
| Threads | 9 |
| Allocations | 45 |

<details>
<summary>CPU Timeline (3 unique values: 17-19 cores)</summary>

```
1787927123 18
1787927128 18
1787927133 18
1787927138 18
1787927143 17
1787927148 17
1787927153 17
1787927158 17
1787927163 17
1787927168 17
1787927173 17
1787927178 17
1787927183 17
1787927188 17
1787927193 17
1787927198 17
1787927203 17
1787927208 17
1787927213 19
1787927218 19
```
</details>

---

