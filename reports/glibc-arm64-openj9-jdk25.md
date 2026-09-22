---
layout: default
title: glibc-arm64-openj9-jdk25
---

## glibc-arm64-openj9-jdk25 - ✅ PASS

**Date:** 2026-09-22 12:28:35 EDT

### Configuration
| Setting | Value |
|---------|-------|
| Platform | glibc-arm64 |
| JVM | openj9 |
| Java | jdk25 |
| Container | false |

### System Diagnostics
| Metric | Value |
|--------|-------|
| CPU Cores (start) | 19 |
| CPU Cores (end) | 17 |
| Throttling | 0% |

### Test Results

#### Scenario 1: Profiler-Only ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 247 |
| Sample Rate | 4.12/sec |
| Health Score | 258% |
| Threads | 11 |
| Allocations | 101 |

#### Scenario 2: Tracer+Profiler ✅
| Metric | Value |
|--------|-------|
| Status | PASS |
| CPU Samples | 90 |
| Sample Rate | 1.50/sec |
| Health Score | 94% |
| Threads | 15 |
| Allocations | 72 |

<details>
<summary>CPU Timeline (2 unique values: 17-19 cores)</summary>

```
1790094179 19
1790094184 19
1790094189 19
1790094194 19
1790094199 19
1790094204 19
1790094209 19
1790094214 19
1790094219 19
1790094224 19
1790094229 19
1790094234 19
1790094239 19
1790094244 19
1790094249 19
1790094254 19
1790094259 19
1790094264 17
1790094269 17
1790094274 17
```
</details>

---

