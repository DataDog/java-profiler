---
layout: default
title: glibc-arm64-hotspot-jdk21
---

## glibc-arm64-hotspot-jdk21 - ✅ PASS

**Date:** 2026-10-24 04:44:30 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | hotspot |
| Java | jdk21 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 35 |
| CPU Cores (end) | 48 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 292 |
| Sample Rate | 4.87/sec |
| Health Score | 304% |
| Threads | 9 |
| Allocations | 169 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 879 |
| Sample Rate | 14.65/sec |
| Health Score | 916% |
| Threads | 12 |
| Allocations | 465 |

<details>
<summary>CPU Timeline (3 unique values: 35-48 cores)</summary>

```
1792831153 35
1792831158 35
1792831163 35
1792831168 35
1792831173 35
1792831178 35
1792831183 35
1792831188 35
1792831193 35
1792831198 40
1792831203 40
1792831208 40
1792831213 40
1792831218 40
1792831223 40
1792831228 40
1792831233 40
1792831238 40
1792831243 40
1792831248 40
```
</details>

---

