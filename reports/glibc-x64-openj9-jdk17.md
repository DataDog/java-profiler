---
layout: default
title: glibc-x64-openj9-jdk17
---

## glibc-x64-openj9-jdk17 - ✅ PASS

**Date:** 2026-09-23 07:03:23 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-x64 |
| JVM | openj9 |
| Java | jdk17 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 21 |
| CPU Cores (end) | 21 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 447 |
| Sample Rate | 7.45/sec |
| Health Score | 466% |
| Threads | 8 |
| Allocations | 325 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 568 |
| Sample Rate | 9.47/sec |
| Health Score | 592% |
| Threads | 9 |
| Allocations | 446 |

<details>
<summary>CPU Timeline (2 unique values: 21-23 cores)</summary>

```
1790161148 21
1790161153 21
1790161158 21
1790161163 21
1790161168 23
1790161173 23
1790161178 23
1790161183 23
1790161188 23
1790161193 23
1790161198 23
1790161203 23
1790161208 23
1790161213 23
1790161218 23
1790161223 23
1790161228 23
1790161233 23
1790161238 23
1790161243 23
```
</details>

---

