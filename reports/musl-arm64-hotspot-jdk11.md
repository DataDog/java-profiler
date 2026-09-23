---
layout: default
title: musl-arm64-hotspot-jdk11
---

## musl-arm64-hotspot-jdk11 - ✅ PASS

**Date:** 2026-09-23 07:03:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | musl-arm64 |
| JVM | hotspot |
| Java | jdk11 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 22 |
| CPU Cores (end) | 59 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 125 |
| Sample Rate | 2.08/sec |
| Health Score | 130% |
| Threads | 8 |
| Allocations | 57 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 1023 |
| Sample Rate | 17.05/sec |
| Health Score | 1066% |
| Threads | 9 |
| Allocations | 449 |

<details>
<summary>CPU Timeline (2 unique values: 22-59 cores)</summary>

```
1790161148 22
1790161153 22
1790161158 22
1790161163 59
1790161168 59
1790161173 59
1790161178 59
1790161183 59
1790161188 59
1790161193 59
1790161198 59
1790161203 59
1790161208 59
1790161213 59
1790161218 59
1790161223 59
1790161228 59
1790161233 59
1790161238 59
1790161243 59
```
</details>

---

