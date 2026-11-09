---
layout: default
title: musl-arm64-openj9-jdk11
---

## musl-arm64-openj9-jdk11 - ✅ PASS

**Date:** 2026-11-09 11:10:57 EST

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
| CPU Cores (start) | 45 |
| CPU Cores (end) | 46 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 289 |
| Sample Rate | 4.82/sec |
| Health Score | 301% |
| Threads | 12 |
| Allocations | 172 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 77 |
| Sample Rate | 1.28/sec |
| Health Score | 80% |
| Threads | 11 |
| Allocations | 56 |

<details>
<summary>CPU Timeline (3 unique values: 45-48 cores)</summary>

```
1794240162 45
1794240167 45
1794240172 48
1794240177 48
1794240182 48
1794240187 48
1794240192 48
1794240198 48
1794240203 48
1794240208 48
1794240213 48
1794240218 48
1794240223 48
1794240228 48
1794240233 48
1794240238 46
1794240243 46
1794240248 46
1794240253 46
1794240258 46
```
</details>

---

