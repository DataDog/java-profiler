---
layout: default
title: musl-x64-hotspot-jdk17
---

## musl-x64-hotspot-jdk17 - ✅ PASS

**Date:** 2026-10-19 01:06:12 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-x64 |
| JVM | hotspot |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 24 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 540 |
| Sample Rate | 9.00/sec |
| Health Score | 562% |
| Threads | 8 |
| Allocations | 382 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 564 |
| Sample Rate | 9.40/sec |
| Health Score | 588% |
| Threads | 8 |
| Allocations | 469 |

<details>
<summary>CPU Timeline (2 unique values: 22-24 cores)</summary>

```
1792386123 22
1792386128 22
1792386133 22
1792386138 22
1792386143 22
1792386148 22
1792386153 22
1792386158 22
1792386163 22
1792386168 22
1792386173 22
1792386178 22
1792386183 22
1792386188 22
1792386193 24
1792386198 24
1792386203 24
1792386208 24
1792386213 24
1792386218 24
```
</details>

---

